//
// Created by liangjie on 2024/3/29.
//

#include "cc/ui_event.h"
#include "SDL2/SDL.h"

namespace CC {
    // UIEvents
    const UInt32 UIEventType::FirstEvent = SDL_FIRSTEVENT;
    const UInt32 UIEventType::Quit = SDL_QUIT;
    const UInt32 UIEventType::AppTerminating = SDL_APP_TERMINATING;
    const UInt32 UIEventType::AppLowMemory = SDL_APP_LOWMEMORY;
    const UInt32 UIEventType::AppWillEnterBackground = SDL_APP_WILLENTERBACKGROUND;
    const UInt32 UIEventType::AppDidEnterBackground = SDL_APP_DIDENTERBACKGROUND;
    const UInt32 UIEventType::AppWillEnterForeground = SDL_APP_WILLENTERFOREGROUND;
    const UInt32 UIEventType::AppDidEnterForeground = SDL_APP_DIDENTERFOREGROUND;
    const UInt32 UIEventType::LocaleChanged = SDL_LOCALECHANGED;
    const UInt32 UIEventType::DisplayEvent = SDL_DISPLAYEVENT;
    const UInt32 UIEventType::WindowEvent = SDL_WINDOWEVENT;
    const UInt32 UIEventType::SysWMEvent = SDL_SYSWMEVENT;
    const UInt32 UIEventType::KeyDown = SDL_KEYDOWN;
    const UInt32 UIEventType::KeyUp = SDL_KEYUP;
    const UInt32 UIEventType::TextEditing = SDL_TEXTEDITING;
    const UInt32 UIEventType::TextInput = SDL_TEXTINPUT;
    const UInt32 UIEventType::KeymapChanged = SDL_KEYMAPCHANGED;
    const UInt32 UIEventType::TextEditingExt = SDL_TEXTEDITING_EXT;
    const UInt32 UIEventType::MouseMotion = SDL_MOUSEMOTION;
    const UInt32 UIEventType::MouseButtonDown = SDL_MOUSEBUTTONDOWN;
    const UInt32 UIEventType::MouseButtonUp = SDL_MOUSEBUTTONUP;
    const UInt32 UIEventType::MouseWheel = SDL_MOUSEWHEEL;
    const UInt32 UIEventType::JoyAxisMotion = SDL_JOYAXISMOTION;
    const UInt32 UIEventType::JoyBallMotion = SDL_JOYBALLMOTION;
    const UInt32 UIEventType::JoyHatMotion = SDL_JOYHATMOTION;
    const UInt32 UIEventType::JoyButtonDown = SDL_JOYBUTTONDOWN;
    const UInt32 UIEventType::JoyButtonUp = SDL_JOYBUTTONUP;
    const UInt32 UIEventType::JoyDeviceAdded = SDL_JOYDEVICEADDED;
    const UInt32 UIEventType::JoyDeviceRemoved = SDL_JOYDEVICEREMOVED;
    const UInt32 UIEventType::JoyBatteryUpdated = SDL_JOYBATTERYUPDATED;
    const UInt32 UIEventType::ControllerAxisMotion = SDL_CONTROLLERAXISMOTION;
    const UInt32 UIEventType::ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN;
    const UInt32 UIEventType::ControllerButtonUp = SDL_CONTROLLERBUTTONUP;
    const UInt32 UIEventType::ControllerDeviceAdded = SDL_CONTROLLERDEVICEADDED;
    const UInt32 UIEventType::ControllerDeviceRemoved = SDL_CONTROLLERDEVICEREMOVED;
    const UInt32 UIEventType::ControllerDeviceRemapped = SDL_CONTROLLERDEVICEREMAPPED;
    const UInt32 UIEventType::ControllerTouchpadDown = SDL_CONTROLLERTOUCHPADDOWN;
    const UInt32 UIEventType::ControllerTouchpadMotion = SDL_CONTROLLERTOUCHPADMOTION;
    const UInt32 UIEventType::ControllerTouchpadUp = SDL_CONTROLLERTOUCHPADUP;
    const UInt32 UIEventType::ControllerSensorUpdate = SDL_CONTROLLERSENSORUPDATE;
    const UInt32 UIEventType::FingerDown = SDL_FINGERDOWN;
    const UInt32 UIEventType::FingerUp = SDL_FINGERUP;
    const UInt32 UIEventType::FingerMotion = SDL_FINGERMOTION;
    const UInt32 UIEventType::DollarGesture = SDL_DOLLARGESTURE;
    const UInt32 UIEventType::DollarRecord = SDL_DOLLARRECORD;
    const UInt32 UIEventType::MultiGesture = SDL_MULTIGESTURE;
    const UInt32 UIEventType::ClipboardUpdate = SDL_CLIPBOARDUPDATE;
    const UInt32 UIEventType::DropFile = SDL_DROPFILE;
    const UInt32 UIEventType::DropText = SDL_DROPTEXT;
    const UInt32 UIEventType::DropBegin = SDL_DROPBEGIN;
    const UInt32 UIEventType::DropComplete = SDL_DROPCOMPLETE;
    const UInt32 UIEventType::AudioDeviceAdded = SDL_AUDIODEVICEADDED;
    const UInt32 UIEventType::AudioDeviceRemoved = SDL_AUDIODEVICEREMOVED;
    const UInt32 UIEventType::SensorUpdate = SDL_SENSORUPDATE;
    const UInt32 UIEventType::RenderTargetsReset = SDL_RENDER_TARGETS_RESET;
    const UInt32 UIEventType::RenderDeviceReset = SDL_RENDER_DEVICE_RESET;
    const UInt32 UIEventType::PollSentinel = SDL_POLLSENTINEL;
    const UInt32 UIEventType::UserEvent = SDL_USEREVENT;
    const UInt32 UIEventType::LastEvent = SDL_LASTEVENT;
}
