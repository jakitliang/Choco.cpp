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
        int & i = Alloc<int>(0);
        i = 123456;
        int & j = Retain(i);
        Release(i);
        Release(j);
    }

    // Copy assign
    {
        int j = 333;
        int & i = Alloc<int>(j);
        Release(i);
    }

    // C++17 aggregate init
    {
        auto & t = Alloc<Test>({{}, 1});
        cout << t.i << endl;
        Release(t);
    }

    // Passing class member as initializer
    {
        auto & t = Alloc<Test1>(&Test1::Init);
        cout << t.i << endl;
        Release(t);
    }

    // Default destruct and default destruct
    {
        auto & t = Alloc<Test1>(true);
        cout << t.i << endl;
        Release(t, true);
    }

    // Inspect and user-defined finalizer
    {
        auto & t = Alloc<Test>();
        t.i = 6513408;

        for (auto & b : t.Inspect()) {
            cout << b << endl;
        }

        Release(t, [](Test & o) {
            cout << o.i << endl;
        });
    }

    return 0;
}
