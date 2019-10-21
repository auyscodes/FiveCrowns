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
    cout << "----------------------------------------------------------------------------------" << endl;
    // UI::showRoundState(this);

    // while all the players have not gone out
        // play
        // if a player has gone out count the players score
        // better set the players score
        int nextPlayerIndex = 0;
        int totalNumberOfPlayers = dataLayer->getPlayers()->size();
        cout << "totalNumberOfPlayers : " << totalNumberOfPlayers << endl;
        cout << "playersGoneOut : "  << playersGoneOut << endl;

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n";
        while(playersGoneOut < totalNumberOfPlayers){
            auto nextPlayer = (*dataLayer->getPlayers())[nextPlayerIndex];
            cout << "Next Player : " << nextPlayer->getName() << endl;


			// !!! Note: it is important to keep the order of this if else statement
			// Since, if next player in the statement goes out then playersGoneOut will be automatically incremented
			if (this->playersGoneOut > 0) {
				nextPlayer->play();
				// nextPlayer->addToScore(countScore(nextPlayer->getHand()));
				vector<vector<CardInterface*>> cardsArgnmnt;

				// conflict when player already goes out
				int score;
				forceGoOut(nextPlayer->getHand(), score, cardsArgnmnt);
				nextPlayer->addToScore(score);
				playersGoneOut++;
			}
			else {
				nextPlayer->play();
			}
			nextPlayerIndex = (++nextPlayerIndex) % (*dataLayer->getPlayers()).size();
            
        }


    cout << "--------------------------------------------------------------------------------" << endl;


	
    // collects cards at the end of every round and puts it in the card collection
    collectCardsFromPiles();

}

void Round::collectCardsFromPiles(){

    DrawPile* drawPile = DrawPile::getInstance();
    DiscardPile* discardPile = DiscardPile::getInstance();
    CardPile* cardCollection = CardPile::getInstance();


    cardCollection->collect(drawPile);
    cardCollection->collect(discardPile);


    for (auto player:*dataLayer->getPlayers()){
        cardCollection->collect(player->getHand());
    }
	cardCollection->undoCardsTmation(to_string(numCardsToDeal), "X");
    cardCollection->shuffle();

}

//map<string, Player*> & Round::getPlayers() {
//    return this->players;
//}




vector<Player *> *Round::getPlayers() {
    return this->dataLayer->getPlayers();
}

Round::Round(int round, DataLayer *dataLayer) {
    this->numCardsToDeal = round + 2;
    this->dataLayer = dataLayer;
}

// checks if go out success. if success increases players gone out count, notifies other players and returns true
// otherwise returns false
bool Round::tryGoOut(Hand* hand, int& score, vector<vector<CardInterface*>>& cardsArrgnmnt) {
	Hand new_hand = *hand; // so that hand is copied and not modified
		if (checkGoOutPossible(&new_hand, score, cardsArrgnmnt)) {
			/*cout << "Inside rounds try go out " << endl;

			cout << "score : " << score << endl;
			
			cout << "Cards Arrangement : ";
			tempPrinter(cardsArrgnmnt);*/

			this->playersGoneOut++;
			notifyOtherPlayers(this->dataLayer->getPlayers());
			return true;
		}
		return false;
	
}




void Round::tempPrinter(vector < vector<CardInterface*>> & cardsArrgnment) {
	cout << " [ ";
	for (auto elem : cardsArrgnment) {
		cout << " [ ";
		for (auto e : elem) {
			cout << e->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}

// right now notifies all the players even the  one that just go out
void Round::notifyOtherPlayers(vector<Player*>* players) {
	vector<Player*>& playersRef = *players;
	for (int i = 0; i < players->size(); i++) {
		Player* player = playersRef[i];
		player->playerGoOut(true);
	}
}

void Round::setGoOutListener() {
    for (auto player: *dataLayer->getPlayers()){
        player->setGoOutListener(this);
    }
}



void Round::forceGoOut(CardCollection* hand, int&score, vector<vector<CardInterface*>>& branch)
{
	CardCollection new_hand = *hand; // so that hand is copied and not modified 

	new_hand.minScoreAndBranch(score, branch);
	this->playersGoneOut++;
	notifyOtherPlayers(this->dataLayer->getPlayers());

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
    if (numCardsToDeal <= 10) return to_string(numCardsToDeal);
    if (numCardsToDeal == 11) return "J";
    if (numCardsToDeal == 12) return "Q";
    if (numCardsToDeal == 13) return "K";
}


bool Round::checkGoOutPossible(CardCollection *hand, int& score, vector<vector<CardInterface*>>&minBranch) {
	
	
	if (hand->isGoingOutPossible(score, minBranch)) {
		return true; 
	}
    return false;
}


void Round::startGame() {
	if (numCardsToDeal == 10) {
		cout << " Debug from here " << endl;
	}
	cout << "-----------------------" << "Round " << this->numCardsToDeal - 2 << "-----------------------------" << endl;
	deal();

	
	cout << "DrawPile: " << DrawPile::getInstance()->toString() << endl;
	cout << "DiscardPile: " << DiscardPile::getInstance()->toString() << endl;
	
	for (auto player : *dataLayer->getPlayers()) {
		cout << "name : " << player->getName() << endl;
		cout << "\t\thand : " << player->getHand()->toString() << endl;
	}
	
	

	
	int nextPlayerIndex = 0;
	int totalNumberOfPlayers = dataLayer->getPlayers()->size();
	cout << "totalNumberOfPlayers : " << totalNumberOfPlayers << endl;
	cout << "playersGoneOut : " << playersGoneOut << endl;

	cout << "----------------------------------------------------------------------------------" << endl;

	while (playersGoneOut < totalNumberOfPlayers) {
		auto nextPlayer = (*dataLayer->getPlayers())[nextPlayerIndex];
		cout << "Next Player : " << nextPlayer->getName() << endl;

		bool goOutFlag = nextPlayer->playGame();

		if (this->playersGoneOut > 0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			forceGoOut(nextPlayer->getPlayerHand(), score, arrgnmnt);
			cout << "Player gone out " << endl;
			cout << "Arragement of cards while going out : ";
			this->tempPrinter(arrgnmnt);
			cout << "Score Player received : " << score << endl;
			
		}

		if (goOutFlag && playersGoneOut==0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			bool successful = tryGoOut(nextPlayer->getPlayerHand(), score, arrgnmnt);
			if (successful) {
				cout << "Player successfully gone out " << endl;
				cout << "Arragement of cards while going out : ";
				this->tempPrinter(arrgnmnt);
				cout << "Score Player received : " << score << endl;
			}
			else {
				cout << "!!! Going out was not possible " << endl;
			}
		}

		nextPlayerIndex = (++nextPlayerIndex) % (*dataLayer->getPlayers()).size();

	}


	cout << "--------------------------------------------------------------------------------" << endl;



	// collects cards at the end of every round and puts it in the card collection
	collectCardsFromPiles();

}

Round::~Round()
{
	// might not be needed
}

