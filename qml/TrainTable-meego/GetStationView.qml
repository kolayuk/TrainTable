import QtQuick 1.0
import com.nokia.meego 1.0


Rectangle {
    color: "transparent"
    anchors.fill:  parent
    property Item win: Item{}
    signal about();
    property bool txtfocus:hands.txtfocus
    onTxtfocusChanged: {hands.txtfocus=txtfocus;}
    VisualItemModel {
        id: itemModel
        Rectangle{
            width: view.width; height: view.height
            color:  "transparent"
            GetStationGPSView{
                id: gps;
                list: view;
            }
        }
        Rectangle{
            width: view.width; height: view.height
            color:  "transparent"
            GetStationHandsView{
                id: hands;
                list:view;
            }
        }
    }

    ListView {
        id: view
        anchors { fill: parent; bottomMargin: toolBar.height;topMargin:statusBar.height; }
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Vertical
        snapMode: ListView.SnapOneItem;
        cacheBuffer: 200
        highlightMoveSpeed: 800;
        onCurrentIndexChanged:
        {
            if (currentIndex==0){
                //gps
                view.currentIndex=0;
                gps.loading=true;
                gps.text.text="Определение местоположения..."
                gps.mytimer.start();
                getstation.StartPosSearch();
            }
            else if (currentIndex==1){
                //list
                gps.loading=false;
                if (gps.mytimer.running){getstation.StopPosSearch();}
                gps.mytimer.stop();
                gps.text.text="";
                gps.mytimer.ticks=0;
                if (hands.listtype!=3){getstation.GetCachedStations();}
                hands.txt="Последние станции:";
            }
        }
    }
    ToolBar {
        id: toolBar
        anchors.bottom: parent.bottom
        tools: ToolBarLayout {
            id: toolBarLayout
            ToolButton {
                flat: true
                iconSource: "toolbar-back.png"
                onClicked: {
                    Qt.quit();

                }
            }
            ToolButton {
                flat: true
                visible: view.currentIndex==1?true:false
                text: "Очистить"
                onClicked: {
                    getstation.clearCache();
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
