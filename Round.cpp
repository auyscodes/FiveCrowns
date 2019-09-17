//
// Created by nbhat on 9/15/2019.
//

#include "Round.h"



void Round::deal() {
    /*Code belongs to function before deal*/

    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();




    // If it is a first round then builds a deck and adds to a cardcollection
    // else collects all the cards from discard pile, drawpile and player's hands
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

        // plus needs to determine the first player

    }
    else{

        cardCollection->collect(drawPile);
        cardCollection->collect(discardPile);
//        for (Player* player: players){
//            cardCollection->collect(player->getHand());
//        }
        map<string, Player*>::iterator it;
        for (it = players.begin(); it!=players.end(); it++){
            cardCollection->collect(it->second->getHand());
        }
        cardCollection->shuffle();
    }

    /*Code belongs to function before deal*/

    for (int i=0;i<numCardsToDeal;i++){
//        for (auto player: players){
//
//
//             player->setCard(cardCollection->popFront());
//        }
        map<string, Player*>::iterator it;
        for (it=players.begin();it!=players.end();it++){
            it->second->setCard(cardCollection->popFront());
        }
    }

    drawPile->collect(cardCollection);
    discardPile->addFront(drawPile->popFront());


}

void Round::start() {
    deal();

    UI::showRoundState(this);
//    UI::showMenu();

}

//vector<Player *>& Round::getPlayers() {
//    return this->players;
//}
map<string, Player*> & Round::getPlayers() {
    return this->players;
}

Round::Round(int round, map<string, Player *> &players) {
    this->numCardsToDeal = round + 2;
    this->players = players;

}



//        for (int i=0;i<deck.getSize();i++){
//            cout << "i : " << i << "\t" << deck.getCardAt(i)->toString() << endl;
//        }