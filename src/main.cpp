#include <iostream>

#include "cc/variant.h"
#include "cc/var.h"
#include "cc/slice.h"
#include "cc/array.h"
#include "cc/string.h"

using namespace std;
using namespace CC;

int main() {
    cout << is_pod<Variant<int>>::value << endl;
    cout << is_pod<Var<int>>::value << endl;
    cout << is_pod<Slice<int>>::value << endl;
    cout << is_pod<Array<int>>::value << endl;
    cout << is_pod<String>::value << endl;
    cout << "===================" << endl;

    cout << is_standard_layout<Variant<int>>::value << endl;
    cout << is_standard_layout<Var<int>>::value << endl;
    cout << is_standard_layout<Slice<int>>::value << endl;
    cout << is_standard_layout<Array<int>>::value << endl;
    cout << is_standard_layout<String>::value << endl;
    cout << "===================" << endl;

    {
        int i = 123;
    }

    {
        Var<int> i;
        *i = 123;
    }

    {
        Array<int> ai;

        ai.Push(1);
        int ais[] = {2,3,4,5};

        ai.Push(ais, 4);

        for (auto &i : ai) {
            cout << i << endl;
        }
    }

    {
        String s = "hello";

        s.Push(" world!");

        for (auto & c : s) {
            cout << c << endl;
        }

        cout << s.cString() << endl;
    }

    return 0;
}
