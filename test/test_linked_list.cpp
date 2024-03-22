//
// Created by Jakit on 2024/3/21.
//

#include "cc/linked_list.h"

int main() {
    {
        CC::Var<CC::IList<CC::Linked<int>>> i;
        i.Push(123);
    }

    cout << "===============" << endl;

    {
        CC::List<CC::Linked<int>> s;
        s.Insert(0, 123);
    }

    cout << "===============" << endl;

    {
        CC::LinkedList<int> s;
        s.Insert(0, 123);
    }
}
