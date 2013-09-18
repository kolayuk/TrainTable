#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QDeclarativeContext>
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList empty;
    int c=0;
    QCoreApplication::setAttribute(Qt::AA_S60DisablePartialScreenInputMode, false);
    QmlApplicationViewer viewer;
    Application* myapp=new Application(viewer);
    viewer.rootContext()->setContextProperty("application",myapp);
    viewer.rootContext()->setContextProperty("map",myapp->map);
    viewer.rootContext()->setContextProperty("stringsModel",empty);
    viewer.rootContext()->setContextProperty("trainsModel",empty);
    viewer.rootContext()->setContextProperty("directionsModel",empty);
    viewer.rootContext()->setContextProperty("stationsModel",empty);
    viewer.rootContext()->setContextProperty("currentDirection",c);
    viewer.rootContext()->setContextProperty("directionCount",c);
    viewer.rootContext()->setContextProperty("promoModel",myapp->LoadPromoBanners());
    QString str;
    viewer.rootContext()->setContextProperty("routetxt",str);
    viewer.rootContext()->setContextProperty("mapurl",str);
    viewer.rootContext()->setContextProperty("maperror",str);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationLockPortrait); 
    viewer.setMainQmlFile(QLatin1String("qml/TrainTable/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
