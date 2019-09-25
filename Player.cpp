//
// Created by nbhat on 9/15/2019.
//

#include "Player.h"
#include "DrawPile.h"
#include "DiscardPile.h"

Player::Player() {
    hand = new Hand();
}


void Player::setCard(CardInterface *card) {

    hand->addFront(card);
}

CardCollection *Player::getHand() {
    return hand;
}

void Player::setName(string* name) {
    this->name = name;
}

string Player::getName() {
    return *this->name;
}

void Player::setGoOutListener(IGoOut *iGoOut) {
    this->iGoOut = iGoOut;
}

void Player::addToScore(int score) {
    this->score += score;
}



