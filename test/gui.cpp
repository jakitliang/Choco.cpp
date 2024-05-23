//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/screen.h"
#include "cc/application.h"
#include "cc/graphics.h"
#include "cc/image.h"
#include "cc/canvas.h"
#include "cc/pixels.h"
#include "cc/font.h"
#include <iostream>

using namespace std;
using namespace CC;

static CC::Image img;
static CC::Canvas canvas;
static CC::Font font;

extern unsigned char hkyt_ttf[];
extern unsigned int hkyt_ttf_len;
static bool ButtonStatus = false;
static Vector2 CurrentMouse;
static Vector2 PreviousMouse;

struct MyWindow : Window {
    void onStateChanged(UIWindowEvent &event) override {
        Window::onStateChanged(event);

        cout << "onStateChanged: " << (int) event.Event << endl;
    }

    void Update(UInt64 deltaTime) override {
        Window::Update(deltaTime);

        if (ButtonStatus) {
//            cout << CurrentMouse.X << ", " << CurrentMouse.Y << endl;
//            cout << PreviousMouse.X << ", " << PreviousMouse.Y << endl;
            if (CurrentMouse != PreviousMouse) {
                auto v = CurrentMouse - PreviousMouse;
                cout << v.X << ", " << v.Y << endl;
            }
        }
    }

    void Draw() override {
        static CC::Float32 r = 0;
        static CC::Float32 tWidth = 0;
        CC::Graphics::SetColor(255, 0, 0, 255);

//        CC::Graphics::Line(0, 0, 50, 50);  // Draw one line

        CC::Graphics::Line({{0, 0}, {50, 50}, {100, 0}}); // Draw many lines

        CC::Graphics::Draw(&img, 0, 0, r); // Draw image with rotation
        r = r > 358 ? 0.0 : r + 1.0f;
        tWidth = tWidth > 200 ? 0.0 : tWidth + 1.0f;

        Vertex vertex[] = {
                {{100, 150, r}, Colors::Red},
                {{tWidth, 100, 0}, Colors::Green},
                {{100, 100, 0}, Colors::Blue}
        };

//        CC::Graphics::Geometry2D(nullptr, &vertex[0], 3, nullptr, 0);
        CC::Graphics::Geometry(nullptr, &vertex[0], 3, nullptr, 0);


        CC::Rect rect = CC::Rect::Make(100, 200, 100, 50);
        rect.SetColor({106, 136, 255, 255}, {106, 136, 255, 255}, {255, 255, 255, 255}, {255, 255, 255, 255});
        CC::Graphics::Rectangle(rect, true);

//        Vertex vertex[] = {
//            {{100, 150, r}, Colors::Red},
//            {{tWidth, 100, 0}, Colors::Green},
//            {{100, 100, 0}, Colors::Blue}
//        };
//
////        CC::Graphics::Geometry2D(nullptr, &vertex[0], 3, nullptr, 0);
//        CC::Graphics::Geometry(nullptr, &vertex[0], 3, nullptr, 0);

        CC::Graphics::Print("那你很棒棒哦!", &font, 200, 200);
    }

    void onMouseMotion(CC::UIMouseMotionEvent &event) override {
//        cout << event.X << ", " << event.Y << endl;

        if (ButtonStatus) {
            CurrentMouse = Vector2{event.X * 1.f, event.Y * 1.f};
        }
    }

    void onMouseButton(CC::UIMouseButtonEvent &event, bool isReleased) override {
        if (!isReleased) {
            ButtonStatus = true;
            CurrentMouse = PreviousMouse = Vector2{event.X * 1.f, event.Y * 1.f};
            cout << "Start Mouse" << endl;

        } else {
            ButtonStatus = false;
            CurrentMouse = PreviousMouse = Vector2{event.X * 1.f, event.Y * 1.f};
            cout << "End Mouse" << endl;
        }
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

        // Initialize resources
        if (img.Open(Renderer::GetWithWindow(&mainWindow), "hamster.png")) cout << "Image load OK" << endl;

        if (canvas.Open(Renderer::GetWithWindow(&mainWindow), 640, 480)) cout << "Canvas load OK" << endl;

        if (font.Open(hkyt_ttf, hkyt_ttf_len, 15)) cout << "Font load OK" << endl;
//        if (font.Open("/System/Library/Fonts/PingFang.ttc", 15)) cout << "Font load OK" << endl;
    }

    void onClose() override {
        Application::onClose();
        mainWindow.Close();
    }
};

int main() {
    MyApp app;
    ButtonStatus = false;

    printf("ERROR --- %d%d%d\n", hkyt_ttf[10], hkyt_ttf[20], hkyt_ttf[30]);

    if (!app.Open()) {
        cout << "Error!" << endl;
        return -1;
    }

//    app.Open("nihao", screen.width / 2 - 50, screen.height / 2 - 50, 200, 200, 0);

    app.Run();

    return 0;
}
