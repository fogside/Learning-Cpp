//
// Created by Eugenia Cheskidova on 14/06/2017.
//

#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

void N()
{
    priority_queue<int, vector<int>, greater<int> > heap;
    int N, tmp;
    double percentage = 0.05, cost = 0;
    cin>>N;
    for(int i = 0; i<N; ++i) {
        cin>>tmp;
        heap.push(tmp);
    }

    while(heap.size()!=1){
        tmp = heap.top();
        heap.pop();
        tmp+= heap.top();
        heap.pop();
        cost+=tmp*percentage;
        heap.push(tmp);
    }
    cout << setprecision (2) << fixed << cost;
}

int main()
{
    N();
    return 0;
}