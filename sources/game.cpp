#include "game.hpp"
#include <random>
#include <iostream>

void Game::CreateGame() {

    // Initializing cards deck
    this->InitNewCardsDeck();

    // Shuffle the deck
    this->ShuffleDeck();

    // Dealing the cards to the players
    this->DealingCards();
}

void ::Game::InitNewCardsDeck() {

    std::string types[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    std::string ranks[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};

    for (const auto &type: types) {
        for (const auto &rank: ranks) {
            Card card(type, rank); // create a new Card object
            deck.push_back(card);  // add the new Card to the vector
        }
    }
}

void ::Game::ShuffleDeck() {

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

void ::Game::DealingCards() {

    std::vector<Card> deck1(deck.begin(), deck.begin() + (long long) deck.size() / 2);
    std::vector<Card> deck2(deck.begin() + (long long) deck.size() / 2, deck.end());
    this->player1.setDeck(deck1);
    this->player2.setDeck(deck2);
}

void Game::printLastTurn() const {

    if (!GAMEON) throw std::invalid_argument("Game is not started yet.\n");
    std::cout << getLastTurnString() + "\n";
}

void Game::printLog() {

    while (!getLog().empty()) {
        std::string lastTurn = getLog().front();
        getLog().erase(getLog().begin());
        std::cout << lastTurn << std::endl;
    }
}

void Game::playTurn() {


    if (&player1 == &player2) throw std::invalid_argument("Cannot play with the same player!");
    if (!GAMEON) GAMEON = true;
    if (player1.stacksize() == 0) throw std::invalid_argument("Players has no turns to play!");

    int cardCount = 0;
    setLastTurnString("");
    player1Won = false;
    player2Won = false;
    while (!player1Won && !player2Won) {

        if (player2.getDeck().front() < player1.getDeck().front()) { // Player1 wins
            cardCount += 2;
            std::string appending =
                    player1.getName() + " played " + player1.getDeck().front().toString() + " " + player2.getName() +
                    " played " + player2.getDeck().front().toString() + ". " + player1.getName() + " wins.";
            setLastTurnString(getLastTurnString() + appending);

            player1.setWinCounter(player1.getWinCounter() + 1); // Winner++
            player1.setCardsTaken(player1.cardesTaken() + cardCount); // Update cardsTaken
            player1.getDeck().erase(player1.getDeck().begin()); // Erase 1 card
            player2.getDeck().erase(player2.getDeck().begin()); // Erase 1 card
            player1Won = true;
            cardCount = 0;
        } else if (player1.getDeck().front() < player2.getDeck().front()) { // Player2 wins
            cardCount += 2;
            std::string appending =
                    player1.getName() + " played " + player1.getDeck().front().toString() + " " + player2.getName() +
                    " played " + player2.getDeck().front().toString() + ". " + player2.getName() + " wins.";
            setLastTurnString(getLastTurnString() + appending);

            player2.setWinCounter(player2.getWinCounter() + 1); // Winner++
            player2.setCardsTaken(player2.cardesTaken() + cardCount); // Update cardsTaken
            player1.getDeck().erase(player1.getDeck().begin()); // Erase 1 card
            player2.getDeck().erase(player2.getDeck().begin()); // Erase 1 card
            player2Won = true;
            cardCount = 0;
        } else { // Draw
            setDraws(getDraws() + 1);
            std::string appending =
                    player1.getName() + " played " + player1.getDeck().front().toString() + " " + player2.getName() +
                    " played " + player2.getDeck().front().toString() + ". Draw. ";
            setLastTurnString(getLastTurnString() + appending);
            player1.getDeck().erase(player1.getDeck().begin()); // Erase 1 card
            player1.getDeck().erase(player1.getDeck().begin()); // Erase 1 card

            if(player1.stacksize() == 0) { // Last card through a draw, each player take his own cards
                player2.setCardsTaken(player2.cardesTaken() + 1);
                player1.setCardsTaken(player1.cardesTaken() + 1);
                return;
            }
            player2.getDeck().erase(player2.getDeck().begin()); // Erase 1 card
            player2.getDeck().erase(player2.getDeck().begin()); // Erase 1 card
            cardCount = cardCount + 4; // 4 cards via draw
        }
    }

    if (player1.cardesTaken() == 0) { // Last turn -> set winner/draw
        if (player1.cardesTaken() > player2.cardesTaken()) setWinner(player1.getName());
        else if (player1.cardesTaken() < player2.cardesTaken()) setWinner(player2.getName());
        else {
            setWinner("Constant draw between the players.\n");
        }
    }
    getLog().push_back(getLastTurnString()); // Update log
}

void Game::printStats() {

    std::cout << "---- Game stats: ----" << std::endl;
    printPlayerStats(player1);
    printPlayerStats(player2);

    int draws = getDraws();
    double drawRate = double(draws) / 26.0;
    std::cout << "[**] Draw rate: " << drawRate << std::endl << "[**] Draws amount: " << draws << std::endl;
}

void Game::printPlayerStats(Player &player) {

    double playerWinRate = double(player.getWinCounter()) / 26.0;
    std::cout << "[*] Player name: " << player.getName() << std::endl << std::endl << "[*] Win rate: " << playerWinRate
              << std::endl;

    int cardsWon = player.cardesTaken();
    std::cout << "[*] Cards won: " << cardsWon << std::endl;

    std::cout << "---------------------" << std::endl;
}

void Game::playAll() {

    while (player1.stacksize() > 0) {
        playTurn();
    }
}

void Game::printWiner() {

    if (!GAMEON) throw std::invalid_argument("No winner yet!");
    std::cout << getWinner();
}

std::string Game::getWinner() {
    return this->winner;
}

const std::string &Game::getLastTurnString() const {
    return lastTurnString;
}

void Game::setLastTurnString(const std::string &string) {
    Game::lastTurnString = string;
}

std::vector<std::string> &Game::getLog() {
    return log;
}

void Game::setWinner(const std::string &w) {
    Game::winner = w;
}

void Game::setDraws(int count) {
    drawsCounter = count;
}

int Game::getDraws() const {
    return drawsCounter;

}



