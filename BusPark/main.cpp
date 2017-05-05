#include <iostream>
#include <fstream>
#include <sstream>
#include "bus.h"
#include "FileNotFoundException.h"

using namespace std;

void help()
{
    cout<<"Hello! You are at the system of bus park control"<<endl;
    cout<<"Please, choose action and type its number;"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"1: Create db from file;"<<endl;
    cout<<"2: Create db from cmd;"<<endl;
    cout<<"3: Type bus number which is going on the route now;"<<endl;
    cout<<"4: Type bus number which is arriving to the bus_park now;"<<endl;
    cout<<"5: Print dataBase;"<<endl;
    cout<<"6: This Help"<<endl;
    cout<<"7: Exit without saving"<<endl;
    cout<<"----------------------------------"<<endl;

}

void createDBfromFile(BusDB & db)
{
    string filename;
    cout<<"Please, write path to the file with data;"<<endl;
    cin>>filename;
    ifstream infile(filename);

    if (!infile.is_open()) {
        throw FileNotFoundException(filename);
    }

    BusDB::readDBfromStream(infile, db);
}

void createDBfromCmd(BusDB & db)
{
    cout << "Type lines in format:" << endl;
    cout << "bus_number driver_initials driver_surname route_number" << endl;
    cout << "(you can use as delimeters both space and tab)" << endl;
    cout << "Type # to end input" << endl;
    cout << "----------------------------------" << endl;

    BusDB::readDBfromStream(cin, db);
}

void BusToRoute(BusDB &db)
{
    cout<<"Please, type number for bus which is going on the route:"<<endl;
    int num;
    cin>>num;
    db.BusToRoute(num);
}

void BusToHome(BusDB &db)
{
    cout<<"Please, type number for bus which is going on the route:"<<endl;
    int num;
    cin>>num;
    db.BusToPark(num);
}


enum class Action {
    CREATE_FROM_FILE = 1,
    CREATE_FROM_CMD,
    BUS_TO_ROUTE,
    BUS_TO_HOME,
    PRINT_DB,
    HELP,
    EXIT
};

int main() {

    help();
    BusDB db;

    while(true)
    {
        try {
            cout << "Write smth again if you want or 7 exit" << endl;

            string action_code;

            cout<<"EOF: "<<cin.eof()<<" BAD: "<<cin.bad()<<" FAIL: "<<cin.fail()<<endl;
            cin.clear();
            cin >> action_code;

            if(action_code.empty())
                continue;

            Action action = static_cast<Action>(stoi(action_code));

            switch (action) {
                case Action::CREATE_FROM_FILE:
                    createDBfromFile(db);
                    break;
                case Action::CREATE_FROM_CMD:
                    createDBfromCmd(db);
                    break;
                case Action::BUS_TO_ROUTE:
                    BusToRoute(db);
                    break;
                case Action::BUS_TO_HOME:
                    BusToHome(db);
                    break;
                case Action::PRINT_DB:
                    db.PrintDB();
                    break;
                case Action::HELP:
                    help();
                    break;
                case Action::EXIT:
                    exit(0);
                default:
                    cout<<"Wrong command, try another"<<endl;
                    break;

            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
    }
}
