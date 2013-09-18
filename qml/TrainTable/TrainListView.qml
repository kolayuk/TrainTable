import QtQuick 1.0
import com.nokia.symbian 1.0
Rectangle {
    id: root;
    anchors.fill: parent
    color: "transparent"
    property string txt:"Идет загрузка..."
    property Item list: Item{}
    property int upmode:0;
    property int liststate:0
    onUpmodeChanged: {
        if (upmode==0){selectionDialog.selectedIndex=currentDirection;}
    }

    signal setBackToHideTxtField();
    signal setBackToTrainsFromStation();
    Connections{
        target: timetable;
        onSetUIText:{root.txt=txt;}
        onSetCurrentDirection:{selectionDialog.selectedIndex=dir;}
        onShowDestinationDialog:{destinations.open();}
        onSetTrainListState:{
            if (state==0){/*ads.num=ads.random(0,4); ads.visible=true;*/}
            else if (state==1){busy.visible=true;busy.running=true;}
            else if (state==2||state==6||state==4){busy.visible=false;busy.running=false;}
            else if (state==3){setBackToTrainsFromStation();}
            root.liststate=state;
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
            subItemIndicator:true
            height: c.height
            property string first:String(modelData).split("***")[0];
            property string second:String(modelData).split("***")[1];
            property string trird:String(modelData).split("***")[2];
            property string four:String(modelData).split("***")[3];
            Column {
                    width: listItem.implicitWidth
                    id:c
                    ListItemText {
                        id: lbl1;
                        mode: listItem.mode
                        role: "Title"
                        text: btn.checked==true?four:first
                        //width: String(modelData).split("***")[3]!=""?parent.width-btn.width:parent.width
                    }

                ListItemText {
                    mode: listItem.mode
                    role: "SubTitle"
                    text: second
                    width: four!=""?parent.width-btn.x:parent.width
                    //y: listItem.paddingItem.height/4-height/2;
                    font.pixelSize: 16;
                }
                ListItemText {
                    id:lbl3;
                    mode: listItem.mode
                    role: "SubTitle"
                    text: trird
                    width: parent.width
                    //y: listItem.paddingItem.height/4-height/2;
                    font.pixelSize: 16;
                }
            }
           Button{
                id:btn;
                opacity: 1
                checkable: true;
                //x: lbl1.width+(view.width-lbl1.width)/2-width/2
                x:view.width-width-30;
                y:4
                visible: four!="";
                text: "Изменения"
                height: parent.height-lbl3.height-(2*y)
                font.pixelSize: 16;
            }
           onClicked: {forceActiveFocus(); root.list.currentIndex=1;timetable.itemClicked(index);}
        }
    }
    TextField{
        id:txtfield;
        visible: root.upmode==0?false:true;
        x:0
        placeholderText: "Станция назначения"
        anchors.verticalCenter: item.verticalCenter;
        width:(3/4)*parent.width;
        height:50;
        /*
        onFocusChanged: {
            if (focus==true){
                application.EnableSplitScreen();
            }
        }
        */
    }
    Button{
        x:(3/4)*parent.width+10;
        iconSource: "search.png"
        anchors.verticalCenter: item.verticalCenter;
        visible: root.upmode==0?false:true;
        width: (1/4)*parent.width-20;
        y:0;height: 50;
        onClicked: {forceActiveFocus();timetable.getTrainsToStation(txtfield.text);}
    }

    SelectionListItem {
        id: item
        visible:root.upmode==0?(directionCount==0?false:true):false
        title: "Куда едем?"
        //height: directionCount!=0?SelectionListItem.paddingItem.height*2:0
        subTitle: selectionDialog.model[selectionDialog.selectedIndex]
        /*
        Timer{
            id:timer;
            interval: 100;
            running: true;
            onTriggered: {selectionDialog.selectedIndex=currentDirection;}
        }
        */
        onClicked: selectionDialog.open()
        SelectionDialog {
            id: selectionDialog
            titleText: "Выберите направление:"
            selectedIndex: currentDirection
            model: directionsModel
            onSelectedIndexChanged: {
                if (selectionDialog.model[selectionDialog.selectedIndex]!="На станцию...")
                    {

                    if (selectionDialog.selectedIndex!=currentDirection){timetable.GoToDirection(selectedIndex);}
                    }
                else
                {
                    setBackToHideTxtField();
                    root.upmode=1;
                }
            }
        }
    }
    SelectionDialog {
            id: destinations
            titleText: "Выберите станцию:"
            selectedIndex: -1
            model: multipleDestinations
            onSelectedIndexChanged: {
                timetable.destinationSelected(selectedIndex);
                selectedIndex=-1;
            }
    }
    ListView {
        visible: true//listsModel.index==pathView.currentIndex?true:false;
        id: listView
        x:0;y:directionCount!=0?item.height:0;

        width: parent.width;
        height: directionCount!=0?parent.height-item.height:parent.height;
        clip: true;

        header: listHeader
        delegate: listDelegate;
        model: trainsModel;
    }
    /*
    AdBanner{
        id: ads;
        //visible: true;
        y:438;
        x:0;
    }
    */

}
