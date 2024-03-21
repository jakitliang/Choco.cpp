//
// Created by Jakit on 2024/3/21.
//

#include "cc/linked_list.h"
//#include "cc/var_delegate.h"
//#include "cc/vector.h"

#include "cc/list.h"

template<typename T>
struct A {};

int main() {
    {
        CC::Var<CC::IList<int>> i(CC::Make<CC::LinkedList<int>>());
    }

    int a = 1;
}
