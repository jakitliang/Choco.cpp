//
// Created by Jakit on 2024/3/21.
//

#include "cc/vector.h"

#include "cc/list.h"

template<typename T>
struct A {};

int main() {
    {
        CC::Var<CC::IList<CC::Trivial<int>>> i;
        i.Push(123);
    }

    cout << "===============" << endl;

    {
        CC::List<CC::Trivial<int>> s;
        s.Insert(0, 123);
    }

    cout << "===============" << endl;

    {
        CC::Vector<int> s;
        s.Insert(0, 123);
    }

    int a = 1;
}
