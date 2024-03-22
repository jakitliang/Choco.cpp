//
// Created by Jakit on 2024/3/21.
//

#include "cc/linked.h"
#include "cc/vector.h"
//#include "cc/var_delegate.h"
//#include "cc/vector.h"

#include "cc/list.h"

template<typename T>
struct A {};

int main() {
//    {
//        CC::Var<CC::IList<int>> i(CC::Make<CC::Linked<int>>());
//    }

//    {
//        auto i = CC::Make<CC::Linked<int>>();
//        CC::Destroy(i);
//    }

//    {
//        CC::Var<CC::IList<int>> i(CC::Make<CC::Vector<int>>());
//    }

//    {
//        auto i = CC::Make<CC::Vector<int>>();
//        CC::Destroy(i);
//    }

    {
        CC::Var<CC::IList<CC::Linked<int>>> i;
        i.Push(123);
    }

    cout << "===============" << endl;

    {
        CC::Var<CC::IList<CC::Linked<int>>> i;
        i.Push(123);
    }

    cout << "===============" << endl;

    {
        CC::Var<CC::IList<CC::Linked<int>>> i;
        i.Push(123);
    }

    cout << "===============" << endl;

//    {
//        CC::List<CC::Linked<int>> s;
//        s.Insert(0, 123);
//    }

    int a = 1;
}
