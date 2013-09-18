import QtQuick 1.0

import com.nokia.symbian 1.0


Rectangle {
    color: "transparent"
    anchors.fill:  parent
    signal back();
    signal about();
    id: root;
    property int from:0;
    property Item win: Item{}
    property string do_on_back:"back";
    Connections{
        target: trainlist;
        onSetBackToHideTxtField:root.do_on_back="hide txtfield";
        onSetBackToTrainsFromStation:{root.do_on_back="back to trains from station"}
    }

    VisualItemModel {
        id: itemModel
        Rectangle{
            width: view.width; height: view.height
            color:  "black"
            TrainListView{
                id:trainlist;
                list: view
            }

        }
        Rectangle{
            width: view.width; height: view.height
            color:  "black"
            TrainInfoView{
                id:info
            }

        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: toolBar.height;topMargin:statusBar.height; }
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem;
        cacheBuffer: 200
        highlightMoveSpeed: 800;
        onCurrentIndexChanged:
        {

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
                    if (root.do_on_back=="back")
                    {
                    if (view.currentIndex==0){back();}
                    else if (view.currentIndex==1){timetable.backToStation();view.currentIndex=0;}
                    }
                    else if (root.do_on_back=="hide txtfield")
                    {
                        root.do_on_back="back"
                        trainlist.upmode=0;
                    }
                    else if (root.do_on_back=="back to trains from station")
                    {
                        root.do_on_back="back"
                        trainlist.upmode=0;
                        timetable.backToStation();
                        view.currentIndex=0;
                    }
                }
            }
            ToolButton {
                flat: true
                visible:view.currentIndex==0&&trainlist.upmode==0;
                text: trainlist.liststate==5?"":"..."
                iconSource: trainlist.liststate==5?"up.png":""
                onClicked: {
                    timetable.ShowLongList(trainlist.liststate!=5);
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
        anchors.top: parent.win.top
    }
}
