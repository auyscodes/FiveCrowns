//
// Created by nbhat on 9/15/2019.
//

#include "Human.h"
#include "DiscardPile.h"
#include "DrawPile.h"


void Human::play() {
    // Note: This is UI code
    showDrawAndDiscardPile();
    showHand();
    int option;
    cout << "1. Save the game" << endl;
    cout << "2. Make a move" << endl;
    cout << "3. Ask for help" << endl;
    cout << "4. Quit the game" << endl;

    cout << "Enter option : " ;
    cin >> option;

    switch (option){
        case 1:
            cout << "Saving the game" << endl;
            break;
        case 2:
            askToChooseCardFromDrawPileOrDiscardPile();
            break;
        case 3:
            cout << "Asking for help" << endl;
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            exit(EXIT_FAILURE); // might need to change this later

    }

}

void Human::askToChooseCardFromDrawPileOrDiscardPile() {

    int option;
    cout << "1. Get card from DrawPile" << endl;
    cout << "2. Get card from DiscardPile" << endl;
    cin >> option;
    switch (option){
        case 1:
            hand->addFront(DrawPile::getInstance()->popFront());
            break;
        case 2:
            hand->addFront(DiscardPile::getInstance()->popFront());
            break;
        default:
            break; // need to change this later
    }
    cin.ignore();
    showDrawAndDiscardPile();
    showHand();


    bool goOut = false;
    cout << "1. Throw card" << endl;
    cout << "2. Throw card and Go Out " << endl;
    cin >> option;
    if (option == 2) goOut = true;

    bool flag = false;
    while(true){

        string card;
        cout << "1. Enter card that you want to throw: " << endl;
        cin.ignore();
        getline(cin, card);
        cout << card;
        cout << "size of hand : " << hand->getSize();
        for (int i=0;i<hand->getSize();i++){
            if (hand->getCardAt(i)->match(card)){
                DiscardPile::getInstance()->addFront(hand->popCardAt(i));
                flag = true;
                break;
                cout << "true" << endl;
            }
            cout << "false" << endl;
            cout << "i : " << i << endl;
        }
        if (flag) break;
    }
    if (goOut) iGoOut->goOut(this->hand);

}

void Human::showDrawAndDiscardPile() {
    cout << "showing drawpile : " << endl;
    cout << DrawPile::getInstance()->toString();
    cout << endl;
    cout << "showing discardpile : " << endl;
    cout << DiscardPile::getInstance()->toString();
    cout << endl;
}
void Human::showHand(){
    cout << "showing hand : " << endl;
    cout << hand->toString();
    cout << endl;
}
