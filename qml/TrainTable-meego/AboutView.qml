import QtQuick 1.0
import com.nokia.meego 1.0
Rectangle {
    anchors.fill: parent
    color:"darkgrey"
    signal back();
    Column{
        anchors.fill: parent
        anchors.topMargin: statusBar.height+10
        spacing: 20;
        Image {
            id: logo
            anchors.horizontalCenter: parent.horizontalCenter;
            source: "logo.png"
            y:0
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "Расписание электричек v.1.1";
            font.pixelSize: 20;
            font.bold: true
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "Разработчик: Усанов-Корнилов Николай";
            font.pixelSize: 16;
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "E-Mail: kolayuk@gmail.com";
            font.pixelSize: 16;
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter;
            Text {
                text: "Web: "
                font.pixelSize: 16;
            }
            Text{
                font.pixelSize: 16;
                text: "http://kolaysoft.ru/"
                font.underline: true;
                color: "blue"
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {Qt.openUrlExternally("http://kolaysoft.ru/");}
                }
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter;
            Text {
                text: "Twitter: "
                font.pixelSize: 16;
            }
            Text{
                font.pixelSize: 16;
                text: "@kolayuk"
                font.underline: true;
                color: "blue"
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {Qt.openUrlExternally("http://twitter.com/#!/kolayuk");}
                }
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter;
            Text {
                id: icon
                text: "Иконка: "
                font.pixelSize: 16;
            }
            Text{
                id:icon_twitter
                font.pixelSize: 16;
                text: "@boroda1"
                font.underline: true;
                color: "blue"
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {Qt.openUrlExternally("http://twitter.com/#!/boroda1");}
                }
            }
        }


        Text {
            id: name
            text: "Расписание предоставлено:"
            font.pixelSize: 16;
            anchors.horizontalCenter: parent.horizontalCenter;
        }
        Image{
            id:ya_logo;
            source: "yandex.png"
            anchors.horizontalCenter: parent.horizontalCenter;
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
            }
        }
    StatusBar {
        id: statusBar
        y:0
    }
}
