#include <iostream>

#include "cc/object.h"
#include "cc/var.h"
#include "cc/pointer.h"
#include "cc/array.h"
#include "cc/string.h"

using namespace std;
using namespace CC;

struct A : Object {
    int a;
    int b;
};

struct Test1 {
    static const struct {
        static void Echo () { cout << "Echo" << endl; }
    } Object;
};

struct Test2 : Test1 {
    int b;
};

int main() {
    A a;

    cout << is_pod<Object>::value << endl;
    cout << is_standard_layout<A>::value << endl;
    cout << is_pod<Test2>::value << endl;

//    Test2 t2;
//    t2.Object.Echo();

//    cout << is

//    cout << sizeof(Var<void>) << endl;

//    {
//        Var<int> i;
//
//        Var<int[]> z;
//    }

//    int * ip = static_cast<int *>(CC::Pointer::Alloc(4, 1));
//
//    ip = static_cast<int *>(CC::Pointer::ReAlloc(ip, 2));
//
//    cout << "count 2: " << ((CC::Pointer) ip).SizeOfElement() << endl;
//
//    CC::Pointer::Retain(ip);
//
//    CC::Pointer::Release(ip);
//
//    CC::Pointer::Release(ip);

    {
        CC::Array<int> arri;
        cout << arri.Count() << endl;
        cout << arri.Capacity() << endl;
        arri.Insert(100, 111);
        arri.Insert(100, 222);
        arri.Insert(100, 333);
        arri.Insert(100, 111);
        arri.Insert(1, 222);
        cout << arri.Count() << endl;
        cout << arri.Capacity() << endl;

        for (auto & i : arri) {
            cout << i << endl;
        }

        cout << "------" << endl;
        arri.Delete(0);

        for (auto & i : arri) {
            cout << i << endl;
        }
    }

    {
        String s = "hello";

        s.Push(" world!");

        for (auto & c : s) {
            cout << c << endl;
        }
    }

    return 0;
}
