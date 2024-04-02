//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/screen.h"
#include "cc/application.h"
#include <iostream>

using namespace std;
using namespace CC;

struct MyWindow : Window {
    void Update(UInt64 deltaTime) override {
        Window::Update(deltaTime);
    }

    void Draw() override {
        Window::Draw();
    }
};

struct MyApp : Application {
    MyWindow mainWindow;

    void onOpen() override {
        Application::onOpen();
        Screen screen;
        UInt32 width = 640, height = 480;
        mainWindow.Open("Hello world",
                        screen.width / 2 - width / 2,
                        screen.height / 2 - height / 2,
                        width, height, 0);
    }

    void onClose() override {
        Application::onClose();
        mainWindow.Close();
    }
};

int main() {
    MyApp app;

//    if (!app.Open()) {
//        cout << "Error!" << endl;
//        return -1;
//    }

//    app.Open("nihao", screen.width / 2 - 50, screen.height / 2 - 50, 200, 200, 0);
    app.Open();
    app.Run();

    return 0;
}
