//
// Created by Eugenia Cheskidova on 13/06/2017.
//
#include <map>
#include <iostream>

using namespace std;

void I() {

    map<string, string> dict;
    int N;
    string w1, w2;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin>>w1>>w2;
        dict[w1] = w2;
        dict[w2] = w1;
    }
    cin>>w1;
    cout<<dict[w1]<<'\n';
}

int main() {
    I();
    return 0;
}