//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/16.
//

#include "cc/array.h"
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
    {
        Var<int[1]> i;
        i[0] = 123;
        cout << i.Count() << endl;
    }

    cout << "===================" << endl;

    {
        Var<int [10]> i({1, 2, 3});

        for (auto & item : i) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        auto i = Slice({1, 2, 3});
        auto j = Slice({4, 5, 6});
        auto k = i + j;

        for (auto & item : k) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        auto i = Slice({1, 2, 3});
        int j[] = {4, 5, 6};
        auto k = i + j;

        for (auto & item : k) {
            cout << item << endl;
        }
    }

    {
        auto i = Slice({1, 2, 3, 4, 5});
        auto cut = i.Range<2, 3>();
        for (auto & item : cut) {
            cout << item << endl;
        }
    }

    {
        auto i = Slice({1, 2, 3, 4, 5});
        for (auto & item : i) {
            cout << item << endl;
        }
    }

    return 0;
}