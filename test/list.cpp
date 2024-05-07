//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/18.
//

#include <iostream>
#include "cc/linked_list.h"

using namespace std;
using namespace CC;

void TestArgs(const LinkedList<int> & numbers) {
    for (auto item : numbers) {
        cout << item << ", ";
    }

    cout << endl;
}

int main() {
//    cout << is_standard_layout<Var<int>>::value << endl;
//    cout << is_standard_layout<Var<int>>::value << endl;
//    cout << is_standard_layout<Slice<int>>::value << endl;
//    cout << is_standard_layout<Array<int>>::value << endl;
//    cout << is_standard_layout<String>::value << endl;
//    cout << "===================" << endl;

    {
        LinkedList<int> i;
        i.Push(123);
//        i.Push(456);
//        i.Push(789);
        cout << i.Count() << endl;
        for (auto & item : i) {
            cout << item << endl;
        }
        cout << "===================" << endl;
        i.Delete(0, 0);
        for (auto & item : i) {
            cout << item << endl;
        }
    }

    cout << "===================" << endl;

    {
        LinkedList<int> i = {{1, 2, 3}};
    }

    cout << "===================" << endl;

    {
        TestArgs({{1, 2, 3}});
    }

    cout << "===================" << endl;

    return 0;
}
