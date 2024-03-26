//
// Created by liangjie on 2024/3/26.
//

#include "cc/window.h"
#include <iostream>

using namespace std;
using namespace CC;

int main() {
    Window wnd;
    wnd.Open("nihao", 0, 0, 100, 100, Window::Flags::Metal);
    return 0;
}
