import QtQuick 1.0

import com.nokia.meego 1.0


Rectangle {
    color: "transparent"
    anchors.fill:  parent
    signal back();
    signal about();
    id: root;
    Connections{
        target: map;
        onRouteParsed:{txt.text=route;im.source=url;statustxt.text="Загрузка карты";}
        onError:{statustxt.text=text;}
    }
    BusyIndicator{
        id:busy;
        running: visible
        visible: true;
        width: 100
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter;
        y:txt.y-height-20;
    }

    Text {
        anchors.centerIn: parent
        id: statustxt;
        width: parent.width
        color:"white"
        anchors.margins: 30
        horizontalAlignment: Text.AlignHCenter;
        font.pixelSize: 16;
        wrapMode: Text.WordWrap;
        verticalAlignment: Text.AlignVCenter;
        text: maperror
    }

    Flickable {
       id: m
       visible: true
       x:0;y:0
       height: parent.height*(2/3);
       width: parent.width;
       contentWidth: im.width
       contentHeight: im.height
       flickableDirection: Flickable.HorizontalAndVerticalFlick;
       clip: true
       Image {
           id: im
           source: mapurl
           fillMode: Image.PreserveAspectCrop
           onStatusChanged: if (im.status == Image.Ready) {busy.visible=false;statustxt.visible=false;}
       }
      }
    Flickable {
       id: route
       visible: true
       x:0;y:parent.height*(2/3)+20;
       height: parent.height*(1/3)-80;
       width: parent.width;
       contentWidth: txt.width
       contentHeight: txt.height
       flickableDirection: Flickable.VerticalFlick;
       clip: true
       Text {
           id: txt
           y:00;x:0;
           width: root.width
           text: routetxt
           color:"white";
           font.pixelSize: 18;
           horizontalAlignment: Text.AlignJustify
           verticalAlignment: Text.AlignVCenter
           wrapMode: Text.WordWrap
       }
      }

    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            id: toolBarLayout

            ToolButton {
                flat: true
                id:backbtn;
                iconSource: "toolbar-back.png"
                onClicked: {
                    back();
                }
            }
            ToolButton {
                flat: true
                iconSource: "toolbar-menu.png"
                onClicked: {
                    about();
                    }
                }
            }
        }
    StatusBar {
        id: statusBar
        y:0
        x:0
    }
}
