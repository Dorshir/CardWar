#include "card.hpp"

bool Card::operator<(const Card &other) const {
    int myRank = 0;
    if (rank_ == "Jack") myRank = 11;
    else if (rank_ == "Queen") myRank = 12;
    else if (rank_ == "King") myRank = 13;
    else {
        myRank = std::stoi(rank_);
    }

    int otherRank;
    if (other.getRank() == "Jack")otherRank = 11;
    else if (other.getRank() == "Queen") otherRank = 12;
    else if (other.getRank() == "King") otherRank = 13;
    else {
        otherRank = std::stoi(other.getRank());
    }
    if (myRank == 1) {
        if (otherRank == 2) return true;
        else return false;
    } else if (otherRank == 1) return true;
    if (myRank < otherRank) return true;
    else return false;
}

Card &Card::operator=(const Card &other) {
    if (this != &other) {
        this->rank_ = other.rank_;
        this->type_ = other.type_;
    }
    return *this;
}

void swap(Card &a, Card &b) noexcept {
    std::swap(a.rank_, b.rank_);
    std::swap(a.type_, b.type_);
}


