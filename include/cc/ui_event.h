//
// Created by liangjie on 2024/3/29.
//

#ifndef CHOCO_CPP_UI_EVENT_H
#define CHOCO_CPP_UI_EVENT_H

#include "cc/types.h"
#include "cc/rect.h"

namespace CC {
    struct UIEventType {
        static const UInt32 FirstEvent; // 0
        static const UInt32 Quit; // 0x100 - App events
        static const UInt32 AppTerminating;
        static const UInt32 AppLowMemory;
        static const UInt32 AppWillEnterBackground;
        static const UInt32 AppDidEnterBackground;
        static const UInt32 AppWillEnterForeground;
        static const UInt32 AppDidEnterForeground;
        static const UInt32 LocaleChanged;
        static const UInt32 DisplayEvent; // 0x150 Display events
        static const UInt32 WindowEvent; // 0x200 Window events
        static const UInt32 SysWMEvent;
        static const UInt32 KeyDown; // 0x300 Keyboard events
        static const UInt32 KeyUp;
        static const UInt32 TextEditing;
        static const UInt32 TextInput;
        static const UInt32 KeymapChanged;
        static const UInt32 TextEditingExt;
        static const UInt32 MouseMotion; // 0x400 Mouse events
        static const UInt32 MouseButtonDown;
        static const UInt32 MouseButtonUp;
        static const UInt32 MouseWheel;
        static const UInt32 JoyAxisMotion; // 0x600 Joystick events
        static const UInt32 JoyBallMotion;
        static const UInt32 JoyHatMotion;
        static const UInt32 JoyButtonDown;
        static const UInt32 JoyButtonUp;
        static const UInt32 JoyDeviceAdded;
        static const UInt32 JoyDeviceRemoved;
        static const UInt32 JoyBatteryUpdated;
        static const UInt32 ControllerAxisMotion; // 0x650 Game controller events
        static const UInt32 ControllerButtonDown;
        static const UInt32 ControllerButtonUp;
        static const UInt32 ControllerDeviceAdded;
        static const UInt32 ControllerDeviceRemoved;
        static const UInt32 ControllerDeviceRemapped;
        static const UInt32 ControllerTouchpadDown;
        static const UInt32 ControllerTouchpadMotion;
        static const UInt32 ControllerTouchpadUp;
        static const UInt32 ControllerSensorUpdate;
        static const UInt32 FingerDown; // 0x700 Touch events
        static const UInt32 FingerUp;
        static const UInt32 FingerMotion;
        static const UInt32 DollarGesture; // 0x800 Gesture events
        static const UInt32 DollarRecord;
        static const UInt32 MultiGesture;
        static const UInt32 ClipboardUpdate; // 0x900 Clipboard events
        static const UInt32 DropFile; // 0x1000 Drag and drop events
        static const UInt32 DropText;
        static const UInt32 DropBegin;
        static const UInt32 DropComplete;
        static const UInt32 AudioDeviceAdded; // 0x1100 Audio hot-plug events
        static const UInt32 AudioDeviceRemoved;
        static const UInt32 SensorUpdate; // 0x1200 Sensor events
        static const UInt32 RenderTargetsReset; // 0x2000 Render events
        static const UInt32 RenderDeviceReset;
        static const UInt32 PollSentinel; // 0x7F00 Internal events
        static const UInt32 UserEvent; // 0x8000 User defined events
        static const UInt32 LastEvent; // Only for bounding internal arrays
    };

    struct UIKeyboardEvent {
        UInt32 Timestamp;   /**< In milliseconds */
        UInt32 WindowID;    /**< The window with keyboard focus, if any */
        UInt8 State;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
        UInt8 Repeat;       /**< Non-zero if this is a key repeat */
    };

    struct UIMouseMotionEvent {
        UInt32 Timestamp;   /**< In milliseconds */
        UInt32 WindowID;    /**< The window with mouse focus, if any */
        UInt32 MouseID;       /**< The mouse instance id */
        UInt32 State;       /**< The current button state */
        Int32 X;           /**< X coordinate, relative to window */
        Int32 Y;           /**< Y coordinate, relative to window */
        Int32 XRel;        /**< The relative motion in the X direction */
        Int32 YRel;        /**< The relative motion in the Y direction */
    };

    struct UIMouseButtonEvent {
        UInt32 Timestamp;   /**< In milliseconds */
        UInt32 WindowID;    /**< The window with mouse focus, if any */
        UInt32 MouseID;       /**< The mouse instance id */
        UInt8 Button;       /**< The mouse button index */
        UInt8 State;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
        UInt8 Clicks;       /**< 1 for single-click, 2 for double-click, etc. */
        Int32 X;           /**< X coordinate, relative to window */
        Int32 Y;           /**< Y coordinate, relative to window */
    };

    struct UIMouseWheelEvent {
        UInt32 Timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
        UInt32 WindowID;    /**< The window with mouse focus, if any */
        UInt32 MouseID;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
        Int32 X;           /**< The amount scrolled horizontally, positive to the right and negative to the left */
        Int32 Y;           /**< The amount scrolled vertically, positive away from the user and negative toward the user */
        UInt32 Direction;   /**< Set to one of the SDL_MOUSEWHEEL_* defines. When FLIPPED the values in X and Y will be opposite. Multiply by -1 to change them back */
        float PreciseX;     /**< The amount scrolled horizontally, positive to the right and negative to the left, with float precision (added in 2.0.18) */
        float PreciseY;     /**< The amount scrolled vertically, positive away from the user and negative toward the user, with float precision (added in 2.0.18) */
        Int32 MouseX;      /**< X coordinate, relative to window (added in 2.26.0) */
        Int32 MouseY;      /**< Y coordinate, relative to window (added in 2.26.0) */
    };

    struct UIWindowEvent {
        struct EventType {
            static const UInt8 None;
            static const UInt8 Shown;
            static const UInt8 Hidden;
            static const UInt8 Exposed;
            static const UInt8 Moved;
            static const UInt8 Resized;
            static const UInt8 SizeChanged;
            static const UInt8 Minimized;
            static const UInt8 Maximized;
            static const UInt8 Restored;
            static const UInt8 Enter;
            static const UInt8 Leave;
            static const UInt8 FocusGained;
            static const UInt8 FocusLost;
            static const UInt8 Close;
            static const UInt8 TakeFocus;
            static const UInt8 HitTest;
            static const UInt8 ICCProfChanged;
            static const UInt8 DisplayChanged;
        };
        UInt32 Timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
        UInt32 WindowID;    /**< The associated window */
        UInt8 Event;        /**< ::EventType */
    };

    struct UIEvent {
        typedef CC_ENUM(int, ButtonState) {
            ButtonStateReleased = 0,
            ButtonStatePressed  = 1
        };

        UInt32 Type;

        union {
            UIKeyboardEvent    key;
            UIMouseMotionEvent motion;
            UIMouseButtonEvent button;
            UIMouseWheelEvent  wheel;
            UIWindowEvent      window;
        };
    };
}

#endif //CHOCO_CPP_UI_EVENT_H
