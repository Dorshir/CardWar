#ifndef CARDWAR_B_MAIN_CARD_HPP
#define CARDWAR_B_MAIN_CARD_HPP

#include <utility>
#include <string>
#include <ostream>

namespace ariel {}

class Card {

private:

    std::string rank_;
    std::string type_;

public:

    Card(std::string name, std::string size) : type_(std::move(name)), rank_(std::move(size)) {}

    // Destructor
    ~Card();

    // Copy constructor
    Card(const Card &other) : rank_(other.rank_), type_(other.type_) {}

    // Copy assignment operator overload
    Card &operator=(const Card &other);

    // Move assignment
    Card& operator=(Card&& other) noexcept;

    Card(Card&& other) noexcept : rank_(std::move(other.rank_)), type_(std::move(other.type_)) {
        other.type_ = "INVALID";
        other.rank_ = "INVALID";
    }

    // Relational operator overload
    bool operator<(const Card &other) const;

    // Custom swap function for Card objects
    friend void swap(Card &first, Card &second) noexcept;

    [[nodiscard]] const std::string &getRank() const {
        return rank_;
    }

    [[nodiscard]] const std::string &getType() const {
        return type_;
    }

    [[nodiscard]] std::string toString() const {
        return (getRank() + " of " + getType());
    }

};

#endif
