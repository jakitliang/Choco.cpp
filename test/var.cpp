#include <iostream>

#include "cc/variant.h"
//#include "cc/var.h"
//#include "cc/slice.h"
//#include "cc/array.h"
//#include "cc/string.h"

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
    cout << is_pod<Variant<int>>::value << endl;
//    cout << is_pod<Var<int>>::value << endl;
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
        Variant<int> i;
        auto j = i;

        cout << j.Inspect().size() << endl;
    }

//    {
//        auto vi = new Variant<int []>(10);
//
////        cout << **vi << endl;
//        delete vi;
//    }
//
//    {
//        Var<int> i;
//        *i = 123;
//    }
//
//    {
//        Slice<int> si({1, 2, 3});
//
//        for (auto & i : si) {
//            cout << i << endl;
//        }
//    }
//
//    {
//        Array<int> ai;
//
//        ai.Push(1);
//        int ais[] = {2,3,4,5};
//
//        ai.Push(ais, 4);
//
//        for (auto &i : ai) {
//            cout << i << endl;
//        }
//    }
//
//    {
//        String s = "hello";
//
//        s.Push(" world!");
//
//        for (auto & c : s) {
//            cout << c << endl;
//        }
//
//        cout << s.cString() << endl;
//    }
//
//    {
//        void * p = malloc(1024);
//        cout << "p size: " << _msize(p) << endl;
//        free(p);
//    }

    return 0;
}
