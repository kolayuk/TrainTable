import QtQuick 1.0
import com.nokia.meego 1.0

Rectangle {
    width: 360
    height: 128
    id: root;
    clip:false
    visible: false;
    property int num: random(0,4);
    MouseArea{
        anchors.fill:parent
        onClicked: {Qt.openUrlExternally(String(promoModel[root.num]).split(":::")[3]);root.visible=false;}
    }

    /*
    Text {
        id: other
        text: "Еще...";
        x:root.width-width-20;
        height: 100;
        width: 100;
        y:root.height-height-5;
    }
    */
    function random(min, max)
    {
      //return Math.floor(Math.random() * (max - min + 1)) + min;
      return Math.random() * (max - min) + min;
    }
    Image {
        id: bg
        source: "adbg.png"
        anchors.fill:parent
    }
    function show(){
        root.visible=true;
    }
    Row{
        anchors.fill: parent
        anchors.rightMargin: 100;
        spacing: 20;
        Image {
            id: promoim
            width: height
            x:3
            anchors.top: root.top;
            anchors.bottom: root.bottom;
            y:3;
            height: root.height-6
            source: String(promoModel[root.num]).split(":::")[0];
        }
        Column{
            spacing: 5;
            width: root.width-x;
            Text{
                y:0
                color:"white"
                text: String(promoModel[root.num]).split(":::")[1];
                font.pixelSize: 18;
                font.bold: true;
            }
            Text{
                color:"white"
                width: parent.width
                text: String(promoModel[root.num]).split(":::")[2];
                font.pixelSize: 14;
                font.bold: false;
                wrapMode: Text.WordWrap;
            }

        }
        Timer{
            interval: 5000;
            running: root.visible;
            onTriggered: {root.visible=false;}
        }
    }

}
