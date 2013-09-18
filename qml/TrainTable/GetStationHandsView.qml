import QtQuick 1.0
import com.nokia.symbian 1.0
Rectangle {
    id: root;
    anchors.fill: parent
    color: "transparent"
    property string txt: "Последние станции:"
    property Item list: Item{}
    property int listtype:1
    property bool txtfocus:txtfield.focus
    onTxtfocusChanged: {view.focus=true;txtfield.focus=txtfocus;}
    Connections{
        target: getstation;
        onStationRecieved:{}
        onUnableToGetStation:{txt=reason;busy.running=false;busy.visible=false;}
        onSetListType: {
            listtype=type;
            if (type==1){txt="Последние станции:";busy.running=false;busy.visible=false;}
            else if (type==0){txt="Результаты поиска:";busy.running=false;busy.visible=false;}
            else if (type==2){txt="Идет поиск...";busy.running=true;busy.visible=true;}
            else if (type==3){root.list.currentIndex=1;txt="Несколько одинаковых станций:";busy.running=false;busy.visible=false;}
        }
        onGotoTimeTable:{txtfield.focus=false;}
    }
    BusyIndicator {
         id: busy
         width: 100
         height: 100
         visible: false;
         anchors.horizontalCenter: parent.horizontalCenter;
         anchors.verticalCenter:parent.verticalCenter;
         }
    TextField{
        id:txtfield;
        placeholderText: "Введите город или станцию"
        x:0
        y:0
        width:parent.width-sbtn.width-20;
        height:50;

        onFocusChanged: {
            console.log("focus changed");
            if (focus==true){
                application.EnableSplitScreen();
            }
        }

        /*
        MouseArea{
            anchors.fill: parent
            onClicked: {
                txtfield.focus = true;
                txtfield.openSoftwareInputPanel();
            }
        }
        */
        }

    Button{
        id:sbtn;
        x:parent.width-width-10;
        iconSource: "search.png"
        width: height;
        y:0;height: 50;
        onClicked: {forceActiveFocus(); getstation.GetStationID(txtfield.text);}
    }
    Component {
         id: listHeader

         ListHeading {
             id: listHeading

             ListItemText {
                 id: headingText
                 anchors.fill: listHeading.paddingItem
                 role: "Heading"
                 text: txt
             }
         }
     }

    Component {
        id: listDelegate

        ListItem {
            id: listItem
            subItemIndicator:true
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
                }
            }
            onClicked: {forceActiveFocus();getstation.listViewPressed(index);}
        }
    }

     ListView {
         id: listView
         x:0;y:60;

         width: parent.width;
         height: parent.height-60;
         clip: true;
         header: listHeader
         delegate: listDelegate;
         model: stringsModel;
     }
}
