#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <print>

#include "Score.hpp"
#include "Team.hpp"
#include "ScoreManager.hpp"

const uint16_t testSetValue{42};

TEST_CASE("test Score class"){

    SUBCASE("test CTOR"){
        Score MyScore{};
        CHECK(MyScore.getPoints() == 0);

        Score MyScoreInit{testSetValue};
        CHECK(MyScoreInit.getPoints() == testSetValue);
    }

    Score MyScore{};
    CHECK(MyScore.getPoints() == 0);

    SUBCASE("test set / reset"){
        
        MyScore.set(testSetValue);
        CHECK(MyScore.getPoints() == testSetValue);

        MyScore.reset();
        CHECK(MyScore.getPoints() == 0);

    }

    SUBCASE("test inc"){
        
        REQUIRE(MyScore.getPoints() == 0);

        MyScore.inc();
        CHECK(MyScore.getPoints() == 1);

        MyScore.inc(2);
        CHECK(MyScore.getPoints() == 3);
    }

    SUBCASE("test dec"){
        MyScore.set(testSetValue);
        REQUIRE(MyScore.getPoints() == testSetValue);

        MyScore.dec();
        CHECK(MyScore.getPoints() == (testSetValue-1));

        MyScore.dec(3);
        CHECK(MyScore.getPoints() == (testSetValue-4));

        REQUIRE(testSetValue > MyScore.getPoints());
        MyScore.dec(testSetValue);
        CHECK(MyScore.getPoints() == 0);

    }
}


TEST_CASE("test Team class"){

    SUBCASE("Default Ctor"){
        Team MyTeam{};
        CHECK (MyTeam.getName() == "");
    }

    SUBCASE("Standard Ctor"){
        Team MyTeam{"USAP"};
        CHECK (MyTeam.getName() == "USAP");
    }

    SUBCASE("setName Test"){
        std::string testName{"Stade Toulousain"};

        Team MyTeam{"USAP"};
        REQUIRE(MyTeam.getName() == "USAP");

        MyTeam.setName(testName);
        CHECK (MyTeam.getName() == testName);
    }

    Team MyTeam{"USAP"};

    SUBCASE("tests gestion score"){
        uint16_t NbPoints{};

        NbPoints = MyTeam.getLocalScore().getPoints();
        CHECK(NbPoints == 0);

        MyTeam.getLocalScore().inc();
        NbPoints = MyTeam.getLocalScore().getPoints();
        CHECK(NbPoints == 1);
    }
}

TEST_CASE("test ScoreManager class"){

    ScoreManager    Manager{};
    CHECK(Manager.getNbTeams() == 0);

    Manager.addTeam("USAP");
    CHECK(Manager.getNbTeams() == 1);
    Manager.addTeam("Stade Toulousain");
    CHECK(Manager.getNbTeams() == 2);

    Manager.listTeamNames();

    SUBCASE("test getScore, inc..."){
        uint16_t nbPoints{};
        nbPoints = Manager.getTeamScore("USAP");
        CHECK(nbPoints == 0);
        nbPoints = Manager.getTeamScore("Stade Toulousain");
        CHECK(nbPoints == 0);

        Manager.incTeamScore("USAP");
        nbPoints = Manager.getTeamScore("USAP");
        CHECK(nbPoints == 1);

        Manager.incTeamScore("Stade Toulousain",3);
        nbPoints = Manager.getTeamScore("Stade Toulousain");
        CHECK(nbPoints == 3);
    }

}



