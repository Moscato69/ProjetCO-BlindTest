//
// Created by matthias on 29/05/25.
//

#include "KeyboardWatcher.hpp"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <thread>
#include <atomic>
#include <wx/wx.h>
#include <chrono>
#include <thread>

static constexpr int ID_KEY_COMBINAISON_CAPTURED = wxID_HIGHEST + 1;

static std::atomic<bool> running = false;
static std::thread watcherThread;


void WatchKeyboard()
{
    Display* display = XOpenDisplay(nullptr);
    if (!display) return;
    bool Key_F12_Captured = false;
    bool Key_W_Captured = false;
    Window root = DefaultRootWindow(display);
    int Keycode_F12 = XKeysymToKeycode(display, XK_F12);
    int Keycode_W = XKeysymToKeycode(display, XK_W);
    // Grab F12 and W key on root window with any modifier
    XGrabKey(display, Keycode_F12, AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, Keycode_W, AnyModifier, root, True, GrabModeAsync, GrabModeAsync);
    XSelectInput(display, root, KeyPressMask);

    // Set X to non-blocking so XNextEvent won’t hang forever
    XEvent event;

    // Make sure XPending is used to check for events without blocking
    while (running)
    {
        while (XPending(display) && running)
        {
            XNextEvent(display, &event);
            if (event.type == KeyPress && event.xkey.keycode == Keycode_F12)
            {
                Key_F12_Captured = true;

                std::cout << event.xkey.keycode << std::endl;
            } else if (event.type == KeyPress && event.xkey.keycode == Keycode_W)
            {
                Key_W_Captured = true;
                std::cout << event.xkey.keycode << std::endl;
            }

            if (Key_F12_Captured && Key_W_Captured)
            {
                std::cout <<"arrêt " << std::endl;
                // Post event to wxWidgets main window
                wxCommandEvent evt(wxEVT_MENU, ID_KEY_COMBINAISON_CAPTURED);
                wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
                Key_F12_Captured = false;
                Key_W_Captured = false;
            }


        }
        // Small sleep to avoid busy loop
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    XUngrabKey(display, Keycode_F12, AnyModifier, root);
    XCloseDisplay(display);
}



void StartKeyboardWatcher()
{
    if (running)
        return; // déjà lancé

    running = true;
    watcherThread = std::thread(WatchKeyboard);
}

void StopKeyboardWatcher()
{
    running = false;
    if (watcherThread.joinable())
        watcherThread.join();
}
