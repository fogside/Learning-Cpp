//
// Created by Eugenia Cheskidova on 13/06/2017.
//

#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace std;

struct transOp{
    pair<int, string> operator()(const pair<string, int> &p)
    {
        return make_pair(p.second, p.first);
    }
};

struct cmpPair{
    bool operator()(const pair<int, string> &p1, const pair<int, string> &p2)
    {
        if(p1.first!=p2.first)
            return p1.first<p2.first;
        else
            return strcmp(p1.second.c_str(), p2.second.c_str())>0;
    }

};

void K()
{
    map<string, int> dict;
    string word;
    while(cin>>word)
    {
        if(dict.count(word)>0)
            dict[word]+=1;
        else
            dict[word] = 1;
    }

    list<pair<int, string> > pairs_list;

    pairs_list.resize(dict.size());
    transform(dict.begin(), dict.end(), pairs_list.begin(), transOp());

    pairs_list.sort(cmpPair());

    while(!pairs_list.empty()) {
        cout << pairs_list.back().second <<'\n';
        pairs_list.pop_back();
    }
}

int main(){
    K();
    return 0;
}