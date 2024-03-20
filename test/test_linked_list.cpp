//
// Created by Jakit on 2024/3/21.
//

#include "cc/linked_list.h"
#include "cc/var_delegate.h"
#include "cc/vector.h"

int main() {
    {
        CC::Variant<CC::LinkedList<int>> i;
        i.Push(1);
    }

    int a = 1;
}
