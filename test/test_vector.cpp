//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/21.
//

#include "cc/vector.h"
#include <iostream>

using namespace std;

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

    cout << "===============" << endl;

    {
        CC::Vector<int> s;
        s.Push({1, 2, 3});
        cout << s.Last() << endl;

        auto ret = std::find(s.begin(), s.end(), 1);

        if (ret != s.end()) {
            cout << ret << endl;
        }
    }

    int a = 1;
}
