//
// Created by Eugenia Cheskidova on 14/06/2017.
//

#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct MinMaxSet
{
private:
    set<long long, less<long long> > local_set;
public:
    bool empty(){
        return local_set.empty();
    }

    void push(long long num){
        local_set.insert(num);
    }

    unsigned long size(){
        return local_set.size();
    }

    long long end(){
        return *(--local_set.end());
    }
    long long begin(){
        return *(local_set.begin());
    }
    void pop_end(){
        local_set.erase((--local_set.end()));
    }
    void pop_begin(){
        local_set.erase((local_set.begin()));
    }

};


struct MedianSet
{
private:
    MinMaxSet max_set;
    MinMaxSet min_set;
public:
    void insert(long long num);
    long long popMedian();
    long long popMax();
    long long popMin();
};

void MedianSet::insert(long long num) {
    if(max_set.empty() || (num < max_set.end()))
    {
        max_set.push(num);
        if((max_set.size() - min_set.size()) > 1)
        {
            min_set.push(max_set.end());
            max_set.pop_end();
        }
    }
    else
    {
        min_set.push(num);
        if(min_set.size() > max_set.size())
        {
            max_set.push(min_set.begin());
            min_set.pop_begin();
        }
    }
}

long long MedianSet::popMedian() {
    {
        if(!max_set.empty()) {
            long long tmp = max_set.end();
            max_set.pop_end();

            if(min_set.size() > max_set.size())
            {
                max_set.push(min_set.begin());
                min_set.pop_begin();
            }
            return tmp;
        }
        else
            if(!min_set.empty())
            {
                long long tmp = min_set.begin();
                max_set.pop_begin();
                return tmp;
            }
    }
}

long long MedianSet::popMax() {

    if(!min_set.empty())
    {
        long long tmp = min_set.end();
        min_set.pop_end();

        if((max_set.size() - min_set.size()) > 1)
        {
            min_set.push(max_set.end());
            max_set.pop_end();
        }
        return tmp;
    }

    if(!max_set.empty()){
        long long tmp = max_set.end();
        max_set.pop_end();
        return tmp;
    }
}

long long MedianSet::popMin() {

    if(!max_set.empty())
    {
        long long tmp = max_set.begin();
        max_set.pop_begin();

        if(max_set.size() < min_set.size())
        {
            max_set.push(min_set.begin());
            min_set.pop_begin();
        }
        return tmp;
    }

    if(!min_set.empty()){
        long long tmp = min_set.end();
        min_set.pop_end();
        return tmp;
    }
}


enum cmds
{
    ADD, MIN, MAX, MID
};

int O() {
    MedianSet my_set;
    long counter = 0, N;
    long long value;
    map<string, int> mapping;
    mapping["add"] = ADD;
    mapping["min"] = MIN;
    mapping["max"] = MAX;
    mapping["mid"] = MID;

    cin>>N;
    string s_in, command;

    while(getline(cin, s_in))
    {
        if(s_in == "")
            continue;
        istringstream stream(s_in);
        stream>>command;

        switch (mapping[command]) {
            case ADD:
                stream>>value;
                my_set.insert(value);
                break;
            case MIN:
                cout<< my_set.popMin()<<'\n';
                break;
            case MAX:
                cout<< my_set.popMax()<<'\n';
                break;
            case MID:
                cout<< my_set.popMedian()<<'\n';
                break;
        }
        if(++counter == N)
            break;
    }
    return 0;
}


int main()
{
    O();
    return 0;
}