//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/21.
//

#include "cc/linked_list.h"
#include <iostream>

using namespace std;

struct A {
    int n;
};

int main() {
    {
        CC::List<CC::Linked<int>> s;
        s.Insert(0, 123);
    }

    cout << "===============" << endl;

    {
        CC::LinkedList<int> s;
        s.Insert(0, 1);
        s.Insert(0, 2);
        s.Insert(0, 3);
        s.Insert(1, 4);
        s.Insert(1, 5);

        for (auto item : s) {
            cout << item << endl;
        }

        cout << "===============" << endl;

        {
            const CC::LinkedList<int> * ss = &s;

            for (auto item : *ss) {
                cout << item << endl;
            }
        }

        cout << "===============" << endl;

        for (auto i = s.begin(); i != s.end(); ++i) {
            cout << i << endl;
        }
    }

    cout << "===============" << endl;

    {
        CC::LinkedList<int> i;
        i.Push({1, 2, 3});
        CC::UInt32 offset = 0;
        for (auto & item : i) {
            if (item == 2) {
                i.Push(item);
                i.Delete(offset);
                break;
            }
            offset += 1;
        }
        for (auto & item : i) {
            cout << item << endl;
        }
    }

    cout << "===============" << endl;

    {
        CC::LinkedList<int> i;
        i.Push({1, 2, 3});

        CC::Swap(i[0], i.Last());

        for (auto & item : i) {
            cout << item << endl;
        }

        cout << "last: " << i.Last() << endl;
    }

    {
        A a;
        CC::LinkedList<A *> i;
        i.Push(&a);

        for (auto & item : i) {
            cout << item->n << endl;
        }

        find(i.begin(), i.end(), &a);
    }
}
