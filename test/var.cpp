//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/16.
//

#include <iostream>

#include "cc/var.h"
//#include "cc/local.h"
//#include "cc/slice.h"
//#include "cc/array.h"
//#include "cc/string.h"

#include <vector>

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
    cout << is_pod<Object>::value << endl;
    cout << is_pod<Var<int>>::value << endl;
//    cout << is_pod<Var<int>>::value << endl;
//    cout << is_pod<Slice<int>>::value << endl;
//    cout << is_pod<Array<int>>::value << endl;
//    cout << is_pod<String>::value << endl;
    cout << "===================" << endl;

    // Local var test
    {
        int i1 = 123;
        Var<int> i = i1;
        auto j = i;
        auto t = Var(1);

        static int count = 1;

        struct A {
            int a;
            A() : a(count) { count++; }

            ~A() { cout << "~A()" << endl; }
        };

//        vector<Var<A>> v;
//        v.emplace_back(Var<A>());
//        v.push_back(static_cast<A &&>(a));

        Var<A> s = A();
        cout << "===================" << endl;
    }

    return 0;
}
