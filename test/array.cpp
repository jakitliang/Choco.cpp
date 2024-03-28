//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/16.
//

#include "cc/array.h"
#include <iostream>

using namespace std;
using namespace CC;

void printCount(Var<int []> & i) {
    for (auto & item : i) {
        cout << item << endl;
    }
    cout << "count: " << i.Count() << endl;
}

int main() {
    {
        Var<int [3]> i;
        auto i1 = Var<int [3]>({1, 2, 3});
        int ii1[] = {1,2,3};
        Var<int [3]> i2 = ii1;
        printCount(i2);
    }

    cout << "===================" << endl;

    {
        auto array = Array({1, 2, 3});
    }

    {
        Var<int [3]> i;
        int a = 1;
    }

    return 0;
}
