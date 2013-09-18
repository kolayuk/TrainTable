 # Add more folders to ship with the application, here
folder_01.source = qml/TrainTable
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

folder_02.source = qml/TrainTable-meego
folder_02.target = qml
DEPLOYMENTFOLDERS += folder_02

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

CONFIG += qt-components

symbian:DEPLOYMENT.installer_header = "$${LITERAL_HASH}{\"TrainTable\"},(0x2002CCCF),1,2,0"
packageheader = "$${LITERAL_HASH}{\"TrainTable\"}, (0x2004B2E1), 1, 2, 0, TYPE=SA"
info.pkg_prerules=packageheader
symbian:DEPLOYMENT+=info

qt_components.pkg_prerules += "(0x200346DE), 1, 0, 0, {\"Qt Components\"}"
symbian:DEPLOYMENT += qt_components

vendorinfo =  "%{\"KolaySoft\"}" \
    ":\"KolaySoft\""
vendor.pkg_prerules = vendorinfo
symbian:DEPLOYMENT += vendor

symbian {
TARGET.CAPABILITY+=NetworkServices Location ReadUserData WriteUserData SwEvent
TARGET.UID3 = 0x2004B2E1
#TARGET.EPOCSTACKSIZE = 0xf000
#TARGET.EPOCHEAPSIZE = 0x19000 0x1000000000
LIBS += -lcone -lws32 -lavkon -leikctl -leikcoctl -luiklaf -lform -lfepbase -lalarmshared -lalarmclient
ICON=TrainTable.svg
}
meego:ICON=TrainTable_MeeGo_Launcher_80x80.png

 CONFIG += mobility
 QT += network
 MOBILITY += location

SOURCES += main.cpp \
    application.cpp \
    stationgetter.cpp \
    timetable.cpp \
    map.cpp
HEADERS += \
    application.h \
    const.h \
    stationgetter.h \
    timetable.h \
    map.h
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    promo.txt \
    dic.txt














