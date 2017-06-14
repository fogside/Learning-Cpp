#include <iostream>
#include <algorithm>
#include <deque>
#include <stack>
#include <stdexcept>
#include <map>
#include <sstream>
#include <utility>
#include <climits>

using namespace std;


//---------------------------------------------------------


class MinQueueEmptyException : public logic_error {
public:
    MinQueueEmptyException() : logic_error("Queue is empty!") {};
};

//---------------------------------------------------------

struct minStack {
    stack<pair<long long, long long> > _stack;

    void push(long long a);

    void pop();

    bool isEmpty();

    pair<long long, long long> peek();

    long long int size();

    long long int minimum();
};

void minStack::push(long long a) {

    long long _min;
    _min = min(this->minimum(), a);
    _stack.push(make_pair(a, _min));
    return;
}

void minStack::pop() {
    if (isEmpty())
        throw MinQueueEmptyException();
    _stack.pop();
    return;
}

bool minStack::isEmpty() {
    return _stack.empty();
}

pair<long long, long long> minStack::peek() {
    if (isEmpty())
        throw MinQueueEmptyException();
    return _stack.top();
}

long long minStack::minimum() {
    if (!isEmpty())
        return _stack.top().second;
    return LLONG_MAX;
}

long long minStack::size() {
    return (long long) _stack.size();
}



//---------------------------------------------------------

struct minQueue {
private:
    minStack in_stack;
    minStack out_stack;
    void shuffle();
public:
    minQueue() {};

    void enqueue(long long a);

    long long size();

    void dequeue();

    long long front();

    void clear();

    long long minimum();

    bool isEmpty();
};

//---------------------------------------------------------

long long minQueue::size() {
    long long size = in_stack.size() + out_stack.size();
    return size;
}

void minQueue::shuffle() {
    if (out_stack.isEmpty() && !in_stack.isEmpty())
        while (!in_stack.isEmpty()) {
            out_stack.push(in_stack.peek().first);
            in_stack.pop();
        }
}

void minQueue::enqueue(long long a) {
    in_stack.push(a);
}

void minQueue::dequeue() {
    shuffle();
    out_stack.pop();
}

long long int minQueue::front() {
    shuffle();
    return out_stack.peek().first;
}

long long int minQueue::minimum() {
    if ((in_stack.isEmpty() && out_stack.isEmpty()))
        throw MinQueueEmptyException();
    return min(in_stack.minimum(), out_stack.minimum());
}

void minQueue::clear() {
    while (!in_stack.isEmpty()) {
        in_stack.pop();
    }
    while (!out_stack.isEmpty()) {
        out_stack.pop();
    }
    return;
}

bool minQueue::isEmpty() {
    return in_stack.isEmpty() && out_stack.isEmpty();
}

enum queue_cmds {
    enqueue, dequeue, front, size, clear, minimum
};

void E() {
    minQueue minQ;
    map<string, int> mapping;

    mapping["enqueue"] = enqueue;
    mapping["dequeue"] = dequeue;
    mapping["front"] = front;
    mapping["size"] = size;
    mapping["clear"] = clear;
    mapping["min"] = minimum;

    int M; //number of commands;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        string s;
        long long tmp;

        cin >> s;
        try {
            switch (mapping[s]) {
                case enqueue:
                    cin >> tmp;
                    minQ.enqueue(tmp);
                    cout << "ok" << '\n';
                    break;
                case dequeue:
                    cout<<minQ.front()<<'\n';
                    minQ.dequeue();
                    break;
                case front:
                    cout<<minQ.front()<<'\n';
                    break;
                case minimum:
                    cout<<minQ.minimum()<<'\n';
                    break;
                case size:
                    cout << minQ.size() << '\n';
                    break;
                case clear:
                    minQ.clear();
                    cout << "ok" << '\n';
                    break;
            }
        }
        catch (MinQueueEmptyException &e) {
            cout << "error" << '\n';
        }
    }

}


void test()
{
    /*
     * enum queue_cmds {
    enqueue, dequeue, front, size, clear, minimum
     };
     */
    minQueue minQ;
    map<string, int> mapping;

    string test_str = "14\n0 10000000\n0 123232342\n0 34\n5\n1\n0 1232\n0 1232\n0 1231\n5\n1\n5\n1\n3\n5\n";
    istringstream s(test_str);
    int M; //number of commands;
    s >> M;
    for (int i = 0; i < M; ++i) {
        long long tmp;
        int act;
        s >> act;
        cout<<"act: "<<queue_cmds(act)<<'\n';
        try {
            switch (act) {
                case enqueue:
                    s >> tmp;
                    minQ.enqueue(tmp);
                    cout<< "enqueue: "<<tmp<<'\n';
                    cout << "ok" << '\n';
                    break;
                case dequeue:
                    cout<<minQ.front()<<'\n';
                    minQ.dequeue();
                    break;
                case front:
                    cout<<minQ.front()<<'\n';
                    break;
                case minimum:
                    cout<<minQ.minimum()<<'\n';
                    break;
                case size:
                    cout << minQ.size() << '\n';
                    break;
                case clear:
                    minQ.clear();
                    cout << "ok" << '\n';
                    break;
            }
        }
        catch (MinQueueEmptyException &e) {
            cout << "error" << '\n';
        }
    }
}

int main() {
    E();
    return 0;
}