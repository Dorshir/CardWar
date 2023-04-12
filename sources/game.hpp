#ifndef CARDWAR_B_MAIN_GAME_HPP
#define CARDWAR_B_MAIN_GAME_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "card.hpp"
#include "player.hpp"

class Game {

private:

    std::vector<Card> deck;
    std::vector<std::string> log;
    std::string winner;
    Player &player1;
    Player &player2;
    std::string lastTurnString;
    bool player1Won;
    bool player2Won;
    bool GAMEON;
    int drawsCounter;

public:

    Game(Player &player1, Player &player2) : player1(player1), player2(player2), player1Won(false), player2Won(false),
                                             winner("No winner yet"), GAMEON(false), drawsCounter(0) {
        CreateGame();
    }

    void setLastTurnString(const std::string &lastTurnString);

    void playTurn();

    void printLastTurn() const;

    void playAll();

    void printWiner();

    void printLog();

    void printStats();

    void CreateGame();

    void ShuffleDeck();

    void DealingCards();

    void InitNewCardsDeck();

    std::string getWinner();

    void setWinner(const std::string &winner);

    std::vector<std::string> &getLog();

    [[nodiscard]] const std::string &getLastTurnString() const;

    void printPlayerStats(Player &player);

    void setDraws(int count);

    int getDraws() const;
};


#endif
