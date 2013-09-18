#include "application.h"
#include <QDeclarativeContext>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "const.h"

#ifdef Q_OS_SYMBIAN
    #include <aknedsts.h>
    #include <coeaui.h>
    #include <coemain.h>
    #include <w32std.h>
    #define EAknEditorFlagEnablePartialScreen 0x200000
    #include <asclisession.h>
    #include <asshdalarm.h>
    const TUid KAlarmClockOne = { 0x101F793A };
#endif

Application::Application(QmlApplicationViewer& v,QObject *parent) :
    QObject(parent),viewer(v)
{
    stGetter=new StationGetter(v,this);
    table=new Timetable(v,this);
    map=new Map(v,this);
    connect(stGetter,SIGNAL(gotoTimeTable(QString,QString,bool)),table,SLOT(setStation(QString,QString)));
    connect(stGetter,SIGNAL(showMap(double,double,double,double)),map,SLOT(loadMap(double,double,double,double)));
}

void Application::EnableSplitScreen()
{
    qDebug()<<"Application::EnableSplitScreen";
#ifdef Q_OS_SYMBIAN
    MCoeFepAwareTextEditor *fte = CCoeEnv::Static()->AppUi()->InputCapabilities().FepAwareTextEditor();

    // FepAwareTextEditor() returns 0 if no text editor is present
    if (fte)
    {
        CAknEdwinState *state = STATIC_CAST(CAknEdwinState*, fte->Extension1()->State(KNullUid));
        state->SetFlags(state->Flags() | EAknEditorFlagEnablePartialScreen);
    }
#endif
}

QStringList Application::LoadPromoBanners()
{
    QFile file(PROMO_FILE);
    file.open(QIODevice::ReadOnly);
    QString data=QString::fromUtf8(file.readAll());
    data=data.replace("\n","").replace("\r","");
    file.close();
    return data.split("***");

}

void Application::SetAlarm(QString time)
{
#ifdef Q_OS_SYMBIAN
    if (!time.contains(":")){return;}
    RASCliSession session;
    session.Connect();
    TASShdAlarm alarm=TASShdAlarm();
    alarm.RepeatDefinition() = EAlarmRepeatDefintionRepeatOnce;
    alarm.Category()=KAlarmClockOne;
    TDateTime dt;
    QDate d=QDate::currentDate();
    QTime qtime=QTime::currentTime();
    int day=d.day()-1;
    if (qtime.hour()>time.split(":")[0].toInt()){day=day+1;}
    dt.Set(d.year(),((TMonth)(d.month()-1)),day,time.split(":")[0].toInt(),time.split(":")[1].toInt(),0,0);
    TTime t(dt);
    t=t-TTimeIntervalMinutes(5);
    alarm.NextDueTime()=t;
    session.AlarmAdd( alarm );
    session.Close();
#endif

}
