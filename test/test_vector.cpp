//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/21.
//

#include "cc/vector.h"

#include "cc/list.h"

template<typename T>
struct A {};

int main() {
    {
        CC::List<CC::Trivial<int>> s;
        s.Insert(0, 123);
    }

    cout << "===============" << endl;

    {
        CC::Vector<int> s;
        s.Insert(0, 1);
        s.Insert(0, 2);
        s.Insert(0, 3);

        for (auto item : s) {
            cout << item << endl;
        }

        cout << "===============" << endl;

        for (auto i = s.begin(); i != s.end(); ++i) {
            cout << i << endl;
        }
    }

    int a = 1;
}
