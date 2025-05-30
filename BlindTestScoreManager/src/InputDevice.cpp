#include "InputDevice.hpp"

//----------------------------------------------------------------------------
/**     concrete input device   */
//----------------------------------------------------------------------------
void    udp_server_InputDevice::_serverThread(){
    int sockfd;
    sockaddr_in     servaddr{};
    sockaddr_in     cliaddr{};
    char buffer[MAXLINEIN];
    std::println(std::clog,"UDP Server starting (port : {0:d})",static_cast<int>(this->getUdpPort()));
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) throw NetworkExceptionIn("Error while creating socket.");

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(this->getUdpPort());

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) throw NetworkExceptionIn("Error while binding the socket.");
    socklen_t len = sizeof(cliaddr); //len is value/result;

    int n{0};

    while(true){
        n = recvfrom(sockfd, (char *)buffer, MAXLINEIN, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        std::string stmp{buffer};
        std::erase(stmp,'\n');
        std::erase(stmp,'\r');
        std::println(std::clog,"Message received = {0:}",stmp);
        this->DecodeTrame(stmp);
    }
}

void    udp_server_InputDevice::DecodeTrame(const std::string &frame){
    std::string teamName{};

    if (frame.starts_with("lsteams")){
        std::println(std::clog,"Listing Teams");
        this->Manager.listTeamNames();
    }
    else if (frame.starts_with("add;")){
        teamName = frame.substr(4);    
        std::println(std::clog,"Team Name = {0:}",teamName);
        this->Manager.addTeam(teamName);
    }
    else if (frame.starts_with("del;")){
        teamName = frame.substr(4);    
        std::println(std::clog,"Team Name = {0:}",teamName);
        this->Manager.removeTeam(teamName);
    }
    else if (frame.starts_with("inc;")){
        teamName = frame.substr(4);    
        std::println(std::clog,"INC {0:}",teamName);
        this->Manager.incTeamScore(teamName);
    }
    else if (frame.starts_with("dec;")){
        teamName = frame.substr(4);    
        std::println(std::clog,"DEC {0:}",teamName);
        this->Manager.decTeamScore(teamName);
    }
    this->Manager.updateScreen();
}


void    udp_server_InputDevice::Start(){
    this->udpServerThread = std::jthread(&udp_server_InputDevice::_serverThread,this);
}

