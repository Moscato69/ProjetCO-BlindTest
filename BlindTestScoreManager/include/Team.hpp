#ifndef __TEAM_HPP__
#define __TEAM_HPP__

#include <string>

#include "Score.hpp"

class Team{
    private:
        std::string Name{};     /** Team's name     */
        Score   TeamScore{};    /*  Team's scode    */

    public:
        /**
         * @brief Default Ctor - Defaulted
         */
        Team() = default;


        /**
         * @brief Standard Ctor
         * @param std::string Name : Team's name 
         */
        Team(const std::string &Name)noexcept:Name{Name}{};

        /**
         * @brief Dtor - Defaulted
         */
        virtual ~Team() = default;

        /**
         * @brief   Team's name getter
         * @return  std::string : Team's name
         */
        [[nodiscard]]   std::string getName()noexcept{return this->Name;};

        /**
         * @brief Team's name setter
         * @param std::string Name : Team's name 
         */
        void        setName(const std::string &Name){this->Name = Name;};

        /**
         * @brief   Returns a reference to the internal Score object
         * @return  Score&
         */
        [[nodiscard]]   Score&  getLocalScoreRef()noexcept{return this->TeamScore;};


};



#endif  /*  __TEAM_HPP__    */

