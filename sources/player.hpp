#ifndef CARDWAR_B_MAIN_PLAYER_HPP
#define CARDWAR_B_MAIN_PLAYER_HPP

#include "card.hpp"
#include <utility>
#include <vector>
#include <string>

class Player {

    std::string name_;
    std::vector<Card> deck;
    int winCounter;
    int cardsTaken;

public:

    explicit Player(std::string name) : name_(std::move(name)), winCounter(0), cardsTaken(0) {}

    int stacksize() {
        return (int)deck.size();
    }

    int cardesTaken() const {
        return cardsTaken;
    }

    std::string getName() {
        return name_;
    }

    [[nodiscard]] std::vector<Card> &getDeck() {
        return deck;
    }

    [[nodiscard]] int getWinCounter() const {
        return winCounter;
    }

    void setWinCounter(int wins) {
        Player::winCounter = wins;
    }

    void setDeck(const std::vector<Card> &d) {
        this->deck = d;
    }

    void setCardsTaken(int i) {
        cardsTaken = i;
    }

};

#endif
