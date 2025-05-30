#include "InputDevice.hpp"
#include "outputDevice.hpp"

int main(){

    OutputDeviceUDP   Screen{};
    ScoreManager    Manager{Screen};
    udp_server_InputDevice indev{Manager};
    //udp_server_OutputDevice outdev{Manager};


    indev.Start();
    //outdev.Start();

}