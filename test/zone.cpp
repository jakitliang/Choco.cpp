//
// Created by Jakit on 2024/3/16.
//

#include <iostream>
#include "cc/object.h"

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

    // Initializer and retain
    {
        auto i = Alloc<int>();
        * i = 123456;
        auto j = Retain(i);
        Release(i);
        Release(j);
    }

    cout << "=============" << endl;

    // Copy assign
    {
        int j = 333;
        auto i = Clone(j);
        Release(i);
    }

    cout << "=============" << endl;

    // C++17 aggregate init
    {
        auto t = Clone({1, 2, 3});
        cout << t[0] << endl;
        Release(t);
    }

    return 0;
}
