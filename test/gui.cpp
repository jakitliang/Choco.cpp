//
// Created by liangjie on 2024/3/26.
//

#include "cc/window.h"
#include "cc/screen.h"
#include "cc/application.h"
#include <iostream>

using namespace std;
using namespace CC;

int main() {
    Application app;

    if (!app.Open()) {
        cout << "Error!" << endl;
        return -1;
    }

    Screen screen;
    Window wnd;
    wnd.Open("nihao", screen.width / 2 - 50, screen.height / 2 - 50, 100, 100, 0);
    app.Run();

    return 0;
}
