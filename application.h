#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <qmlapplicationviewer.h>
#include "stationgetter.h"
#include "timetable.h"
#include "map.h"
class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QmlApplicationViewer& v,QObject *parent = 0);
    StationGetter* stGetter;
    Timetable* table;
    Map* map;
    QmlApplicationViewer& viewer;
    Q_INVOKABLE void EnableSplitScreen();
    Q_INVOKABLE void SetAlarm(QString time);
    QStringList LoadPromoBanners();
};

#endif // APPLICATION_H
