//
// Created by nbhat on 9/15/2019.
//

#include "Round.h"



void Round::deal() {


    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();


    // if discardPile isEmpty then it is a new game
    if (discardPile->isEmpty()){
        // If it is a first round then builds a deck and adds to a cardcollection.
        if (numCardsToDeal == startRound) {
            Deck deck1 = Deck::Builder().numericFace(3, 10).specialFace({"J", "Q", "K"}).suits(
                    {"C", "H", "D", "S", "T"}).joker(3).build();
            deck1.shuffle();
            Deck deck2 = Deck::Builder().numericFace(3, 10).specialFace({"J", "Q", "K"}).suits(
                    {"C", "H", "D", "S", "T"}).joker(3).build();
            deck2.shuffle();


            cardCollection->collect(&deck1);
            cardCollection->collect(&deck2);
            cardCollection->shuffle();
        }
        for (int i=0;i<numCardsToDeal;i++){

            map<string, Player*>::iterator it;
            for (it=players.begin();it!=players.end();it++){
                it->second->setCard(cardCollection->popFront());
            }
        }

        drawPile->collect(cardCollection);
        discardPile->addFront(drawPile->popFront());
    }
    // don't need to setup anything in game resume. Everything is already setup.


}

void Round::start() {
    deal();

    UI::showRoundState(this);


    // collects cards at the end of every round and puts it in the card collection
    collectCardsFromPiles();
}

void Round::collectCardsFromPiles(){

    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();


    cardCollection->collect(drawPile);
    cardCollection->collect(discardPile);

    map<string, Player*>::iterator it;
    for (it = players.begin(); it!=players.end(); it++){
        cardCollection->collect(it->second->getHand());
    }
    cardCollection->shuffle();
}

map<string, Player*> & Round::getPlayers() {
    return this->players;
}

Round::Round(int round, map<string, Player *> &players) {
    this->numCardsToDeal = round + 2;
    this->players = players;

}



