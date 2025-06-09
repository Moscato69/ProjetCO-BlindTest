#include "InputDeviceUDP.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>  // Nécessaire pour std::istringstream
#include <cerrno>   // Pour errno

InputDeviceUDP::InputDeviceUDP(uint16_t port) : udpPort(port), sockfd(-1), numTeams(0) {
    std::cout << "Creating UDP connection" << std::endl;
    // Créer le socket pour le client
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur lors de la création du socket client : " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "Descripteur de socket : " << sockfd << std::endl;
    if (sockfd < 0) {
        std::cerr << "Erreur lors de la création du socket : " << strerror(errno) << std::endl;
        return;
    }

    // Configuration de l'adresse du serveur
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(udpPort);
    servaddr.sin_addr.s_addr = INADDR_ANY;


    std::cout << "Socket créé et lié sur le port " << udpPort << std::endl;
}

InputDeviceUDP::~InputDeviceUDP() {
    if (sockfd >= 0 and !SendingAndREceiving    ) {
        close(sockfd);
        std::cout << "Socket fermé" << std::endl;
    }
}

void InputDeviceUDP::sendAndReceiveData() {
    SendingAndREceiving = true;
    std::cout << "Début de sendAndReceiveData" << std::endl;
    char buffer[MAXLINEOUT] = {0};

    sockaddr_in cliaddr{};
    socklen_t len = sizeof(cliaddr);

    // Vérification que le socket est valide
    if (sockfd < 0) {
        std::cerr << "Erreur : socket non initialisé" << std::endl;
        return;
    }

    // Initialisation correcte de l'adresse client avant l'envoi
    memset(&cliaddr, 0, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(6667);  // Port cible
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");




    // Envoi de l'update avant la réception
    std::string message = "update";
    int sendResult = sendto(sockfd, message.c_str(), message.size(), 0,
                            (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    if (sendResult < 0) {
        std::cerr << "Erreur lors de l'envoi : " << strerror(errno) << std::endl;
        return;
    }
    std::cout << "Message envoyé : " << message << std::endl;

    // Réinitialiser les équipes à chaque appel
    teams.clear();
    teams.resize(8);  // Toujours 8 équipes
    std::cout << "Attente des données..." << std::endl;


    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    int n = recvfrom(sockfd, buffer, MAXLINEOUT, 0, (struct sockaddr*)&cliaddr, &len);

    if (n < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "Timeout atteint : aucune donnée reçue dans le délai imparti." << std::endl;
        } else {
            std::cerr << "Erreur de réception : " << strerror(errno) << std::endl;
        }
        return;  // Ne pas continuer en cas de réception échouée

    }





    if (n < 0) {
        std::cerr << "Erreur de réception : " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "Données reçues" << std::endl;

    // Vérification si le nombre d'octets reçus est nul
    if (n == 0) {
        std::cerr << "Erreur : données reçues vides" << std::endl;
        return;
    }

    buffer[n] = '\0';
    std::string received(buffer);
    std::cout << "Données reçues : " << received << std::endl;

    // Si les données sont vides après conversion en chaîne
    if (received.empty()) {
        std::cerr << "Erreur : données reçues vides après conversion" << std::endl;
        return;
    }

    // Traitement des données reçues
    std::istringstream iss(received);
    std::string token;
    size_t i = 0;
    while (std::getline(iss, token, ';')) {

        if (i == 0) {
            try {
                numTeams = std::stoi(token);
                if (numTeams < 0 || numTeams > 8) {
                    std::cerr << "Erreur : nombre d'équipes invalide" << std::endl;
                    return;
                }
            } catch (...) {
                std::cerr << "Erreur : nombre d'équipes non valide" << std::endl;
                return;
            }
        } else if (i % 2 == 1) {
            teams[(i - 1) / 2].name = token;
        } else {
            try {
                teams[(i - 1) / 2].score = std::stoi(token);
            } catch (...) {
                std::cerr << "Erreur : score non valide" << std::endl;
                return;
            }
        }
        ++i;
    }

    std::cout << "Traitement terminé." << std::endl;
    std::cout<<teams[0].name << " " << teams[0].score<<std::endl;
    std::cout<<teams[1].name << " " << teams[1].score<<std::endl;
    std::cout<<teams[2].name << " " << teams[2].score<<std::endl;
    std::cout<<teams[3].name << " " << teams[3].score<<std::endl;
    std::cout<<teams[4].name << " " << teams[4].score<<std::endl;
    std::cout<<teams[5].name << " " << teams[5].score<<std::endl;
    std::cout<<teams[6].name << " " << teams[6].score<<std::endl;
    std::cout<<teams[7].name << " " << teams[7].score<<std::endl;
    SendingAndREceiving = false;

}


void InputDeviceUDP::parseData(const std::string& data) {
    size_t pos = 0;
    numTeams = std::stoi(data.substr(pos, data.find(';', pos) - pos));
    pos = data.find(';', pos) + 1;

    // Réinitialiser toutes les équipes avec des valeurs par défaut
    for (auto& team : teams) {
        team.name = "";
        team.score = 0;
    }

    // Mettre à jour uniquement les équipes reçues
    for (size_t i = 0; i < numTeams && i < 8; ++i) {
        teams[i].name = data.substr(pos, data.find(';', pos) - pos);
        pos = data.find(';', pos) + 1;

        teams[i].score = std::stoi(data.substr(pos, data.find(';', pos) - pos));
        pos = data.find(';', pos) + 1;
    }

    // Réinitialiser les équipes en trop si le nombre d'équipes est inférieur à 8
    for (size_t i = numTeams; i < 8; ++i) {
        teams[i].name = "";
        teams[i].score = 0;
    }
}
