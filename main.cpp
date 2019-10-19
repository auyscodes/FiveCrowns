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
CardCollection genCol(){
	

    Deck deck1 = Deck::Builder().numericFace(3, 5).suits(
            {"C"}).joker(3).build();
    deck1.shuffle();
    cout << deck1.toString() << endl;
    return deck1;

    CardCollection cardCollection;

    vector<CardInterface*> cardCol;
    for (int i=0;i<3;i++){
        CardInterface* card = new Card();
        card->setSuit(to_string(i+3));
        card->setFace("H");
        cardCol.push_back(card);
    }
    CardInterface* card1 = new Card();
    card1->setFace("J");
    card1->setSuit("H");

    CardInterface* card2 = new Card();
    card1->setFace("Q");
    card1->setSuit("H");

    Card* card3;
    card1->setFace("K");
    card1->setSuit("H");

    cardCollection.addBack(cardCol[0]);
    cardCollection.addBack(card1);

    cardCollection.addBack(cardCol[1]);
    cardCollection.addBack(card2);

    cardCollection.addBack(cardCol[2]);
    cardCollection.addBack(card3);
}

int main() {
    /*testCheckRunFunction();
    testCheckBookFunction();*/

	

    vector<vector<CardInterface*>> output = genCol().getBestPossibleBooksAndRuns();
    cout << "\n----------------------------------------main----\n";
    for (auto elem:output){
        for (auto e: elem)  {
            cout << e->toString() << " ";
        }
        cout << endl;
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