//
// Created by Eugenia Cheskidova on 14/06/2017.
//

#include <list>
#include <sstream>
#include <iostream>
#include <assert.h>

using namespace std;

class TextField {
private:
    list<char> field;
    list<char>::iterator cursor;

public:
    TextField() {
        cursor = field.begin();
    }

    void left() {
        if (cursor != field.begin()) {
            cursor--;
        }
    }

    void right() {
        if (cursor != field.end()) {
            cursor++;
        }
    }

    void home() {
        cursor = field.begin();
    }

    void end() {
        cursor = field.end();
    }

    void del() {
        if (cursor != field.end()) {
            cursor = field.erase(cursor);
        }
    }

    void backspace() {
        if (cursor != field.begin()) {
            cursor = field.erase(--cursor);
        }
    }

    void typeCharacter(char c) {
        field.insert(cursor, c);
    }

    string value() {
        stringstream ss;

        for (list<char>::iterator it = field.begin(); it != field.end(); it++) {
            ss << *it;
        }

        return ss.str();
    }
};

string getInput() {
    string str;
    getline(cin, str);
    return str;
}

void R() {
    TextField tf;
    string input = getInput();

    for (string::iterator it=input.begin(); it != input.end(); it++) {

        char c = *it;

        if (c == 0 || c == '\n') {
            break;
        }
        switch (c) {
            case '<':
                tf.left();
                break;
            case '>':
                tf.right();
                break;
            case '#':
                tf.del();
                break;
            case '@':
                tf.backspace();
                break;
            case '~':
            case '^':
                tf.home();
                break;
            case '$':
                tf.end();
                break;
            default:
                tf.typeCharacter(c);
                break;
        }
    }
    cout << tf.value();
}

int main() {
    R();
}
