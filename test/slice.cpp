//
// Created by Jakit on 2024/3/16.
//

#include "cc/slice.h"
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
        Slice<int> i;
        cout << i.Count() << endl;
    }

    cout << "===================" << endl;

    {
        Slice<int> i(10);
        i[0] = 123;
        cout << i.Count() << endl;
    }

    cout << "===================" << endl;

    {
        Slice<int> i({1, 2, 3});

        for (auto & item : i) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        Slice<int> i({1, 2, 3});
        Slice<int> j({4, 5, 6});
        auto k = i + j;

        for (auto & item : k) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        Slice<int> i({1, 2, 3});
        int j[] = {4, 5, 6};
        auto k = i + j;

        for (auto & item : k) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    struct A {
        int * a;

        A() : a(new int) { cout << "A()" << endl; }

        A(const A & a) : a(new int) {
            cout << "A() copy" << endl;
            *this->a = *a.a;
        }

        ~A() { cout << "A<" << this << ">" << "~A().a<" << a << ">" << endl; delete a; }
    };

    {
        Slice<A> s(5);
    }

    cout << "===================" << endl;

    {
        Slice<A> s1(1);
        Slice<A> s2(1);
        Slice<A> s3 = s1 + s2;
    }

    cout << "===================" << endl;

    {
        Slice<A> s1(1);
        A s2[1];
        Slice<A> s3 = s1 + s2;
    }

    return 0;
}