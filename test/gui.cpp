//
// Created by liangjie on 2024/3/26.
//

#include "cc/window.h"
#include "cc/application.h"
#include <iostream>

using namespace std;
using namespace CC;

int main() {
    Application app;
    Window wnd;
    wnd.Open("nihao", 0, 0, 100, 100, Window::Flags::Metal);
    return 0;
}
