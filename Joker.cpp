//
// Created by nbhat on 9/9/2019.
//

#include "Joker.h"


string Joker::toString() {

    return CardInterface::getSuit()+ CardInterface::getFace();
}

string Joker::getFace() {

    return CardInterface::getFace();
}

string Joker::getSuit() {

    return CardInterface::getSuit();
}



void Joker::setFace(string face) {
    CardInterface::setFace(face);
}

void Joker::setSuit(string suit) {
    CardInterface::setSuit(suit);
}
