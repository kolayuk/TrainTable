#include "timetable.h"
#include <qdebug.h>
#include <QDeclarativeContext>
#include <QRegExp>
#include <QFile>
#include <QDir>
#include "const.h"
#include <QTextCodec>

Timetable::Timetable(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent),viewer(v)
{
    viewer.rootContext()->setContextProperty("timetable",this);
    iHTTP = new QNetworkAccessManager(this);
    hiddenTrains=0;
    connect(this,SIGNAL(setTrainListState(int)),this,SLOT(storeListState(int)));
}

void Timetable::setStation(QString url, QString name)
{
    setTrainListState(ETrainsListOpened);
    trains.clear();
    modelData.clear();
    viewer.rootContext()->setContextProperty("trainsModel",modelData);
    qDebug()<<"setStation";
    emit setUIText(name);
    emit setTrainListState(ETrainsListLoading);
    iStation.name=name;
    if (url.contains("?")){url=url.split("?")[0];}
    iStation.id=url.split("/")[url.split("/").count()-1];
    qDebug()<<iStation.id;
    iStation.url=url+"?type=suburban";
    QDate date=QDate::currentDate();
    QDir dir(TIMETABLE_CACHE_FOLDER);
    if (!dir.exists()){dir.mkdir(TIMETABLE_CACHE_FOLDER);}
    QFile file(TIMETABLE_CACHE_FOLDER+iStation.id+"-"+QString::number(date.dayOfYear())+".html");
    if (file.exists())
    {
        qDebug()<<"data got from cache";
        file.open(QIODevice::ReadOnly);
        QByteArray arr=file.readAll();
        QString data=QString::fromUtf8(arr);
        file.close();
        parseTrainList(data);
    }
    else
    {
    QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    iHTTP->get(QNetworkRequest(iStation.url));
    }
}

void Timetable::GotTrainList(QNetworkReply *reply)
{
    qDebug()<<"rasp got from internet";
    QDate date=QDate::currentDate();

    QByteArray arr=reply->readAll();
    QString data=QString::fromUtf8(arr);
    QFile file(TIMETABLE_CACHE_FOLDER+iStation.id+"-"+QString::number(date.dayOfYear())+".html");
    file.open(QIODevice::WriteOnly);
    file.write(arr);
    file.close();
    parseTrainList(data);
}

void Timetable::parseTrainList(QString data)
{
    hiddenTrains=0;
    qDebug()<<"parseTrainList "<<data.count();
    iStation.directions.clear();
    //get directions
    QStringList list;
    QRegExp exp;
    exp.setPattern("\\?direction=.[^<]+<");
    int pos = 0;
    QString temp;
    while((pos = exp.indexIn(data, pos)) != -1)
    {
        temp=exp.cap(0);
        if (temp.contains("span")){pos += exp.matchedLength();continue;}
        temp=temp.split(">")[1];
        temp=temp.left(temp.count()-1).replace("+"," ");
        if (temp.count()>2&&!temp.contains(QString::fromUtf8("все направления"))&&!temp.contains(QString::fromUtf8("прибытие"))){ list << temp;}
        pos += exp.matchedLength();
    }
    //currently active, there is another format
    exp.setPattern("direction__item_state_current.[^<]+<");
    pos = 0;
    iStation.currentDirection=list.count();
    qDebug()<<"current direction (count before current): "<<list.count();
    while((pos = exp.indexIn(data, pos)) != -1)
    {
        temp=exp.cap(0);
        if (temp.contains("span")){pos += exp.matchedLength();continue;}
        temp=temp.split(">")[1];
        temp=temp.left(temp.count()-1).replace("+"," ");
        if (temp.count()>2&&!temp.contains(QString::fromUtf8("все направления"))&&!temp.contains(QString::fromUtf8("прибытие"))){ list << temp;}
        pos += exp.matchedLength();
    }
    qDebug()<<list;
    iStation.directions.clear();
    iStation.directions.append(list);
    viewer.rootContext()->setContextProperty("directionCount",iStation.directions.count());
    if (iStation.directions.count()!=0)
    {
    QDate date=QDate::currentDate();
    int day=date.dayOfYear();
    QFile file(TIMETABLE_CACHE_FOLDER+iStation.id+"-"+QString::number(day)+"-"+iStation.directions[iStation.currentDirection]+".html");
    file.open(QIODevice::WriteOnly);
    file.write(data.toUtf8());
    file.close();
    QStringList directions=iStation.directions;
    directions<<QString::fromUtf8("На станцию...");
    emit setCurrentDirection(iStation.currentDirection);
    viewer.rootContext()->setContextProperty("currentDirection",iStation.currentDirection);
    viewer.rootContext()->setContextProperty("directionsModel",directions);
    }
    //get trains
    list.clear();
    list=data.split("b-timetable__row");
    list.removeAt(0);
    list.removeAt(list.count()-2);
    list[list.count()-1]=list[list.count()-1].split("</tr>")[0];
    qDebug()<<list.count()<<" trains from station";
    for (int i=0;i<list.count();i++)
    {
        if (list[i].count()<10) continue;
        qDebug()<<"train"<<i;
        Train train;
        exp.setPattern("/thread/.[^>]+>");
        exp.indexIn(list[i]);
        if (exp.cap(0).contains('"')){train.url="http://rasp.yandex.ru"+exp.cap(0).split('"')[0];}
        qDebug()<<train.url;
        if (train.url.count()==0)
        {// GotTrain list called unknown
        setUIText(QString::fromUtf8("Ошибка! Нажмите назад и очистить."));
        return;
        }
        exp.setPattern("g-nowrap.[^<]+</");
        pos = 0;
        QStringList fromto;
        while((pos = exp.indexIn(list[i], pos)) != -1)
        {
            fromto<<exp.cap(0);
            pos += exp.matchedLength();
        }
        train.from=fromto[0].split(">")[1].split("<")[0];
        train.to=fromto[1].split(">")[1].split("<")[0];
        qDebug()<<train.from;
        qDebug()<<train.to;

        exp.setPattern("\\}\">.[^ ]+</strong>");
        exp.indexIn(list[i]);
        train.time=exp.cap(0).replace("<strong>","").replace("</strong>","");
        train.time=train.time.right(train.time.count()-3).left(train.time.count()-10);
        qDebug()<<train.time;

        exp.setPattern("stations\">.[^<]+</span");
        exp.indexIn(list[i]);
        train.exceptStations=exp.cap(0).right(exp.cap(0).count()-10).left(exp.cap(0).count()-16);
        qDebug()<<train.exceptStations;
        if (list[i].contains("b-timetable__days"))
        {
            temp=list[i].split("timetable__days_tz_null")[1].split("div")[0];
            qDebug()<<temp;
            if (!temp.contains("timetable__except")){train.daily=temp.split(">")[1].split("</")[0];train.changes="";}
            else
            {//changes
                exp.setPattern("b-timetable__except\">.[^<]+</span");
                exp.indexIn(temp);
                train.changes=exp.cap(0).split("\">")[1].split("</")[0];
                train.daily=temp.right(temp.count()-temp.indexOf(">")-1).split("<br")[0];
                qDebug()<<"changes: "<<train.changes;
            }
            train.daily=train.daily.left(1).toUpper()+train.daily.right(train.daily.count()-1);
            qDebug()<<train.daily;
        }
        QTime cdate=QTime::currentTime();
        QTime tdate;
        tdate.setHMS(train.time.split(":")[0].toInt(),train.time.split(":")[1].toInt(),0);
       // modelData.append(train.time+" "+train.daily+"***"+train.from+"***"+train.to+"***"+train.changes);
        if (tdate>cdate){modelData.append(train.time+" "+train.daily+"***"+train.from+"***"+train.to+"***"+train.changes);}
        else {hiddenTrains+=1;}
        trains.append(train);
    }
    if (modelData.count()==0&&hiddenTrains==0)
    {
        setUIText(QString::fromUtf8("Нет электричек с этой станции"));
    }
    if (modelData.count()==0&&hiddenTrains>0){ShowLongList(1);}
    emit setTrainListState(ETrainsListLoaded);
    viewer.rootContext()->setContextProperty("trainsModel",modelData);

}

void Timetable::GoToDirection(int dir)
{
    qDebug()<<"GoToDirection";
    if (dir!=iStation.currentDirection)
    {
    emit setTrainListState(ETrainsListLoading);
    trains.clear();
    modelData.clear();
    viewer.rootContext()->setContextProperty("trainsModel",modelData);
    qDebug()<<"GoToDirection "<<dir;
    QString url=iStation.url+"&direction="+iStation.directions[dir];
    QDate date=QDate::currentDate();
    int day=date.dayOfYear();
    QFile file(TIMETABLE_CACHE_FOLDER+iStation.id+"-"+QString::number(day)+"-"+iStation.directions[dir]+".html");
    if (file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QByteArray bytes=file.readAll();
        QString data=QString::fromUtf8(bytes);
        parseTrainList(data);
    }
    else
    {
        QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
        QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
        qDebug()<<url;
        iHTTP->get(QNetworkRequest(url));
    }
    }
}

void Timetable::getTrainsToStation(QString to)
{
    qDebug()<<"getTrainsToStation "<<to;
    emit setTrainListState(ETrainsListLoading);
    emit setTrainListState(ETrainsToStation);
    to=to[0].toUpper()+to.right(to.count()-1);
    setUIText(iStation.name+" - "+to);
    modelData.clear();
    viewer.rootContext()->setContextProperty("trainsModel",modelData);
    QString surl;
    QByteArray u8_id=QTextCodec::codecForName("UTF-8")->fromUnicode("s"+iStation.id);
    u8_id.replace("%","");
    QByteArray u8_to=QTextCodec::codecForName("UTF-8")->fromUnicode(to);
    u8_to.replace("%","");
    surl.sprintf(URL_GET_TRAINS_TO_STATION,u8_id.constData(),u8_to.constData());
    QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainsToStation(QNetworkReply*)));
    qDebug()<<surl;
    QUrl url(surl);
    iHTTP->get(QNetworkRequest(url));
}

void Timetable::GotTrainsToStation(QNetworkReply *reply)
{
    qDebug()<<"GotTrainsToStation";
    QByteArray u8=reply->readAll();
    QString data=QString::fromUtf8(u8);
    QFile file("2.html");
    file.open(QIODevice::WriteOnly);
    file.write(u8);
    file.close();
    if (data.contains("b-precise-list__place")){parseSeveralDestinations(data);return;}
    QStringList list=data.split("b-timetable__tripname");
    list.removeAt(0);
    qDebug()<<list.count()<<" trains from station";
    int pos=0;
    QRegExp exp;
    for (int i=0;i<list.count();i++)
    {
        TrainToStation train;
        exp.setPattern("/thread/.[^>]+>");
        exp.indexIn(list[i]);
        train.url="http://rasp.yandex.ru"+exp.capturedTexts()[0].split('"')[0];
        qDebug()<<train.url;
/*
        exp.setPattern("g-nowrap.[^<]+</");
        pos = 0;
        QStringList fromto;
        while((pos = exp.indexIn(list[i], pos)) != -1)
        {
            fromto<<exp.cap(0);
            pos += exp.matchedLength();
        }
        train.from=fromto[0].split(">")[1].split("<")[0];
        train.to=fromto[1].split(">")[1].split("<")[0];
        qDebug()<<train.from;
        qDebug()<<train.to;
        */
        QString fromto=list[i].split("station_from="+iStation.id+"\">")[1].split("</a>")[0];
        QRegExp rem("<.[^<>]+>");
        fromto=fromto.replace(rem,"");
        fromto.replace(QRegExp(".[0-9]{3,5} "),"");
        train.from=fromto.split(QString::fromUtf8("—"))[0];
        train.to=fromto.split(QString::fromUtf8("—"))[1];
        qDebug()<<train.from;
        qDebug()<<train.to;
        exp.setPattern("i-time[^/]+</");
        pos = 0;
        int j=1;
        while((pos = exp.indexIn(list[i], pos)) != -1)
        {
            if (j%2==1){train.sendTime=exp.cap(0).split("<strong>")[1].split("<")[0];}
            else {train.arriveTime=exp.cap(0).split("<strong>")[1].split("<")[0];}
            pos += exp.matchedLength();
            j++;
        }
         // time in path
        QTime time1,time2;
        QStringList t1=train.sendTime.split(":");
        QStringList t2=train.arriveTime.split(":");
        time1.setHMS(t1[0].toInt(),t1[1].toInt(),0);
        time2.setHMS(t2[0].toInt(),t2[1].toInt(),0);
        int secs=time1.secsTo(time2);
        int mins=secs/60;
        int hours=(mins/60);
        mins=mins-(hours*60);
        qDebug()<<hours<<mins<<secs;
        train.duringTime.clear();
        train.duringTime=" (";
        if (hours!=0){train.duringTime.append(QString::fromUtf8("%1 час.").arg(hours));}
        if (mins!=0){train.duringTime.append(QString::fromUtf8("%1 мин").arg(mins));}
        train.duringTime.append(")");

        modelData.append(train.sendTime+" - "+train.arriveTime+" "+train.duringTime+"***"+train.from+"***"+train.to+"***");
        trainsToStation.append(train);
    }

    viewer.rootContext()->setContextProperty("trainsModel",modelData);
    emit setTrainListState(ETrainsListLoadedToStation);
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainsToStation(QNetworkReply*)));
}

void Timetable::backToStation()
{
    qDebug()<<"backToStation";
    modelData.clear();
    for (int i=0;i<trains.count();i++)
    {
        Train train=trains[i];
        QTime cdate=QTime::currentTime();
        QTime tdate;
        qDebug()<<iPrevState;
        tdate.setHMS(train.time.split(":")[0].toInt(),train.time.split(":")[1].toInt(),0);
        if (tdate>cdate||iPrevState==ETrainsListLoadedLong){modelData.append(train.time+" "+train.daily+"***"+train.from+"***"+train.to+"***"+train.changes);}
    }
    setTrainListState(iPrevState);
    emit setUIText(iStation.name);
    viewer.rootContext()->setContextProperty("trainsModel",modelData);
}

void Timetable::itemClicked(int index)
{
    if (iState!=ETrainsListLoadedToStation)
    {
    qDebug()<<"trains count"<<trains.count();
    index=index+hiddenTrains;
    qDebug()<<"itemClicked "<<index<<" (not to station)";
    emit setTrainListState(ETrainsListLoading);
    setUIText(trains[index].time+" "+trains[index].from+" - "+trains[index].to);
    stationsModel.clear();
    viewer.rootContext()->setContextProperty("stationsModel",stationsModel);
    QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainInfo(QNetworkReply*)));
    iHTTP->get(QNetworkRequest(trains[index].url));
    }
    else
    {
    qDebug()<<"itemClicked "<<index<<" (to station)";
    emit setTrainListState(ETrainsListLoading);
    emit setTrainListState(ETrainInfo);
    setUIText(trainsToStation[index].sendTime+" "+trainsToStation[index].from+" - "+trainsToStation[index].to);
    stationsModel.clear();
    viewer.rootContext()->setContextProperty("stationsModel",stationsModel);
    QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainInfo(QNetworkReply*)));
    iHTTP->get(QNetworkRequest(trainsToStation[index].url));
    }
}

void Timetable::GotTrainInfo(QNetworkReply *reply)
{
   qDebug()<<"GotTrainInfo";
   QByteArray bytes=reply->readAll();
   QString data=QString::fromUtf8(bytes);
   qDebug()<<"GotTrainInfo"<<data.count();
   QStringList list=data.split("b-timetable__row");
   list.removeAt(0);
   list.removeAt(0);
   list.removeAt(list.count()-2);
   list.removeAt(list.count()-2);
   list[list.count()-1]=list[list.count()-1].split("</tr>")[0];
   qDebug()<<list.count()<<" stations";
   trainStations.clear();
   QRegExp exp;
   for (int i=0;i<list.count();i++)
   {
       StationTrainInfo station;
       exp.setPattern("/station/.[^<]+<");
       exp.indexIn(list[i]);
       if (exp.cap(0).count()>0){station.name=exp.cap(0).split(">")[1].split("<")[0];}
       else {continue;}
       station.name.replace("&nbsp;"," ");
       qDebug()<<station.name;


       exp.setPattern("<strong>.[^<]+</s");
       exp.indexIn(list[i]);
       if (exp.cap(0).count()>0){station.time=exp.cap(0).split(">")[1].split("<")[0];}
       else {station.time=QString::fromUtf8("Без остановки");}
       qDebug()<<station.time;
       stationsModel.append(station.time+"***"+station.name);
   }
   emit setTrainListState(ETrainInfo);
   emit setTrainListState(ETrainsListLoaded);
   QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainList(QNetworkReply*)));
   QObject::disconnect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(GotTrainInfo(QNetworkReply*)));
   viewer.rootContext()->setContextProperty("stationsModel",stationsModel);

}

void Timetable::ShowLongList(int aShow)
{
    if (aShow){setTrainListState(ETrainsListLoadedLong);}
    else {setTrainListState(ETrainsListLoaded);}
    qDebug()<<"ShowLongList"<<aShow;
    modelData.clear();
    for (int i=0;i<trains.count();i++)
    {
        Train train=trains[i];
        QTime cdate=QTime::currentTime();
        QTime tdate;
        tdate.setHMS(train.time.split(":")[0].toInt(),train.time.split(":")[1].toInt(),0);
        if (tdate>cdate||aShow){modelData.append(train.time+" "+train.daily+"***"+train.from+"***"+train.to+"***"+train.changes);}
        else {hiddenTrains+=1;}
    }
    if (aShow){hiddenTrains=0;}
    viewer.rootContext()->setContextProperty("trainsModel",modelData);
}

void Timetable::storeListState(int state)
{
qDebug()<<"state changed "<<state;
if (iState!=ETrainsListLoading&&iState!=ETrainInfo)iPrevState=iState;
iState=state;

}

void Timetable::parseSeveralDestinations(QString data)
{

    data=data.split("l-precise__column_display_inline")[2];
    QRegExp exp;
    qDebug()<<"Parsing data, length "<<data.count();
    //qDebug()<<data;
    exp.setPattern("toName.[^<]+<");
      int pos = 0;
      int plpos=0;
      QStringList list;
      QStringList places;
      while((pos = exp.indexIn(data, pos)) != -1)
      {
        list << exp.cap(0);
        pos += exp.matchedLength();
        if (data.right(data.count()-pos).contains("b-precise-list__place"))
        {
            QRegExp expPl("\\(.[^\\)]+\\)");
            plpos=expPl.indexIn(data, pos);
            places<<expPl.cap(0);
        }
      }
      qDebug()<<places;
      DestinationInfo info;
      multipleDestinations.clear();
      QStringList modelData;
      QString modelStr;
      qDebug()<<list;
      for (int i=0;i<list.count();i++)
      {
          list[i]=list[i].replace("&nbsp;"," ").replace("&amp;","&");
          list[i]=list[i].left(list[i].count()-1);
          if (places.count()>0){info.region=places[i];}
          info.name=list[i].split("\">")[1];
          info.url="http://rasp.yandex.ru/search/?"+list[i].split("\">")[0];
          qDebug()<<info.url;
          qDebug()<<info.name;
          qDebug()<<info.region;
          multipleDestinations.append(info);
          modelStr=info.name+" "+info.region;
          modelData.append(modelStr);
      }
      viewer.rootContext()->setContextProperty("multipleDestinations",modelData);
      emit showDestinationDialog();
      emit setTrainListState(ETrainsListLoadedToStation);
}

void Timetable::destinationSelected(int index)
{
if (multipleDestinations.count()==0||index<0){return;}
qDebug()<<"destinationSelected"<<index;
emit setTrainListState(ETrainsListLoading);
emit setTrainListState(ETrainsToStation);
iHTTP->get(QNetworkRequest(multipleDestinations[index].url));
}

