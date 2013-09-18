#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <qmlapplicationviewer.h>
#include <QNetworkAccessManager>
#include "const.h"
#include <QHash>
class Map : public QObject
{
    Q_OBJECT
    QmlApplicationViewer& viewer;
    QNetworkAccessManager* iHTTP;
    void LoadDic();
    QHash<QString,QString> dic;
    QString replace(QString);
    double Lat1,Lat2;
    double Long1,Long2;
public:
    explicit Map(QmlApplicationViewer& v,QObject *parent = 0);

signals:
    void Error(QString text);
    void routeParsed(QString route,QString url);
public slots:
    void loadMap(double long1,double lat1,double long2,double lat2);
    void routeLoaded(QNetworkReply*);
};

#endif // MAP_H
