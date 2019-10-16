#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "CardCollection.h"
#include "Game.h"
#include "Round.h" // for testCheckRunFunction // remove it later
void testCheckRunFunction(){
    Card* card1 = new Card();
    card1->setSuit("H");
    card1->setFace("J");

    Card* card2 = new Card();
    card2->setSuit("H");
    card2->setFace("Q");

    Card* card3 = new Card();
    card3->setSuit("H");
    card3->setFace("K");

    Hand * hand = new Hand();
    hand->addFront(card1);
    hand->addFront(card2);
    hand->addFront(card3);

    cout << "check run function test : " << Round::checkRun(hand) << endl;
}

void testCheckBookFunction(){
    Card* card1 = new Card();
    card1->setSuit("H");
    card1->setFace("J");

    Card* card2 = new Card();
    card2->setSuit("H");
    card2->setFace("J");

    Card* card3 = new Card();
    card3->setSuit("S");
    card3->setFace("J");

    Hand * hand = new Hand();
    hand->addFront(card1);
    hand->addFront(card2);
    hand->addFront(card3);

    cout << "check book function test : " << Round::checkBook(hand) << endl;
}

int main() {
//    testCheckRunFunction();
//    testCheckBookFunction();

    Deck deck1 = Deck::Builder().numericFace(3, 4).suits(
            {"C"}).joker(1).build();
    deck1.shuffle();
    cout << deck1.toString() << endl;

    vector<CardCollection*> output = deck1.genPermutations();
    for (auto elem:output){
        cout << elem->toString() << endl;
    }





























//    for (auto cardCollection: output){
//        cout << cardCollection->toString() << endl;
//    }


//    Card card;
//    card.setSuit("J");
//    card.setFace("1");
//
//    cout << card.getSuit() << endl;
//    cout << card.getSuit() << endl;
//    cout << card.toString();
//
//    CardCollection cardCollection;
//    cardCollection.addFront(&card);


//    Game* game = new Game();
//    game->start();

//    Deck deck =  Deck::Builder().numericFace(3, 10).specialFace({"J", "Q", "K"}).suits({"D", "C", "S", "H", "T"}).joker(3).build();
//    int i = 0;
//    while(!deck.isEmpty()){
//        cout << "i: " << i << "\t" << deck.popFront()->toString()<< endl;
//        i++;
//    }
//    Game * game = new Game();
//    game->start();
}