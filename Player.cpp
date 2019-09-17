//
// Created by nbhat on 9/15/2019.
//

#include "Player.h"

Player::Player() {
    hand = new Hand();
}

void Player::play() {

}

void Player::setCard(CardInterface *card) {

    hand->addFront(card);
}

CardCollection *Player::getHand() {
    return hand;
}
