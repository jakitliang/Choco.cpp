//
// Created by liangjie on 2024/3/25.
//

#include "cc/data.h"
#include <iostream>

using namespace std;

struct Test {
    friend ostream & operator<<(ostream & os, const Test & data) {
        os.setf(ostream::hex);
        os << 100;
        os << " ";
        os << 250;
        return os;
    }
};

int main() {
    CC::Data data(5);
    Test t;

//    cout << t << endl;

    data.Length() = 5;
    data[0] = 100;
    data[1] = 250;
    data[2] = 100;
    data[3] = 250;
    data[4] = 100;

    cout << data << endl;

    return 0;
}
