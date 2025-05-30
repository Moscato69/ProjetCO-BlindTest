#ifndef __INPUT_DEVICE_HPP__
#define __INPUT_DEVICE_HPP__

#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <print>

#include "ScoreManager.hpp"

//----------------------------------------------------------------------------
class InputDevice{
    private:

    protected:
        ScoreManager    &Manager;   /** reference to the ScoreManager object */

    public:
        /**
         * @brief default Ctor - DELETED
         */
        InputDevice() = delete;   


        /**
         * @brief Dtor - defaulted
         */
        virtual ~InputDevice() = default;

        /**
         * @brief Standard Ctor
         * @param ScoreManager& manager : reference to the ScoreManager to use 
         */
        InputDevice(ScoreManager &manager):Manager{manager}{};

        /**
         * @brief Pure virtual function, launching the input device work
         */
        virtual     void    Start() = 0;


};
//----------------------------------------------------------------------------
constexpr   uint16_t    defaultUdpPortIn = 6666;  /** Server's default UDP port */
constexpr   int         MAXLINEIN = 80;

/**
 * @brief General exception class for network errors 
 */
class   NetworkExceptionIn : public std::runtime_error{
    public:
        explicit NetworkExceptionIn(const std::string& what_arg):std::runtime_error(what_arg){};
} ;

/**
 * @brief   udp_server_InputDevice class
 * 
 * Protocole applicatif
 *      -   lsteams : le serveur logue la liste des équipes (test feature)
 *      -   add;team : ajoute une équipe
 *      -   del;team : supprime une équipe
 *      -   inc;team : Ajoute un point à une équipe
 *      -   dec;team : Retire un point à une équipe
 */
class udp_server_InputDevice : public InputDevice{
    private:
        uint16_t    udpPort{};  /** Server's UDP port  */
        std::jthread    udpServerThread;    /** jthread object, server core */
        
        /**
         * @brief "Real" thrad server function
         */
        void    _serverThread();    
        
        /**
         * @brief   UdpPort getter
         * @return  uint16_t : Udp Port used by the server
         */
        [[nodiscard]] uint16_t    getUdpPort()noexcept{return this->udpPort;};

        void    DecodeTrame(const std::string &frame);     
    public:
        /**
         * @brief default Ctor - DELETED
         */
        udp_server_InputDevice() = delete;

        /**
         * @brief Dtor - defaulted
         */
        virtual ~udp_server_InputDevice() = default;

        /**
         * @brief Standard Ctor
         * @param ScoreManager &manager : reference to the ScoreManager to use
         * @param uint16_t udpPort : server's UDP port, defaultUdpPort by default 
         */
        udp_server_InputDevice(ScoreManager &manager, uint16_t udpPort = defaultUdpPortIn)noexcept:InputDevice{manager},udpPort{udpPort}{};

        /**
         * @brief Real Start function
         */
        virtual     void    Start() override;
};
//----------------------------------------------------------------------------






#endif  /*  __INPUT_DEVICE_HPP__    */