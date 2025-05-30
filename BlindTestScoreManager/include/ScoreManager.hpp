
#ifndef __SCORE_MANAGER_HPP__
#define __SCORE_MANAGER_HPP__

#include <iostream>
#include <unordered_map>
#include <string>
#include <print>


#include "Team.hpp"
#include "outputDevice.hpp"

class OutputDevice;

class   ScoreManager{
    private:
        std::unordered_map<std::string,Team> TeamMap{}; /** Main Teams container */

        OutputDevice    &Screen;                /** Generic ref to the output device */

    public:

        /**
         * @brief Default Ctor - DELETED
         */
        ScoreManager() = delete;

        /**
         * @brief Dtor - Defaulted
         */
        virtual ~ScoreManager() = default;


        /**
         * @brief Standard Ctor
         * @param utputDevice& od : Reference to the output device 
         */
        ScoreManager(OutputDevice &od)noexcept:Screen{od}{};


        /**
         * @brief   Returns the number of registered teams 
         * @return  number of registeredteams 
         */
        [[nodiscard]]auto    getNbTeams()noexcept{return this->TeamMap.size();};

        /**
         * @brief Adds a team to the container
         * @param std::string TeamName : Team's name 
         */
        void    addTeam(const std::string &TeamName)noexcept{this->TeamMap.insert({TeamName, Team{TeamName}});this->updateScreen();};
        
        
        /**
         * @brief Removes a Team from the container
         * @param std::string TeamName : Team's name
         */
        void    removeTeam(const std::string &TeamName)noexcept{this->TeamMap.erase(TeamName);this->updateScreen();};


        /**
         * @brief   Returns the Team's actual number of points.
         * @param   std::string TeamName : Team's name 
         * @return  uint16_t : Number of points
         * @throws std::out_of_range if the container does not have an element with the specified key.
         */
        [[nodiscard]]   uint16_t    getTeamScore(const std::string &TeamName){return this->TeamMap.at(TeamName).getLocalScoreRef().getPoints();};

        /**
         * @brief Increments the Team's number of points by a certain value (1 by default)
         * @param std::string TeamName : Team's name
         * @param Nb : Increment value (1 by default)
         * @throws std::out_of_range if the container does not have an element with the specified key. 
         */
        void        incTeamScore(const std::string &TeamName, uint16_t Nb = 1){this->TeamMap.at(TeamName).getLocalScoreRef().inc(Nb);this->updateScreen();};    
        
         /**
         * @brief Decrements the Team's number of points by a certain value (1 by default)
         * @param std::string TeamName : Team's name
         * @param Nb : Decrement value (1 by default)
         * @throws std::out_of_range if the container does not have an element with the specified key. 
         */
        void        decTeamScore(const std::string &TeamName, uint16_t Nb = 1){this->TeamMap.at(TeamName).getLocalScoreRef().dec(Nb);this->updateScreen();};   

        /**
         * @brief   Calls the update (virtual) function of the output device
         */
        void updateScreen() noexcept;

        //void        updateScreen()noexcept{this->Screen.update(this->TeamMap);};

        /**
         * @brief   Prints the list of teamnames to std::clog
         */
        void        listTeamNames()noexcept;
        std::string getTeamNames() noexcept;

};



#endif  /*  __SCORE_MANAGER_HPP__   */
