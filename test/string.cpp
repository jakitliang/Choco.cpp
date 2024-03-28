//
// Created by Jakit on 2024/3/17.
//

#include "cc/array.h"
#include "cc/string.h"
#include <iostream>

using namespace std;
using namespace CC;

int main() {
//    cout << is_pod<Slice<int>>::value << endl;
//    cout << is_pod<Array<int>>::value << endl;
//    cout << is_pod<String>::value << endl;
    cout << "===================" << endl;

//    cout << is_standard_layout<Var<int>>::value << endl;
//    cout << is_standard_layout<Var<int>>::value << endl;
//    cout << is_standard_layout<Slice<int>>::value << endl;
//    cout << is_standard_layout<Array<int>>::value << endl;
//    cout << is_standard_layout<String>::value << endl;
//    cout << "===================" << endl;

    {
        String s;
        if (!s) {
            cout << "string is empty" << endl;
        }
    }

    cout << "===================" << endl;

    {
        String s = "hello world!";
        cout << s << endl;
    }

    cout << "===================" << endl;

    {
        String s = "hello";

        s.Push(" world!");

        for (auto & c : s) {
            cout << c << endl;
        }

        cout << s << endl;
    }

    cout << "===================" << endl;

    {
        String s = "Hello!";

        cout << s << endl;

        s.Insert(5, " demo");

        cout << s << endl;

        s.Delete(0);

        cout << s << endl;

        cout << "s.len: " << s.Length() << ", s.count: " << s.Count() << endl;

        cout << s[9] << endl;
    }

    {

    }

    return 0;
}