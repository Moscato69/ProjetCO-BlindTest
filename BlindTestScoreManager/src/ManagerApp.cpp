#include "InputDevice.hpp"
#include "outputDevice.hpp"

int main(){

    OutputDeviceUDP   Screen{};
    ScoreManager    Manager{Screen};
    udp_server_InputDevice indev{Manager};


    indev.Start();
    Manager.updateScreen();

}