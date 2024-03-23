//
// Created by Jakit on 2024/3/21.
//

#include "cc/linked_list.h"

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
}
