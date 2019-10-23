//
// Created by nbhat on 9/15/2019.
//

#include "Human.h"
#include "DiscardPile.h"
#include "DrawPile.h"
#include "Computer.h"
#include "Round.h"

bool Human::playGame() {
	
	cout << " I am " << *(this->name) << endl;
	showDrawAndDiscardPile();
	showHand();
	while (true) {
		cout << "1. Save the game" << endl;
		cout << "2. Make a move" << endl;
		cout << "3. Ask for help (go out/ keep discard pile card/ draw new) ?" << endl; // discard
		cout << "4. Quit the game" << endl;

		cout << "Enter option : ";
		int option;
		cin >> option;

		while (!cin || option < 1 || option>4) {
			cout << "Please enter valid integer option: ";
			cin.clear();
			cin.ignore();
			cin >> option;

		}
		

		switch (option) {
		case 1: {
			cin.clear();
			cin.ignore();
			string filename;
			do {
				cout << "Enter filename : ";
				getline(cin, filename);
			} while (filename.empty());
			
			iSave->saveGame(filename);
			exit(EXIT_SUCCESS);
		}
			  break;
		case 2: {
			bool flag = moveHelper(); // flag true means user wants to go out
			if (flag) return true;
			return false;
		}
			  break;
		case 3: {
			cout << "Asking for help" << endl;
			Computer::helpPick(*this->hand); // change this hardcoded int
		}
			  break;
		case 4: {
			exit(EXIT_SUCCESS);
		}
			  break;
		default:
			exit(EXIT_FAILURE); // might need to change this later

		}
	}
	
}

bool Human::moveHelper() {
	
	showDrawAndDiscardPile();
	showHand();
	CardInterface* pickedCard;
	Hand hand_before_picking = *(this->hand); // copies curr hand

	bool _getCardOrGoOut = getCardOrGoOut(pickedCard);
	if (_getCardOrGoOut) return true;
	
	int option;
	while (true) {
		cout << "1. Throw card" << endl;
		cout << "2. Throw card and Go Out " << endl;
		cout << "3. Ask for help, which card to throw? " << endl;
		do {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Selection options (e.g 1 or 2) : ";
			cin >> option;

		} while ((option <= 0) || (option >= 4));

		switch (option) {
		case 1: {
			throwCardAtIndex();
			return false;
		}	
			break;
		case 2: {
			throwCardAtIndex();
			return true;
		}
			  break;
		case 3: {
			Computer::helpThrow(hand_before_picking, pickedCard); 
		}
			  break;
			   
		default:
			exit(EXIT_FAILURE);
		}
	}
	
}



void Human::throwCardAtIndex() {
	int index = -1;
	do {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "1. Enter the index of card that you want to throw: " << endl;

		cin >> index;
	} while (index<0 && index>=hand->getSize()-1);
	DiscardPile::getInstance()->addFront(hand->popCardAt(index));
}

// returns true if user decides to go out without picking
bool Human::getCardOrGoOut(CardInterface*& pickedCard)
{
	
	 

	int option;
	cout << "1. Get card from DrawPile" << endl;
	cout << "2. Get card from DiscardPile" << endl;
	cout << "3. Go out " << endl;

	do {
		cin.clear();
		cin.ignore(numeric_limits < streamsize>::max(), '\n');
		cout << "Enter option (e.g 1) : ";
		cin >> option;
	} while ((option <= 0) || (option >= 4));
	switch (option) {
	case 1: {
		hand->addFront(DrawPile::getInstance()->popFront());
		pickedCard = hand->getFront();
	}
		  

		  break;
	case 2: {
		hand->addFront(DiscardPile::getInstance()->popFront());
		pickedCard = hand->getFront();
	}
		  
		  break;
	case 3:
		return true;
	default:
		exit(EXIT_FAILURE);
		
	}
	return false;
}

