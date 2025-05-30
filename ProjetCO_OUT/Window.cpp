#include "Window.h"
#include "FrameGrid.hpp"
#include "KeyboardWatcher.hpp"

bool Window::OnInit()
{
    //je veux lancer la méthode StartKeyboardWatcher de la classe Keyboardwatcher

    StartKeyboardWatcher();

    auto* frame = new FrameGrid("Affichage des scores");
    SetTopWindow(frame); // Important pour wxTheApp->GetTopWindow() utilisé dans le watcher
    frame->Show(true);
    return true;
}

int Window::OnExit()
{
    StopKeyboardWatcher();
    return 0;
}
