#ifndef __INPUT_DEVICE_UDP_HPP__
#define __INPUT_DEVICE_UDP_HPP__

#include <string>
#include <vector>
#include <netinet/in.h>
#include <cstdint>
#define MAXLINEOUT 1024

class InputDeviceUDP {
private:
    uint16_t udpPort;  // Port sur lequel on va se connecter
    int sockfd;        // Socket du client
    sockaddr_in servaddr; // Adresse du serveur
    char buffer[1024];     // Buffer pour recevoir les données
    bool SendingAndREceiving = false;

    // Struct pour stocker les informations sur chaque équipe
    struct TeamInfo {
        std::string name;
        uint32_t score;
    };

    std::vector<TeamInfo> teams; // Vecteur des équipes (nom + score)
    uint32_t numTeams; // Nombre d'équipes

public:
    // Constructeur, avec port par défaut de 6667
    InputDeviceUDP(uint16_t port = 6667);

    // Destructeur
    ~InputDeviceUDP();

    // Envoie la requête "update" au serveur et reçoit les données en retour
    void sendAndReceiveData();

    // Méthodes getter pour accéder aux données
    uint32_t getNumTeams() const { return numTeams; }
    const std::vector<TeamInfo>& getTeams() const { return teams; }

private:
    // Déconstruire la chaîne reçue en différents composants
    void parseData(const std::string& data);
};

#endif  /* __INPUT_DEVICE_UDP_HPP__ */
