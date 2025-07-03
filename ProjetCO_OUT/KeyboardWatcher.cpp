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

static constexpr int ID_KEY_COMBINAISON_CAPTURED = wxID_HIGHEST + 1;

static std::atomic<bool> running = false;
static std::thread watcherThread;



void WatchKeyboard()
{
    Display* display = XOpenDisplay(nullptr);
    if (!display) return;
    Window root = DefaultRootWindow(display);

    // Calcul des keycodes
    int codeF12 = XKeysymToKeycode(display, XK_F12);
    int codeW   = XKeysymToKeycode(display, XK_W);

    // Masks à prendre en compte pour NumLock/CapsLock
    const unsigned int masks[] = {
        0,
        LockMask,
        Mod2Mask,
        LockMask | Mod2Mask
    };

    // On grab les deux touches avec chaque combinaison de lock
    for (auto m : masks) {
        XGrabKey(display, codeF12, m, root, True, GrabModeAsync, GrabModeAsync);
        XGrabKey(display, codeW,   m, root, True, GrabModeAsync, GrabModeAsync);
    }
    XSelectInput(display, root, KeyPressMask);
    XSync(display, False);  // assure que tout est envoyé au serveur

    std::atomic<bool> keyF12{false}, keyW{false};
    XEvent ev;
    while (running) {
        while (XPending(display) && running) {
            XNextEvent(display, &ev);

            if (ev.type == KeyPress) {
                if (ev.xkey.keycode == codeF12) keyF12 = true;
                if (ev.xkey.keycode == codeW)   keyW   = true;

                if (keyF12 && keyW) {
                    // combinaison détectée
                    wxCommandEvent evt(wxEVT_MENU, ID_KEY_COMBINAISON_CAPTURED);
                    wxQueueEvent(wxTheApp->GetTopWindow(), evt.Clone());
                    keyF12 = keyW = false;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // On fait l'ungrab proprement
    for (auto m : masks) {
        XUngrabKey(display, codeF12, m, root);
        XUngrabKey(display, codeW,   m, root);
    }
    XCloseDisplay(display);
}




void StartKeyboardWatcher()
{
    if (running)
        return; // déjà lancé
    std::cout << "Starting watcher" << std::endl;
    running = true;
    watcherThread = std::thread(WatchKeyboard);
}

void StopKeyboardWatcher()
{
    running = false;

    std::cout << "Stopping watcher" << std::endl;
    if (watcherThread.joinable())
        watcherThread.join();

}
