#include "ScoreManager.hpp"

#include <sstream>

void ScoreManager::updateScreen() noexcept {
    std::println("test");
    this->Screen.update(this->TeamMap,this->TeamMap.size());
}

void    ScoreManager::listTeamNames()noexcept{
    for(auto team : this->TeamMap){
        std::println(std::clog,"{}",team.second.getName());
    }
}

std::string ScoreManager::getTeamNames() noexcept {
    std::ostringstream output;
    for (auto team : this->TeamMap) {
        output << team.second.getName() << "\n";
    }
    return output.str();
}

