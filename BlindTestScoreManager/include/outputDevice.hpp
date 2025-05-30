#ifndef __OUTPUT_DEVICE_HPP__
#define __OUTPUT_DEVICE_HPP__

#include "Team.hpp"
#include <print>
#include "ScoreManager.hpp"
#include <thread>
#include <unordered_map>
#include <netinet/in.h>
#include <thread>
#include <string>

constexpr uint16_t defaultUdpPortOut = 6667;  /** Server's default UDP port */
constexpr int MAXLINEOUT = 1024;               /** Taille maximale des messages UDP */

class ScoreManager;

class OutputDevice {
public:
    OutputDevice() = default;
    virtual ~OutputDevice() = default;

    virtual void update(const std::unordered_map<std::string, Team>& teamMap, uint32_t tailleMap) = 0;
};

class OutputDeviceUDP : public OutputDevice {
private:
    bool started = false;
    int sockfd;                     // Descripteur du socket
    sockaddr_in servaddr{};         // Adresse du serveur
    std::jthread udpServerThread;   // Thread du serveur
    std::string chaine;             // Chaîne à envoyer
    uint16_t udpPort;               // Port du serveur UDP

public:
    explicit OutputDeviceUDP(uint16_t port = defaultUdpPortOut) : udpPort(port), sockfd(-1) {}
    virtual ~OutputDeviceUDP();

    void start();
    void _serverThread();
    virtual void update(const std::unordered_map<std::string, Team>& teamMap, uint32_t tailleMap) override;
};

#endif  /* __OUTPUT_DEVICE_HPP__ */
