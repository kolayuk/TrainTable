import QtQuick 1.0
import com.nokia.symbian 1.0

Window {
    id: window
    Connections{
        target: getstation
        onGotoTimeTable:{
            pgs.replace(timeTablePage);
            //pgs.pop(selectStationPage);
        }
        onShowMap:{
            pgs.replace(mapPage);
        }
    }
    Page {
        id: mapPage
        MapView{
            id: map
            onAbout: {pgs.pre_about=pgs.currentPage;pgs.replace(aboutPage);}
            onBack: {pgs.replace(selectStationPage);}
        }
     }
    Page {
        id: selectStationPage
        GetStationView{
            id: station
            win: window;
            onAbout: {pgs.pre_about=pgs.currentPage;pgs.replace(aboutPage);}
        }
     }
    Page {
        id: timeTablePage
        TimeTableView{
            id: table
            win: window;
            onBack:{
                console.log("back");
                pgs.replace(selectStationPage);
                //pgs.pop(timeTablePage);
                station.txtfocus=false;
            }
            onAbout: {
                pgs.pre_about=pgs.currentPage
                pgs.replace(aboutPage);
            }
        }
     }
    Page {
        id: aboutPage
        AboutView{
            id: about;
            onBack: {pgs.replace(pgs.pre_about);}
        }
     }
PageStack{
    id: pgs
    property Item pre_about:Item{}
    Component.onCompleted: pgs.push(selectStationPage);
}

}

