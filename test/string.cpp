//
// Created by Jakit on 2024/3/17.
//

#include "cc/string.h"
#include <iostream>

using namespace std;
using namespace CC;

struct Test : Object {
    int i;
};

struct Test1 : Object {
    int i;

    Test1() = default;

    void Init() {
        i = 0;
    }

    ~Test1() {
        cout << "Test1::~Test()" << endl;
    }
};

int main() {
//    cout << is_pod<Slice<int>>::value << endl;
//    cout << is_pod<Array<int>>::value << endl;
//    cout << is_pod<String>::value << endl;
    cout << "===================" << endl;

//    cout << is_standard_layout<Variant<int>>::value << endl;
//    cout << is_standard_layout<Var<int>>::value << endl;
//    cout << is_standard_layout<Slice<int>>::value << endl;
//    cout << is_standard_layout<Array<int>>::value << endl;
//    cout << is_standard_layout<String>::value << endl;
//    cout << "===================" << endl;

    {
        String s;
        if (!s) {
            cout << "string is empty" << endl;
        }
    }

    cout << "===================" << endl;

    {
        String s = "hello world!";
        cout << s << endl;
    }

    cout << "===================" << endl;

    {
        String s = "hello";

        s.Push(" world!");

        for (auto & c : s) {
            cout << c << endl;
        }

        cout << s << endl;
    }

    return 0;
}