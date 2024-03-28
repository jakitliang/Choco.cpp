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
    app.Open("nihao", screen.width / 2 - 50, screen.height / 2 - 50, 200, 200, 0);
    app.Run();

    return 0;
}
