//
// Created by Eugenia Cheskidova on 25/04/2017.
//

#include "bus.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

bool Bus::operator<(Bus &b) {
    return b.route_number < route_number;
}

istream &operator>>(istream &in, Bus &b) {
    in >> b.bus_number;
    in >> b.driver_surname;
    in >> b.driver_initials;
    in >> b.route_number;
    return in;
}

bool operator==(const Bus &b1, const Bus &b2) {
    return b1.bus_number == b2.bus_number;
}

ostream &operator<<(ostream &stream, const Bus &bus) {
    stream << "bus_num: " << bus.bus_number << ' ' << "Driver: " << bus.driver_surname << ' ' << bus.driver_initials
           << endl;
    return stream;
}

//--------------------------------------------------------------



class PredicateBusNum {
    int bus_num;;

public:
    PredicateBusNum(int num) : bus_num(num) {}

    bool operator()(Bus &b) const {
        return b.bus_number == bus_num;
    }
};


void BusDB::BusToPark(int bus_num) {

    list<Bus>::iterator bus_it = find_if(routeList.begin(), routeList.end(), PredicateBusNum(bus_num));
    if (bus_it == routeList.end()) {
        cerr << "There has not been such a bus on the route" << endl;
        cout << "----------------------------------" << endl;
        return;
    }
    routeList.remove(*bus_it);
    parkList.push_back(*bus_it);

}

void BusDB::BusToRoute(int bus_num) {

    list<Bus>::iterator bus_it = find_if(parkList.begin(), parkList.end(), PredicateBusNum(bus_num));
    if (bus_it == parkList.end()) {
        cerr << "There's no such a bus in the park" << endl;
        cout << "----------------------------------" << endl;
        return;
    }
    parkList.remove(*bus_it);
    routeList.push_back(*bus_it);
}

void BusDB::PrintDB() {

    cout << "In the Bus park:\n";
    for (const Bus& bus: parkList) {
        cout << bus;
    }
    cout << "total: " << parkList.size() << endl;
    cout << "----------------------------------" << endl;
    cout << "On the route:\n";
    for (const Bus& bus: routeList) {
        cout << bus;
    }
    cout << "total: " << routeList.size() << endl;
    cout << "----------------------------------" << endl;

}

BusDB::BusDB(const BusDB &other) {
    routeList = other.routeList;
    parkList = other.parkList;
}

BusDB BusDB::readDBfromStream(istream &infile) {

    BusDB db;
    while (!infile.eof()) {
        Bus b;
        infile >> b;
        db.parkList.push_back(b);
    }
    return db;
}




