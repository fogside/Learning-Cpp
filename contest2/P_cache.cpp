//
// Created by Eugenia Cheskidova on 14/06/2017.
//

//
// Created by Eugenia Cheskidova on 14/06/2017.
//

#include <iostream>
#include <map>
#include <queue>
#include <list>

using namespace std;

void P() {

    map<int, int> cache_values;
    map<int, int> cache_values_inv;
    priority_queue<int, vector<int>, greater<int> > time_queue;

    int size, val, idx, count = 0;
    cin >> size;
    while (cin >> val) {

        if (cache_values.count(val) > 0)
            cout << 0 << ' ';
        else
            cout << 1 << ' ';

        cache_values[val] = count;
        cache_values_inv[count] = val;
        time_queue.push(count);
        ++count;

        while (cache_values.size() > size) {
            idx = time_queue.top();
            time_queue.pop();
            map<int, int>::iterator it1 = cache_values_inv.find(idx);
            int val = it1->second;
            map<int, int>::iterator it2 = cache_values.find(val);
            if (it2->second == idx) { // We're removing most recent "memory" of reading val
                cache_values.erase(it2);
            }
            cache_values_inv.erase(it1);
        }
    }

}

int main() {
    P();
    return 0;
}
