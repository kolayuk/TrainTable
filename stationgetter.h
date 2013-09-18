#ifndef STATIONGETTER_H
#define STATIONGETTER_H

#include <QObject>
#include <qmlapplicationviewer.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QList>
#ifdef Q_OS_SYMBIAN
#include <qgeopositioninfosource.h>
#include <qgeopositioninfo.h>
QTM_USE_NAMESPACE
#endif

enum {
    ESearchResults=0,
    ECachedItems=1,
    EFinding=2,
    ESeveralNear=3
};
struct Station
{
    QString name;
    QString url;
    double latitude;
    double longitude;
    double dim;
    bool operator<(const Station other) const {
            return dim<other.dim;
        }
};
struct SearchStationInfo
{
    QString name;
    QString url;
    QString region;
};

class StationGetter : public QObject
{
    Q_OBJECT
    QmlApplicationViewer& viewer;
    double iLongitude;
    double iLatitude;
    int iTimer;
    QNetworkAccessManager* iHTTP;
    QList<Station> iStations;
    void parseSeveralSearchResults(QString data);
    bool removeDir(const QString &dirName);
    bool runninggps;
    int radius;
    bool searchingstation;
    bool parseExcludingCity;

#ifdef Q_OS_SYMBIAN
    QGeoPositionInfoSource* iSource;
    QGeoCoordinate iUser;
#endif

#ifndef Q_OS_SYMBIAN
    void timerEvent(QTimerEvent *);
#endif
    bool GPS;
public:
    explicit StationGetter(QmlApplicationViewer& v,QObject *parent = 0);
    Q_INVOKABLE void GetStationID(QString name);
    Q_INVOKABLE void StartPosSearch();
    Q_INVOKABLE void StopPosSearch();
    Q_INVOKABLE void listViewPressed(int index);
    Q_INVOKABLE void SendGotoTimeTable();
    Q_INVOKABLE void GetCachedStations();
    Q_INVOKABLE void clearCache();
    Q_INVOKABLE void incRadius();
    Q_INVOKABLE void requestMap();

    QList<SearchStationInfo> searchResults;
signals:
    void coordinatesChanged(QString longitude,QString latitude);
    void timeouted(QString aType);
    void stationRecieved(QString name,double longitude,double latitude);
    void unableToGetStation(QString reason);
    void setListType(int type);
    void gotoTimeTable(QString url,QString name,bool gps);
    void needToIncRadius();
    void showMap(double l1, double lo1, double l2,double lo2);

public slots:
#ifdef Q_OS_SYMBIAN
    void PosUpdated(QGeoPositionInfo info);
    void TimeoutGPS();
#endif
    void GeoStationFound(QNetworkReply*);
    void StationIDFound(QNetworkReply*);
    void GotSeveralSearshResults(QNetworkReply*);
};

#endif // STATIONGETTER_H
