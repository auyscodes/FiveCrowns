#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "CardCollection.h"
#include "Game.h"

int main() {

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
    Game * game = new Game();
    game->start();
}