#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>

#include "TeamsData.hpp"

#include "Window.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(Window);

/*
int main() {
    // Déclaration de 8 équipes
    std:
        std::vector<TeamsData> Equipes(8);
        std::string noms[] = {"Equipe A", "Equipe B", "Equipe C", "Equipe D",
                         "Equipe E", "Equipe F", "Equipe G", "Equipe H"};

    for (int i = 0; i < 8; ++i) {
        Equipes[i].setNom(noms[i]);
        std::cout << "Nom de l'équipe " << i << " : " << Equipes[i].GetNom() << std::endl;
        Equipes[i].setNuméro(i);
        std::cout << "Nom de l'équipe " << i << " : " << Equipes[i].GetNuméro() << std::endl;
        Equipes[i].setScore(i*100);
        std::cout << "Nom de l'équipe " << i << " : " << Equipes[i].GetScore() << std::endl;
    }
    std::cout << "Etape 1 : Création des équipes terminée" << std::endl;

    // Création du socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur de création du socket" << std::endl;
        return 1;
    }
    std::cout << "Etape 2 : Création du socket terminée" << std::endl;

    // Configuration du serveur
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);  // Port de communication
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Lier le socket à l'adresse et au port
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Erreur de binding" << std::endl;
        close(sockfd);
        return 1;
    }

    // Écouter les connexions entrantes
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Erreur de listen" << std::endl;
        close(sockfd);
        return 1;
    }
    std::cout << "Etape 3 : Configuration du serveur terminée" << std::endl;

    // Accepter une connexion entrante
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
    if (newsockfd < 0) {
        std::cerr << "Erreur d'acceptation" << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Etape 4 : Connexion acceptée" << std::endl;

    // Envoi des données des équipes
    for (const auto& equipe : Equipes) {
        char buffer[256];  // Assurez-vous que le buffer est assez grand
        equipe.serialize(buffer);
        ssize_t bytes_sent = send(newsockfd, buffer, sizeof(buffer), 0);
        if (bytes_sent < 0) {
            std::cerr << "Erreur lors de l'envoi des données" << std::endl;
            close(newsockfd);
            close(sockfd);
            return 1;
        }
    }

    std::cout << "Données envoyées avec succès" << std::endl;

    // Fermer les sockets
    close(newsockfd);
    close(sockfd);
    return 0;
}


// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.*/