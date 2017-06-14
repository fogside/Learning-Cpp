//
// Created by Eugenia Cheskidova on 14/06/2017.
//

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <sstream>

using namespace std;

void M() {
    map<string, map<string, long > > dict;
    string s_in;
    string name, thing;
    long how_many;
    while (getline(cin, s_in)) {

            if(s_in == "")
                break;
            istringstream ss(s_in);
            ss>>name>>thing>>how_many;

            if (dict.count(name) > 0)
                if (dict[name].count(thing)>0)
                    dict[name][thing]+=how_many;
                else
                    dict[name][thing]=how_many;
            else {
                map<string, long> mymap;
                mymap[thing] = how_many;
                dict.insert(make_pair(name, mymap));
            }
        }

    for (map<string,map<string, long> >::iterator it = dict.begin(); it!=dict.end(); ++it) {
        cout << it->first << ":\n";
        for (map<string, long>::iterator it2 = it->second.begin(); it2!=it->second.end(); ++it2) {
            cout << it2->first << ' ' << it2->second << '\n';
        }
        }
    }

int main()
{
    M();
    return 0;
}
