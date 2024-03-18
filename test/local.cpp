//
// Created by Jakit on 2024/3/18.
//

#include "cc/slice.h"
#include <iostream>
#include "cc/local.h"

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
        Local<int> i;
        auto j = i;

        cout << j.Inspect().size() << endl;
    }

    {
        Local<int> i;
        auto j = i;

        cout << j.Inspect().size() << endl;
    }
}
