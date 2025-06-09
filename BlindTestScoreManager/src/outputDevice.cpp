#include "outputDevice.hpp"
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>


#define MAXLINEOUT 1024

void OutputDeviceUDP::update(const std::unordered_map<std::string, Team>& teamMap, uint32_t tailleMap) {
    if (!this->started) {
        this->start();
    }

    // Réinitialiser la chaîne pour chaque mise à jour
    this->chaine.clear();

    // Ajouter le nombre d'équipes au début de la chaîne
    this->chaine += std::to_string(tailleMap) + ";";  // Taille suivie d'un séparateur

    // Parcourir chaque équipe et ajouter son nom et score à la chaîne
    for (auto item : teamMap) {
        // Ajouter le nom de l'équipe
        this->chaine += item.second.getName() + ";";
        // Ajouter le score de l'équipe
        this->chaine += std::to_string(item.second.getLocalScoreRef().getPoints()) + ";";
        // Affichage pour vérification
        std::cout << "DOD : Team Name = " << item.second.getName()
                  << " - Score = " << item.second.getLocalScoreRef().getPoints() << std::endl;
    }

    // Afficher la chaîne complète
    std::cout << "Chaine : " << this->chaine << std::endl;


}

void OutputDeviceUDP::start() {
    // Initialisation du socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) throw std::runtime_error("Erreur lors de la création du socket.");

    // Remplissage des informations du serveur
    std::memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;     // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(this->udpPort);

    // Liaison du socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        throw std::runtime_error("Erreur lors de la liaison du socket.");
    }

    std::println(std::clog, "UDP Server initialized (port : {0:d})", static_cast<int>(this->udpPort));

    // Démarrage du thread serveur UDP
    this->udpServerThread = std::jthread(&OutputDeviceUDP::_serverThread, this);
    this->started = true;
}

void OutputDeviceUDP::_serverThread() {
    char buffer[MAXLINEOUT];
    sockaddr_in cliaddr{};
    socklen_t len = sizeof(cliaddr);

    while (true) {
        int n = recvfrom(sockfd, buffer, MAXLINEOUT, MSG_WAITALL,
                         (struct sockaddr*)&cliaddr, &len);
        if (n < 0) {
            std::cerr << "Erreur de réception" << std::endl;
            continue;
        }
        buffer[n] = '\0';
        std::string received(buffer);
        std::cout << "Message reçu : " << received << std::endl;

        // Envoyer la chaîne par UDP au client qui a envoyé le message
        ssize_t send_len = sendto(sockfd, this->chaine.c_str(), this->chaine.size(), 0,
                                  (const struct sockaddr*)&cliaddr, sizeof(cliaddr));
        if (send_len < 0) {
            std::cerr << "Erreur d'envoi de la chaîne" << std::endl;
        } else {
            std::println(std::clog, "Données envoyées : {}", this->chaine);
        }
    }
}

OutputDeviceUDP::~OutputDeviceUDP() {
    if (sockfd >= 0) {
        close(sockfd);
        std::println(std::clog, "Socket fermé");
        this->started = false;
    }
}