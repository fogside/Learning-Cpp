#include <set>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

struct StringSet
{
private:
    set<long long> string_container;
    long long count_hash(const string &s);
public:
    StringSet();
    void add(const string &s);
    bool contains(const string& s);
    void del(const string &s);
};

long long StringSet::count_hash(const string &s) {
        long long r  = 0;
        for (int i = 0; i<=s.size(); ++i) {
            r = 26*r + (unsigned char)s[i]-'a';
        }
        return r;
}

void StringSet::add(const string &s) {
    string_container.insert(count_hash(s));
}

bool StringSet::contains(const string &s) {
    return string_container.find(count_hash(s))!=string_container.end();
}

void StringSet::del(const string &s) {
    string_container.erase(count_hash(s));
    return;

}

StringSet::StringSet() : string_container() {}




enum cmds
{
    ADD, DEL, CHECK, FIN
};

int G()
{
    StringSet my_set;
    map<string, int> mapping;
    mapping["+"] = ADD;
    mapping["-"] = DEL;
    mapping["?"] = CHECK;
    mapping["#"] = FIN;

    string s_in, command, value;
    while(getline(cin, s_in))
    {
        istringstream stream(s_in);
        stream>>command>>value;
        switch (mapping[command]) {
                case ADD:
                    my_set.add(value);
                    break;
                case DEL:
                    my_set.del(value);
                    break;
                case CHECK:
                    if(my_set.contains(value))
                        cout<<"YES"<<'\n';
                    else
                        cout<<"NO"<<'\n';
                    break;
                case FIN:
                    return 0;
        }
    }
    return 0;
}


int main()
{
    return G();
}