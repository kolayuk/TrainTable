import QtQuick 1.0
import com.nokia.meego 1.0


Rectangle{

    id: root;
    anchors.fill: parent
    color: "transparent"
    property Item list: Item{}
    property bool loading:  true;
    property Item text: txt;
    property Timer mytimer: timer;
    Timer{
        property int ticks: 0;
        id: timer;
        interval: 1000;
        running: true;
        repeat: true;
        onTriggered: {
            ticks=ticks+1;
            timertxt.text=ticks.toString();
        }
    }

    Connections{
        target: getstation;
        onCoordinatesChanged:{txt.text="Ваши координаты:\n "+latitude+" "+longitude+"\nОпределение ближайшей станции...";timer.stop(); timertxt.visible=false;}
        onTimeouted:{
            txt.text="Невозможно определить местоположение, выберите станцию вручную";timer.stop(); getstation.StopPosSearch(); indicator2.visible=false;
        }
        onStationRecieved:{
            txt.text+="\nБлижайшая станция: "+name; loading=false;
            upanim.start();
            contbtn.visible=true;
            mapbtn.visible=true;
        }
        onUnableToGetStation:{
            txt.text+="\nОшибка: "+reason;
            loading=false;
            indicator2.visible=false;
        }
        onNeedToIncRadius:{
            incradanim.start();
            loading=true;
        }
        onSetListType:{
            //if (type==3){root.list.currentIndex=1;}
        }

    }
    BusyIndicator {
         id: indicator2
         running: visible
         visible: parent.loading
         width: 100
         height: 100
         anchors.horizontalCenter: parent.horizontalCenter;
         y:txt.y-height-20;
         }
        Text{
            id: timertxt;
            visible: indicator2.visible
            anchors.centerIn: indicator2
            text: "";
            color:"white"
            font.pixelSize: indicator2.height*(1/2)
        }

        Text {
            anchors.centerIn: parent
            id: txt;
            width: parent.width
            color:"white"
            anchors.margins: 30
            horizontalAlignment: Text.AlignHCenter;
            font.pixelSize: 16;
            wrapMode: Text.WordWrap;
            verticalAlignment: Text.AlignVCenter;
            text: "Определение местоположения..."
        }
        ParallelAnimation{
            id:upanim;
            NumberAnimation { target: contbtn; property: "anchors.bottomMargin"; to: 130; duration: 1000 }
            NumberAnimation { target: mapbtn; property: "anchors.bottomMargin"; to: 70; duration: 500 }
        }
        /*
        NumberAnimation {id:incradanim; target: incradbtn; property: "anchors.bottomMargin"; to: 70; duration: 500 }
        Button{
        id: incradbtn
        text: "Увеличить радиус поиска";
        anchors.bottom: parent.bottom;

        height: 50;
        anchors.leftMargin: 5;
        anchors.rightMargin: 5;
        anchors.bottomMargin: 10;
        x:10;width: parent.list.width-20;
        onClicked: {
            getstation.incRadius();
            }
        }
        */
        Button{
        id: contbtn
        text: "Продолжить";
        visible: false;
        anchors.bottom: parent.bottom;
        height: 50;
        x:10;width: parent.list.width-20;
        anchors.bottomMargin: 10;
        onClicked: {
            getstation.SendGotoTimeTable();
        }
        }
        Button{
        id: mapbtn
        text: "Карта";
        anchors.bottom: parent.bottom;
        height: 50;
        anchors.leftMargin: 5;
        anchors.rightMargin: 5;
        anchors.bottomMargin: 10;
        x:10;width: parent.list.width-20;
        onClicked: {
            getstation.requestMap();
            }
        }
        Button{
        id: handsbtn
        text: "Выбрать вручную";
        anchors.bottom: parent.bottom;
        height: 50;
        anchors.leftMargin: 5;
        anchors.rightMargin: 5;
        anchors.bottomMargin: 10;
        x:10;width: parent.list.width-20;
        onClicked: {
            parent.list.currentIndex=1;
            }
        }
}
