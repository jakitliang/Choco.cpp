#include <iostream>

#include "cc/var.h"
#include "cc/local.h"
#include "cc/slice.h"
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

    // Local var test
    {
        Var<int &> i;
        auto j = i;

        cout << j.Inspect().size() << endl;
    }

    cout << "===================" << endl;

    // Slice var test
    {
        Var<int (&)[]> i;
        auto j = i;

        cout << j.Inspect().size() << endl;
    }

    // Vector var
    {
        Var<vector<int>> v;
    }

    return 0;
}
