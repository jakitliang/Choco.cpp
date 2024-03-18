//
// Created by Jakit on 2024/3/16.
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
        Array<int> i;
        Array<int> j = i;
        i.Push(1);
        i.Push(2);
        i.Push(3);
        i.Push(4);
        for (auto item : j) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        Array<int> ai;

        ai.Push(1);
        int ais[] = {2,3,4,5};

        ai.Push(ais, 4);

        for (auto &i : ai) {
            cout << i << endl;
        }

        cout << "==== Delete test ===" << endl;

        ai.Delete(0, 2);

        for (auto &i : ai) {
            cout << i << endl;
        }

        cout << "==== Reins test ===" << endl;

        ai.Insert(4, 1);

        for (auto &i : ai) {
            cout << i << endl;
        }
    }

    cout << "===================" << endl;

    struct A {
        int * a;

        A() : a(new int) {
            cout << "A()" << endl;
        }

        A(const A & a) : a(new int) {
            cout << "A() copy" << endl;
            *this->a = *a.a;
        }

        A(A && a) : a(new int) {
            cout << "A() move" << endl;
            *this->a = *a.a;
        }

        ~A() {
            cout << "A<" << this << ">" << "~A().a<" << a << ">" << endl;
            delete a;
        }

        A & operator=(const A & a) {
            cout << "A::operator= copy" << endl;
            this->a = new int(*a.a);
            return *this;
        }

        A & operator=(A && a) {
            cout << "A::operator= move" << endl;
            this->a = new int(*a.a);
            return *this;
        }
    };

    {
        Array<A> a;


        // MoveCtor
        a.Push(A());
        a.Push(A());
        a.Push(A());

        // CopyCtor
//        A tmp;
//        a.Push(tmp);

        // Move
//        a[0] = A();

        // Copy
//        A tmp;
//        a[0] = tmp;

        cout << "===================" << endl;
        a.Delete(1);

        int x = 4;
    }

    {
        vector<A> a;


        a.push_back(A());
        a.push_back(A());
        a.push_back(A());

        cout << "===================" << endl;
        a.erase(a.begin() + 1);
        int x = 4;
    }

    return 0;
}
