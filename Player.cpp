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

Hand* Player::getPlayerHand() {
	return hand;
}

void Player::setName(string* name) {
    this->name = name;
}

string Player::getName() {
    return *this->name;
}
//
//void Player::setGoOutListener(IGoOut *iGoOut) {
//    this->iGoOut = iGoOut;
//}

void Player::setSaveGameCallback(Save* iSave)
{
	this->iSave = iSave;
}

void Player::addToScore(int score) {
    this->score += score;
}



void Player::playerGoOut(bool hasToGoOut) {
	this->haveToGoOut = hasToGoOut;
}


void Player::showDrawAndDiscardPile() {
	cout << "showing drawpile : " << endl;
	cout << DrawPile::getInstance()->toString();
	cout << endl;
	cout << "showing discardpile : " << endl;
	cout << DiscardPile::getInstance()->toString();
	cout << endl;
}
void Player::showHand() {
	cout << "showing hand : " << endl;
	cout << hand->toString();
	cout << endl;
}

void Player::printCardsArrgmnt(vector<vector<CardInterface*>> cardsArgmnt)
{
	cout << " [ ";
	for (auto argmnt : cardsArgmnt) {
		cout << " [ ";
		for (auto elem : argmnt) {
			cout << elem->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}

int Player::getScore() {
	return this->score;
}

void Player::setPlayerHand(Hand* hand)
{
	this->hand = hand;
}

void Player::setScore(int score)
{
	this->score = score;
}
