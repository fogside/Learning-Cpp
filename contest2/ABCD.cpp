#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <stdexcept>
#include <map>

using namespace std;


//---------------------------------------------------------

struct Command {
    int n_solved;
    int penalty;
    int number;

    Command() : n_solved(0), penalty(0), number(0) {};

    Command(int n, int pent, int num) : n_solved(n), penalty(pent), number(num) {};

    friend std::istream &operator>>(std::istream &istr, Command &cmd);
};

//---------------------------------------------------------

struct A_cmp {
    bool operator()(const Command &cmd1, const Command &cmd2) const {
        if (cmd1.n_solved != cmd2.n_solved)
            return cmd1.n_solved > cmd2.n_solved;

        if (cmd1.penalty != cmd2.penalty)
            return cmd1.penalty < cmd2.penalty;

        return cmd1.number < cmd2.number;
    }
};

//---------------------------------------------------------

std::istream &operator>>(std::istream &istr, Command &cmd) {
    istr >> cmd.n_solved >> cmd.penalty;
    return istr;
}

void A() {
    vector<Command> cmds_vec;
    int cmd_amount;
    cin >> cmd_amount;
    for (int i = 0; i < cmd_amount; ++i) {
        Command cmd;
        cin >> cmd;
        cmd.number = i + 1;
        cmds_vec.push_back(cmd);
    }

    sort(cmds_vec.begin(), cmds_vec.end(), A_cmp());
    for (int i = 0; i < cmd_amount; ++i) {
        cout << cmds_vec[i].number << ' ';
    }
}
//---------------------------------------------------------


void B() {
    vector<int> animals;
    vector<int> answers;

    int anim_amount;
    cin >> anim_amount;

    animals.resize(anim_amount);
    int tmp;
    for (int i = 0; i < anim_amount; ++i) {
        cin >> tmp;
        animals[i] = tmp;
    }
    int M; // number of requests;
    cin >> M;

    answers.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> tmp;
        int low = lower_bound(animals.begin(), animals.end(), tmp) - animals.begin();
        int up = upper_bound(animals.begin(), animals.end(), tmp) - animals.begin();
        int res = up - low;
        answers[i] = res;
    }

    for (int i=0; i<M; ++i)
    {
        cout<<answers[i]<<'\n';
    }

}

//---------------------------------------------------------


void C()
{
    list<int> numbers;
    int N;
    cin>>N;
    for (int i = 0; i < N; ++i) {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
    int target;
    cin>>target;
    int res = count(numbers.begin(), numbers.end(), target);
    cout<<res;
}

//---------------------------------------------------------

enum deque_cmds
{
    PUSH_BACK, PUSH_FRONT, POP_BACK, POP_FRONT, FRONT, BACK, SIZE, CLEAR
};

class DequeEmptyException: public length_error
{
public:
    DequeEmptyException(): length_error("Deque is empty!") {};
};


void D()
{
    deque<int> my_deque;
    map<string, int> mapping;

    mapping["push_back"] = PUSH_BACK;
    mapping["push_front"] = PUSH_FRONT;
    mapping["pop_back"] = POP_BACK;
    mapping["pop_front"] = POP_FRONT;
    mapping["front"] = FRONT;
    mapping["back"] = BACK;
    mapping["size"] = SIZE;
    mapping["clear"] = CLEAR;

    int M; //number of commands;
    cin>>M;
    for(int i = 0; i<M; ++i)
    {
        string s;
        int tmp;

        cin>>s;
        try {
            switch (mapping[s]) {
                case PUSH_BACK:
                    cin >> tmp;
                    my_deque.push_back(tmp);
                    cout << "ok" << '\n';
                    break;
                case PUSH_FRONT:
                    cin >> tmp;
                    my_deque.push_front(tmp);
                    cout << "ok" << '\n';
                    break;
                case POP_BACK:
                    if (my_deque.size() == 0)
                        throw DequeEmptyException();
                    cout << my_deque.back() << '\n';
                    my_deque.pop_back();
                    break;
                case POP_FRONT:
                    if (my_deque.size() == 0)
                        throw DequeEmptyException();
                    cout << my_deque.front() << '\n';
                    my_deque.pop_front();
                    break;
                case FRONT:
                    if (my_deque.size() == 0)
                        throw DequeEmptyException();
                    cout << my_deque.front() << '\n';
                    break;
                case BACK:
                    if (my_deque.size() == 0)
                        throw DequeEmptyException();
                    cout << my_deque.back() << '\n';
                    break;
                case SIZE:
                    cout << my_deque.size() << '\n';
                    break;
                case CLEAR:
                    my_deque.clear();
                    cout << "ok" << '\n';
                    break;
            }
        }
        catch (DequeEmptyException &e)
        {
            cout<<"error"<<'\n';
        }
    }

}


int main() {
    B();
    return 0;
}