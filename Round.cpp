//
// Created by nbhat on 9/15/2019.
//

#include "Round.h"
#include "DataLayer.h"


void Round::deal() {


    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();



    // if discardPile isEmpty then it is a new game
    if (discardPile->isEmpty()){
        // If it is a first round then builds a deck and adds to a cardcollection.
        if (numCardsToDeal - 2 == startRound) {
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
        // here cardCollection is always full whether it is a first round or not
        cardCollection->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal), "X");
        for (int i=0;i<numCardsToDeal;i++){

//            map<string, Player*>::iterator it;
//            for (it=players.begin();it!=players.end();it++){
//                it->second->setCard(cardCollection->popFront());
//            }
            for (auto player: *dataLayer->getPlayers()){
                player->setCard(cardCollection->popFront());
            }
        }

        drawPile->collect(cardCollection);
        discardPile->addFront(drawPile->popFront());


    }
    // don't need to setup anything in game resume. Everything is already setup.


}

void Round::start() {
    deal();

    setGoOutListener();
    cout << "DrawPile: " << DrawPile::getInstance()->toString() << endl;
    cout << "DiscardPile: " << DiscardPile::getInstance()->toString() << endl;
    // cout << "CardPile: " << CardPile::getInstance()->toString() << endl;
    for (auto player: *dataLayer->getPlayers()){
        cout  << "name : " << player->getName() << endl;
        cout << "\t\thand : " << player->getHand()->toString()<< endl;
    }
    // UI::showRoundState(this);

    // while all the players have not gone out
        // play
        // if a player has gone out count the players score
        // better set the players score


    for (auto player: *dataLayer->getPlayers()){
        cout << "Next Player: " << player->getName() << endl;
        player->play();
        if (this->onePlayerHasGoneOut) player->addToScore(countScore(player->getHand()));
        // count player score
    }


    // collects cards at the end of every round and puts it in the card collection
    collectCardsFromPiles();

}

void Round::collectCardsFromPiles(){

    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();


    cardCollection->collect(drawPile);
    cardCollection->collect(discardPile);

//    map<string, Player*>::iterator it;
//    for (it = players.begin(); it!=players.end(); it++){
//        cardCollection->collect(it->second->getHand());
//    }
    for (auto player:*dataLayer->getPlayers()){
        cardCollection->collect(player->getHand());
    }
    cardCollection->shuffle();
}

//map<string, Player*> & Round::getPlayers() {
//    return this->players;
//}


//Round::Round(int round, map<string, Player *> &players) {
//    this->numCardsToDeal = round + 2;
//    this->players = players;
//
//}



//Round::Round(int round, vector<Player*>& players){
//    this->numCardsToDeal = round + 2;
//    this->players = players;
//}

vector<Player *> *Round::getPlayers() {
    return this->dataLayer->getPlayers();
}

Round::Round(int round, DataLayer *dataLayer) {
    this->numCardsToDeal = round + 2;
    this->dataLayer = dataLayer;
}

void Round::goOut(Hand* hand) {
    if (checkGoOutPossible(hand)) this->onePlayerHasGoneOut = true;
    else cout << "Going out not possible" << endl;
}

void Round::setGoOutListener() {
    for (auto player: *dataLayer->getPlayers()){
        player->setGoOutListener(this);
    }
}


// not complete
// wrong now if used
int Round::countScore(CardCollection *hand) {
    int size = hand->getSize();
    for (int i=0;i<size;i++){
        hand->getCardAt(i);
    }

    // need to edit
    return int(1);
}

int Round::getScore(Card* card){
    if (card->getSuit()=="J") return 50;
    if (card->getFace() == "X") return 20;

    if (card->getFace() == "3") return 3;
    if (card->getFace() == "4") return 4;
    if (card->getFace() == "5") return 5;
    if (card->getFace() == "6") return 6;
    if (card->getFace() == "7") return 7;
    if (card->getFace() == "8") return 8;
    if (card->getFace() == "9") return 9;
    if (card->getFace() == "10") return 10;
    if (card->getFace() == "J") return 11;
    if (card->getFace() == "Q") return 12;
    if (card->getFace() == "K") return 13;

}

string Round::convertNumCardsToDealToWildCards(int numCardsToDeal) {
    if (numCardsToDeal < 10) return to_string(numCardsToDeal);
    if (numCardsToDeal == 11) return "J";
    if (numCardsToDeal == 12) return "Q";
    if (numCardsToDeal == 13) return "K";
}

bool Round::checkGoOutPossible(CardCollection *hand) {
    // one way

    // sort card in hand
    // separate joker and wildcard from cards
    // list of possible combos
    // pass into a recursive function
    // done
    // can check if go out is possible
    bool chRun = checkRun(hand);
    bool chBook = checkBook(hand);
    cout << "checkRun : " << chRun << endl;
    cout << "checkBook : " << chBook << endl;

    return false;
}



