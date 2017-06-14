//
// Created by Eugenia Cheskidova on 13/06/2017.
//
#include <set>
#include <map>
#include <iostream>
#include <algorithm>


using namespace std;

struct NextSet
{
private:
    set<int> container;
public:
    void add(int i);
    int next(int i);
};

void NextSet::add(int i) {
    container.insert(i);
}

int NextSet::next(int i) {
    set<int>::iterator next = container.upper_bound(i-1);
    if (next == container.end()) {
        int tmp = *(--next);
        if (tmp<i)
            return -1;
        else
            return tmp;
    }

    return *next;
}

void H()
{
    NextSet nextSet;
    int MAX = 1000000000;

    int N_OPS;
    int FLAG = -1; // it is about previous value of NEXT;
    char cmd;
    int value;
    cin>>N_OPS;
    for(int i=0; i<N_OPS; ++i)
    {
        cin>>cmd>>value;
        switch(cmd)
        {
            case '+':
                if(FLAG<0)
                    nextSet.add(value);
                else {
                    int tmp = ((FLAG + value) > MAX) ? ((FLAG + value) % MAX) : (FLAG + value);
                    nextSet.add(tmp);
                    FLAG = -1;
                }
                break;
            case '?':
                FLAG = nextSet.next(value);
                cout<<FLAG<<'\n';
                break;
        }
    }
}

int main()
{
    H();
    return 0;
}