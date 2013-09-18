#ifndef CONST_H
#define CONST_H

const int POSITIONING_TIMEOUT=20;
#define URL_TEMPLATE_STATION_GEO "https://maps.googleapis.com/maps/api/place/search/xml?location=%f,%f&types=train_station&radius=%d&sensor=false&key=AIzaSyAQo0yaLxKlzzypE3jbr41n2z37Jeg2epc"
const int START_RADIUS=10000;
#define URL_GET_STATION_ID "http://rasp.yandex.ru/station_search?cityFrom=%s"
#define URL_GET_TRAINS_TO_STATION "http://rasp.yandex.ru/search/?fromName=&fromId=%s&toName=%s&toId=&when="
#define URL_FIND_ROUTE "http://maps.googleapis.com/maps/api/directions/xml?sensor=false&origin=%f,%f&destination=%f,%f&mode=walking"
#define URL_REQUEST_MAP "http://maps.google.com/staticmap?markers=%f,%f,redu|%f,%f,blues&size=1500x1500&key=ABQIAAAACVt8r16SyC8Is_qoAPnJcBTMIeNJKTNaIRjbOjyvBVSVDww0NRQUrJ8d-t2c5goqa8NzXuuY4SE3jQ&sensor=false&path=rgb:0x0000ff,weight:5|"

#define PROMO_FOLDER "promo/"
#define PROMO_FILE "qml/TrainTable/promo/promo.txt"
#define TIMETABLE_CACHE_FOLDER "D:\\TrainTable\\"
#define FILE_STATIONS_CACHE "stations.txt"
#define FILE_TRANSLATE "qml/TrainTable/dic.txt"
#endif // CONST_H
