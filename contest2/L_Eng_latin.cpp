//
// Created by Eugenia Cheskidova on 13/06/2017.
//

#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;

void L() {
    map<string, set<string> > dict;
    string s_in, word;
    string word_eng, word_latin;
    while (getline(cin, s_in)) {
        char *token = std::strtok((char *) (s_in.c_str()), " ,-");
        word_eng = string(token);
        while (token != NULL) {
            token = strtok(NULL, " ,-");
            if(token == NULL)
                break;
            word_latin = string(token);
            if(dict.count(word_latin)>0)
                dict[word_latin].insert(word_eng);
            else {
                set<string> myset;
                myset.insert(word_eng);
                dict.insert(make_pair(word_latin, myset));
            }
        }
    }

    cout<<dict.size()<<'\n';
    for (map<string, set<string> >::iterator it = dict.begin(); it!=dict.end(); ++it) {
        cout << it->first << " - ";
        for (set<string>::iterator it2 = it->second.begin(); it2!=it->second.end(); ++it2) {
            if (++it2!=it->second.end()) {
                cout << *(--it2) << ", ";
            } else {
                cout << *(--it2) << '\n';
            }
        }
    }
}

int main() {
    L();
    return 0;
}