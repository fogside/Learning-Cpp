//
// Created by Eugenia Cheskidova on 25/04/2017.
//

#ifndef SEMINARWORKSHOP_BUS_H
#define SEMINARWORKSHOP_BUS_H


#include <iostream>
#include <list>

using namespace std;

struct Bus
{
    friend class PredicateBusNum;
    int bus_number;
    string driver_surname;
    string driver_initials;
    int route_number;

    Bus(): driver_surname(""), driver_initials(""), route_number(-1), bus_number(-1) {};
    Bus(int _bus_number, string _driver_surname, string _driver_initials, int _route_number):
            bus_number(_bus_number), driver_surname(_driver_surname),
            driver_initials(_driver_initials), route_number(_route_number) {};
    friend istream &operator>>(istream &, Bus &);
    friend ostream &operator<<(ostream &, const Bus &);
    friend bool operator==(const Bus &b1, const Bus &b2);
    bool operator<(Bus &);
};

class BusDB
{
    list <Bus> parkList;
    list <Bus> routeList;

public:
    BusDB(){}; // для создания пустой базы
    BusDB(const BusDB &other);

    static void readDBfromStream(istream &strm, BusDB & db);

    void BusToRoute(int bus_num); // вводится номер автобуса, выезжающего на маршрут;
    void BusToPark(int bus_num); // вводится номер автобуса, въезжающего в парк;
    void PrintDB(); // просто выводим все на экран;

    ~BusDB(){};
};


#endif //SEMINARWORKSHOP_BUS_H
