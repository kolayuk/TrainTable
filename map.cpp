#include "map.h"
#include <QDebug>
#include <QDeclarativeContext>
#include <QNetworkReply>
#include <QFile>

Map::Map(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent),viewer(v)
{
    LoadDic();
    iHTTP = new QNetworkAccessManager(this);
    QObject::connect(iHTTP, SIGNAL(finished(QNetworkReply*)), this, SLOT(routeLoaded(QNetworkReply*)));
}

void Map::loadMap(double long1, double lat1, double long2,double lat2)
{
    qDebug()<<"load map";
    viewer.rootContext()->setContextProperty("maperror",QString::fromUtf8("Загрузка карты"));
    QString u;
#ifndef Q_OS_SYMBIAN
    Lat1=lat1; Lat2=lat2; Long1=long1;Long2=long2;
    u.sprintf(URL_FIND_ROUTE,lat1,long1,lat2,long2);
#else
    Lat1=long1; Lat2=lat2; Long1=lat1;Long2=long2;
    u.sprintf(URL_FIND_ROUTE,long1,lat1,lat2,long2);
#endif
    qDebug()<<u;
    QUrl url(u);
    iHTTP->get(QNetworkRequest(url));
}

void Map::routeLoaded(QNetworkReply *reply)
{
    qDebug()<<"routeLoaded";
    if (reply->error()!=QNetworkReply::NoError){viewer.rootContext()->setContextProperty("maperror",QString::fromUtf8("Ошибка сети"));}
    QByteArray arr=reply->readAll();
    QString data=QString::fromUtf8(arr);
    qDebug()<<"length "<<data.count();
    QString status=data.split("<status>")[1].split("</status>")[0];
    if (status=="ZERO_RESULTS"){viewer.rootContext()->setContextProperty("maperror",QString::fromUtf8("Невозможно проложить маршрут"));}
    else if (status=="MAX_WAYPOINTS_EXCEEDED"){viewer.rootContext()->setContextProperty("maperror",QString::fromUtf8("Слишком длинный маршрут"));}
    else if (status!="OK"){viewer.rootContext()->setContextProperty("maperror",QString::fromUtf8("Неизвестная ошибка"));}
    if (status!="OK"){return;}
    data=data.split("<start_address>")[0];

    QStringList longs,lats;
    QRegExp exp;
    exp.setPattern("<lat>.[^<>]+</lat>");
    int pos = 0;
    QString temp;
    while((pos = exp.indexIn(data, pos)) != -1)
    {
        temp=exp.cap(0);
        lats<<temp.replace("<lat>","").replace("</lat>","");
        pos += exp.matchedLength();
    }

    exp.setPattern("<lng>.[^<>]+</lng>");
    pos = 0;
    while((pos = exp.indexIn(data, pos)) != -1)
    {
        temp=exp.cap(0);
        longs<<temp.replace("<lng>","").replace("</lng>","");
        pos += exp.matchedLength();
    }
    lats.removeAt(lats.count()-1);
    lats.removeAt(lats.count()-1);
    longs.removeAt(longs.count()-1);
    longs.removeAt(longs.count()-1);
    qDebug()<<lats;
    qDebug()<<longs;
    data=replace(data);

    QString route;
    exp.setPattern("<html_instructions>.[^<>]+</html_instructions>");
    pos = 0;
    while((pos = exp.indexIn(data, pos)) != -1)
    {
        temp=exp.cap(0);
        route=route+temp.replace("<html_instructions>","").replace("</html_instructions>","")+"\n";
        pos += exp.matchedLength();
    }
    qDebug()<<route;
    viewer.rootContext()->setContextProperty("routetxt",route);
    QString url;
    url.sprintf(URL_REQUEST_MAP,Lat1,Long1,Lat2,Long2);
    for (int i=1;i<lats.count();i++)
    {
        url=url+lats[i]+","+longs[i]+"|";
    }
    url=url.left(url.count()-1);
    emit routeParsed(route,url);
    qDebug()<<url;
    viewer.rootContext()->setContextProperty("mapurl",url);
}

void Map::LoadDic()
{
     QFile file(FILE_TRANSLATE);
     QString line;
     if (file.open (QIODevice::ReadOnly))
     {
         QTextStream stream ( &file );
         stream.setCodec("UTF-8");
         while( !stream.atEnd())
         {
              line=stream.readLine();
              if (line.contains("-")) dic.insert(line.split(" - ")[0],line.split(" - ")[1]);
         }
         file.close();
     }
}

QString Map::replace(QString data)
{
    data.replace("&lt;","<").replace("&gt;",">").replace("&quot;","\"");
    data.replace("<b>","").replace("</b>","");
    data.replace("<div style=\"font-size:0.9em\">","").replace("</div>","");
    qDebug()<<dic.count();
    for (int i=0;i<dic.count();i++)
    {
        data.replace(dic.keys()[i],dic.values()[i]);
        //qDebug()<<data;
    }
    return data;
}
