//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/file_channel.h"
#include <iostream>

using namespace std;
using namespace CC;

int main() {
    {
        FileChannel fileChannel(R"(C:/Users/Jakit/Documents/Temp/test.txt)", "w+");
    }

    int tmp = 123;
}
