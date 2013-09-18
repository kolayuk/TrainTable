import QtQuick 1.0
import com.nokia.symbian 1.0
Rectangle {
    id: root;
    anchors.fill: parent
    color: "transparent"
    property string txt:"Идет загрузка..."
    property Item list: Item{}
    Connections{
        target: timetable;
        onSetUIText:{root.txt=txt;}
        onSetCurrentDirection:{selectionDialog.selectedIndex=dir;}
        onSetTrainListState:{
            if (state==1){busy.visible=true;busy.running=true;}
            else if (state==2){busy.visible=false;busy.running=false;}
            else if (state==3){setBackToTrainsFromStation();}
        }
    }
    BusyIndicator {
         id: busy
         width: 100
         height: 100
         visible: false;
         anchors.horizontalCenter: parent.horizontalCenter;
         anchors.verticalCenter:parent.verticalCenter;
         }
    Component {
         id: listHeader

         ListHeading {
             id: listHeading

             ListItemText {
                 id: head
                 anchors.fill: listHeading.paddingItem
                 role: "Heading"
                 text: root.txt
             }
         }
     }

    Component {
        id: listDelegate

        ListItem {
            id: listItem
            subItemIndicator:false

            Column {
                anchors.fill: listItem.paddingItem
                    ListItemText {
                        mode: listItem.mode
                        role: "Title"
                        text: String(modelData).split("***")[0]
                        width: parent.width
                    }


                ListItemText {
                    mode: listItem.mode
                    role: "SubTitle"
                    text: String(modelData).split("***")[1]
                    width: parent.width
                    y: listItem.paddingItem.height/4-height/2;
                    font.pixelSize: 16;
                }

            }
            Image {
                id: im
                source: "alarm.png"
                height: listItem.paddingItem.height
                width: height
                x: listItem.paddingItem.width-width
                anchors.verticalCenter: listItem.paddingItem.verticalCenter
                MouseArea{
                    anchors.fill:parent;
                    onClicked: {application.SetAlarm(String(modelData).split("***")[0]);im.source="alarm_on.png"}
                }
            }
        }
    }

    ListView {
        visible: true
        id: listView
        x:0;y:0

        width: parent.width;
        height: parent.height;
        clip: true;

        header: listHeader
        delegate: listDelegate;
        model: stationsModel;
    }
}
