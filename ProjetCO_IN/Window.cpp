#include "Window.h"
#include "Frame.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h> // Pour socket, sendto, etc.
#define SERVER_IP "127.0.0.1" // Adresse IP du serveur
#define SERVER_PORT 6666      // Port du serveur
#define BUFFER_SIZE 80      // Taille du tampon pour les messages

bool Window::OnInit()
{
    auto* frame = new Frame("Score manager");
    frame->Show(true);
    return true;
}
