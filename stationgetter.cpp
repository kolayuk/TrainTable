#include "stationgetter.h"
#include <QDeclarativeContext>
#include <QDebug>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QtAlgorithms>
#include <QFile>
#include <QTextCodec>
#include "const.h"
#include <QDir>
bool compareWordItem ( const Station &w1 , const Station &w2 )
{
    return w1.dim > w2.dim;
}

StationGetter::StationGetter(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent),viewer(v)
{
    GPS=false;
    radius=START_RADIUS;
    viewer.rootContext()->setContextProperty("getstation",this);
#ifdef Q_OS_SYMBIAN

    iSource = QtMobility::QGeoPositionInfoSource::createDefaultSource(this);
    if (iSource) {
        connect(iSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(PosUpdated(QGeoPositionInfo)));
        connect(iSource, SIGNAL(updateTimeout()),
                this, SLOT(TimeoutGPS()));
        iSource->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
    }
#endif
    iLongitude=0;
    iLatitude=0;
    iHTTP = new QNetworkAccessManager(this);
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(GeoStationFound(QNetworkReply*)));
    //StartPosSearch();
}


#ifndef Q_OS_SYMBIAN
void StationGetter::timerEvent(QTimerEvent *)
{
    searchingstation=true;
    iLongitude=59.632092;
    iLatitude=30.406637;
    emit coordinatesChanged(QString::number(iLongitude),QString::number(iLatitude));
    QString u;
    u.sprintf(URL_TEMPLATE_STATION_GEO,iLongitude,iLatitude,radius);
    qDebug()<<u;
    QUrl url(u);
    killTimer(iTimer);
    QNetworkReply* reply = iHTTP->get(QNetworkRequest(url));

}
#endif
void StationGetter::GeoStationFound(QNetworkReply *reply)
{
    qDebug()<<"GeoStationFound";
    if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray bytes = reply->readAll();  // bytes
            QString fstring=QString::fromUtf8(bytes); // string
            if (fstring.count()==0){return;}
            QString status=fstring.split("<status>").at(1).split("</status>").at(0);
            if (status=="OK")
            {
#ifdef Q_OS_SYMBIAN
                QGeoCoordinate user(iLongitude,iLatitude);
#endif
                QString string;
                int i;
                foreach(string,fstring.split("</result>"))
                {
                    if (string.indexOf("<result>")<0){continue;}
                    QString name=string.split("<name>").at(1).split("</name>").at(0);
                    double latitude=string.split("<lat>").at(1).split("</lat>").at(0).toDouble();
                    double longitude=string.split("<lng>").at(1).split("</lng>").at(0).toDouble();
                    qDebug()<<name;
                    qDebug()<<latitude;
                    qDebug()<<longitude;
                    double dim;
#ifdef Q_OS_SYMBIAN
                    QGeoCoordinate station(longitude,latitude);
                    dim=user.distanceTo(station);

#else
                    dim=i==0?1:0;
#endif
                    QString id=QString("");
                    Station st={name,id,longitude,latitude,dim};
                    //sort
                    if (iStations.count()==0){iStations.append(st);}
                    if (iStations[0].dim>dim){iStations.prepend(st);}
                    else {iStations.append(st);}
                    i++;
                }
                GPS=true;
                StopPosSearch();
                GetStationID(iStations[0].name);
            }
            else if (status=="ZERO_RESULTS")
            {
                unableToGetStation(QString::fromUtf8("Поблизости нет станций"));//.arg(QString::number(radius/1000)));
                //emit needToIncRadius();
                StopPosSearch();
            }
            else
            {
                qDebug()<<3;
                unableToGetStation(QString::fromUtf8("Неизвестная ошибка"));
                StopPosSearch();
            }

        }
    else
    {
        unableToGetStation(QString::fromUtf8("Ошибка HTTP"));
        StopPosSearch();
    }
}

void StationGetter::GetStationID(QString name)
{
    qDebug()<<"getting id";
    emit setListType(EFinding);
    QStringList empty;
    viewer.rootContext()->setContextProperty("stringsModel",empty);
    QString surl=QString("urlhere");
    QByteArray u8=QTextCodec::codecForName("UTF-8")->fromUnicode(name);
    u8.replace("%","");
    surl.sprintf(URL_GET_STATION_ID,u8.constData());
    QUrl url(surl);
    QNetworkReply* reply = iHTTP->get(QNetworkRequest(url));

}

void StationGetter::StartPosSearch()
{
    runninggps=true;
    qDebug()<<"Start GEO";
#ifdef Q_OS_SYMBIAN
    if (iSource){iSource->requestUpdate(POSITIONING_TIMEOUT*1000);}
#else
  iTimer=startTimer(10000);
#endif
  QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)),this, SLOT(StationIDFound(QNetworkReply*)));
  QObject::connect(iHTTP,SIGNAL(finished(QNetworkReply*)),this,SLOT(GeoStationFound(QNetworkReply*)));

}

void StationGetter::StopPosSearch()
{
    if (!runninggps){return;}
    runninggps=false;
    searchingstation=false;
    qDebug()<<"stop geo";
#ifdef Q_OS_SYMBIAN
    if (iSource){iSource->stopUpdates();}
#else
    killTimer(iTimer);
#endif
    QObject::disconnect(iHTTP,SIGNAL(finished(QNetworkReply*)),this,SLOT(GeoStationFound(QNetworkReply*)));
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)),this, SLOT(StationIDFound(QNetworkReply*)));
}

void StationGetter::StationIDFound(QNetworkReply *reply)
{
    if (reply->error()!=QNetworkReply::NoError){emit unableToGetStation(QString::fromUtf8("Ошибка HTTP"));}
    qDebug()<<"StationIDFound";
    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    qDebug()<<statusCodeV.toInt();

    QByteArray dataarr=reply->readAll();
    QString data=QString::fromUtf8(dataarr);

    QVariant possibleRedirectUrl =reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(!possibleRedirectUrl.toUrl().isEmpty())
    {
        qDebug()<<"redirect found";
        QString url=possibleRedirectUrl.toUrl().toString();
        if (url.contains("station"))
        {
            if (iStations.count()==0){Station st; iStations.append(st);}
            iStations[0].name=url.split("?title=")[1];
            iStations[0].name=iStations[0].name.replace("+"," ");
            iStations[0].url=possibleRedirectUrl.toUrl().toString();

            //stations cache
            QStringList lines;
            QString line;
            bool found=false;
            QFile file(FILE_STATIONS_CACHE);
            if (file.open (QIODevice::ReadOnly))
            {
                QTextStream stream ( &file );
                stream.setCodec("UTF-8");
                while( !stream.atEnd())
                {
                     line=stream.readLine();
                     if (line.contains(iStations[0].name)){found=true;}
                     lines.append(line);
                }
                file.close();
            }
            line=iStations[0].name+"***"+iStations[0].url;
            if (!found){lines.insert(0,line);}
            if (!file.open (QIODevice::WriteOnly)) return;
            QTextStream stream ( &file );
            stream.setCodec("UTF-8");
            for (int i=0;i<lines.count();i++)
            {
                stream << lines[i] << "\n";
            }
            file.close(); // when your done.
            if (!GPS){emit gotoTimeTable(iStations[0].url,iStations[0].name,GPS);}
            emit stationRecieved(iStations[0].name,iStations[0].longitude,iStations[0].latitude);
            GetCachedStations();
            GPS=false;
        }
        else
        {
            qDebug()<<"city in url, getting new page";
            QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)),this, SLOT(StationIDFound(QNetworkReply*)));
            QObject::connect(iHTTP,SIGNAL(finished(QNetworkReply*)),this,SLOT(GotSeveralSearshResults(QNetworkReply*)));
            iHTTP->get(QNetworkRequest(url));
        }
    }
    else
    {
        if (data.contains(QString::fromUtf8("Ничего не найдено")))
        {
            emit unableToGetStation(QString::fromUtf8("Нет расписания для этой станции"));
        }
        else
        {
            qDebug()<<"several results, will parse";
            parseSeveralSearchResults(data);
        }
    }
}
void StationGetter::GotSeveralSearshResults(QNetworkReply *reply)
{
    if (reply->error()!=QNetworkReply::NoError){emit unableToGetStation(QString::fromUtf8("Ошибка HTTP"));}
    qDebug()<<"GotSeveralSearshResults";
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)),this, SLOT(StationIDFound(QNetworkReply*)));
    QObject::disconnect(iHTTP,SIGNAL(finished(QNetworkReply*)),this,SLOT(GotSeveralSearshResults(QNetworkReply*)));
    QByteArray dataarr=reply->readAll();
    QString data=QString::fromUtf8(dataarr);
    parseSeveralSearchResults(data);
}
void StationGetter::parseSeveralSearchResults(QString data)
{
    QRegExp exp;
    qDebug()<<"Parsing data, length "<<data.count();
    QString curUrl=data.split("&quot;retpath&quot;:&quot;")[1].split("&quot")[0];
    qDebug()<<curUrl;
    if (curUrl.contains("city/")){exp.setPattern("(/station/.[^<>]+>.[^<>]+</a>)");}
    else {exp.setPattern("(/station/.[^<>]+>.[^<>]+</a>)|(/city/.[^<>]+>.[^<>]+</a>)");}
      int pos = 0;
      int plpos=0;
      QStringList list;
      QStringList places;
      while((pos = exp.indexIn(data, pos)) != -1)
      {
        list << exp.cap(0);
        pos += exp.matchedLength();
        if (data.right(pos).contains("b-precise-list__place"))
        {
            QRegExp expPl("\\(.[^\\)]+\\)");
            plpos=expPl.indexIn(data, pos);
            places<<expPl.cap(0);
        }
      }
      SearchStationInfo info;
      searchResults.clear();
      QStringList modelData;
      QString modelStr;
      qDebug()<<list;
      for (int i=0;i<list.count();i++)
      {
          list[i]=list[i].replace("&nbsp;"," ");
          if (places.count()>0){info.region=places[i];}
          info.name=list[i].left(list[i].count()-4).split("\">")[1];
          info.url="http://rasp.yandex.ru"+list[i].left(list[i].count()-4).split("\">")[0];
          if (info.url.contains("?")){info.url=info.url.split("?")[0];}
          qDebug()<<info.url;
          qDebug()<<info.name;
          searchResults.append(info);
          modelStr=info.name+"***"+info.region;
          modelData.append(modelStr);
      }
      viewer.rootContext()->setContextProperty("stringsModel",modelData);
      if (!GPS) {emit setListType(ESearchResults);}
      else {emit setListType(ESeveralNear);}
      GPS=false;

}

void StationGetter::GetCachedStations()
{
 searchResults.clear();
 QStringList modelData;

 SearchStationInfo info;
 QString line;
 QString modelStr;
 QFile file(FILE_STATIONS_CACHE);
 if (file.open (QIODevice::ReadOnly))
 {
     QTextStream stream ( &file );
     stream.setCodec("UTF-8");
     while( !stream.atEnd())
     {
          line=stream.readLine();
          info.name=line.split("***")[0];
          info.url=line.split("***")[1];
          info.region="";
          searchResults.append(info);
          modelStr=info.name+"***"+info.region;
          modelData.append(modelStr);
     }
     file.close();
     viewer.rootContext()->setContextProperty("stringsModel",modelData);
     emit setListType(ECachedItems);
 }
}

void StationGetter::listViewPressed(int index)
{
    qDebug()<<"listViewPressed();";
    if (searchResults[index].url.contains("station"))
    {
        QStringList lines;
        QString line;
        bool found=false;
        QFile file(FILE_STATIONS_CACHE);
        if (file.open (QIODevice::ReadOnly))
        {
            QTextStream stream ( &file );
            stream.setCodec("UTF-8");
            while( !stream.atEnd())
            {
                 line=stream.readLine();
                 if (line.contains(searchResults[index].name)){found=true;}
                 lines.append(line);
            }
            file.close();
        }
        line=searchResults[index].name+"***"+searchResults[index].url;
        if (!found){lines.insert(0,line);}
        if (!file.open (QIODevice::WriteOnly)) return;
        QTextStream stream ( &file );
        stream.setCodec("UTF-8");
        for (int i=0;i<lines.count();i++)
        {
            stream << lines[i] << "\n";
        }
        file.close(); // when your done.
        emit gotoTimeTable(searchResults[index].url,searchResults[index].name,GPS);
    }
    else
    {
        setListType(EFinding);
        QStringList m;
        viewer.rootContext()->setContextProperty("stringsModel",m);
        qDebug()<<"city in url, getting new page";
        QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)),this, SLOT(StationIDFound(QNetworkReply*)));
        QObject::connect(iHTTP,SIGNAL(finished(QNetworkReply*)),this,SLOT(GotSeveralSearshResults(QNetworkReply*)));
        iHTTP->get(QNetworkRequest(searchResults[index].url));
    }
}

void StationGetter::SendGotoTimeTable()
{
    emit gotoTimeTable(iStations[0].url,iStations[0].name,GPS);
}

void StationGetter::clearCache()
{
    QFile file(FILE_STATIONS_CACHE);
    if (file.exists()){file.remove();}
    searchResults.clear();
    qDebug()<<removeDir(QString(TIMETABLE_CACHE_FOLDER));
    QStringList modelData;
    viewer.rootContext()->setContextProperty("stringsModel",modelData);
}

bool StationGetter::removeDir(const QString &dirName)
{
    qDebug()<<"remove"<<dirName;
    bool result = true;
    QDir dir(dirName);
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}

void StationGetter::incRadius()
{

    radius=radius+2000;
    QString u;
    u.sprintf(URL_TEMPLATE_STATION_GEO,iLatitude,iLongitude,radius);
    QUrl url(u);
    qDebug()<<"incRadius"<<url;
    QNetworkReply* reply = iHTTP->get(QNetworkRequest(url));
}

void StationGetter::requestMap()
{
    qDebug()<<"requestMap";
    showMap(iLatitude,iLongitude,iStations[0].latitude,iStations[0].longitude);
}

#ifdef Q_OS_SYMBIAN
void StationGetter::PosUpdated(QGeoPositionInfo info)
{
    searchingstation=true;
    iLatitude=info.coordinate().latitude();
    iLongitude=info.coordinate().longitude();
    iSource->stopUpdates();
    qDebug()<<"coordinates recieved "<<iLongitude<<" "<<iLatitude;
    QString lon=QString::number( iLongitude, 'f', 2);
    QString lat=QString::number( iLatitude, 'f', 2);
    emit coordinatesChanged(lon,lat);
    QString u;
    u.sprintf(URL_TEMPLATE_STATION_GEO,iLatitude,iLongitude,radius);
    QUrl url(u);
    QNetworkReply* reply = iHTTP->get(QNetworkRequest(url));
}
void StationGetter::TimeoutGPS()
{
        timeouted(QString("GPS"));
        qDebug()<<"timeout GPS";
}

#endif


