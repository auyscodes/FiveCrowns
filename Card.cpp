//
// Created by nbhat on 9/9/2019.
//

#include "Card.h"


Card::Card()
{
}

string Card::toString() {
    return CardInterface::getFace() + CardInterface::getSuit();
}

string Card::getFace() {
    return CardInterface::getFace();
}

string Card::getSuit() {
    return CardInterface::getSuit();
}



void Card::setFace(string face) {
    CardInterface::setFace(face);
}

void Card::setSuit(string suit) {
    CardInterface::setSuit(suit);
}
