#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QObject>
#include <qmlapplicationviewer.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QList>

struct StationInfo{
    QString url;
    QString name;
    QStringList directions;
    QString id;
    int currentDirection;
};

struct Train{
    QString from;
    QString to;
    QString time;
    QString exceptStations;
    QString daily;
    QString url;
    QString changes;
};
struct TrainToStation{
    QString from;
    QString to;
    QString arriveTime;
    QString sendTime;
    QString duringTime;
    QString url;
    QString changes;
};
struct StationTrainInfo{
    QString time;
    QString name;
};

struct DestinationInfo
{
    QString name;
    QString url;
    QString region;
};

enum{
    ETrainsListOpened=0,
    ETrainsListLoading=1,
    ETrainsListLoaded=2,
    ETrainsToStation=3,
    ETrainInfo=4,
    ETrainsListLoadedLong=5,
    ETrainsListLoadedToStation=6

};

class Timetable : public QObject
{
    Q_OBJECT
    StationInfo iStation;
    QmlApplicationViewer& viewer;
    QNetworkAccessManager* iHTTP;
    QList<Train> trains;
    QList<TrainToStation> trainsToStation;
    QStringList modelData;
    QStringList stationsModel;
    QList<StationTrainInfo> trainStations;
    QList<DestinationInfo> multipleDestinations;
    void parseTrainList(QString);
    int hiddenTrains;
    int iState;
    int iPrevState;
    void parseSeveralDestinations(QString data);
public:
    explicit Timetable(QmlApplicationViewer& v,QObject *parent = 0);
    Q_INVOKABLE void GoToDirection(int dir);
    Q_INVOKABLE void getTrainsToStation(QString to);
    Q_INVOKABLE void backToStation();
    Q_INVOKABLE void itemClicked(int index);
    Q_INVOKABLE void ShowLongList(int aShowOrHide);
    Q_INVOKABLE void destinationSelected(int index);
signals:
    void setTrainListState(int state);
    void setUIText(QString txt);
    void setCurrentDirection(int dir);
    void showDestinationDialog();
public slots:
    void setStation(QString url,QString name);
    void GotTrainList(QNetworkReply*);
    void GotTrainsToStation(QNetworkReply*);
    void GotTrainInfo(QNetworkReply*);
    void storeListState(int state);
};

#endif // TIMETABLE_H
