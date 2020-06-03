/**
* Ryan Huett
* Date: 11/15/2018
* Visual Studio 2017
* The driver for class AddressBook that includes a simple UI as well as
* input validation. Also contains class AddressBook's member functions.
*/
#include "AddressBook.h"

int main() {
	AddressBook addressBook;
	addressBook.displayMenu();
	return 0;
}

AddressBook::AddressBook() {
	numberOfNodes = 0;

	for (int i = 0; i < MAX_HASHES; i++) {
		hashedAddresses[i] = nullptr;
	}
}

void AddressBook::displayMenu() {
	char input = NULL;
	bool userWantsToGoAgain = true;

	do {
		system("CLS");

		cout << "::Address Book::\n\n"
			<< "[E]nter new contact" << endl;
		cout << "[D]isplay contacts\n"
			<< "[Q]uit the program\n\n"
			<< "Choice: ";

		cin.get(input);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("CLS");
		if (input == 'E' || input == 'e') {
			addContact();
		}
		else if (input == 'D' || input == 'd') {
			cout << "::Your Address Book::\n" << endl;
			displayAddressBook();
		}
		else if (input == 'Q' || input == 'q') {
			userWantsToGoAgain = false;
			cout << "::Exit::\n\nGoodbye!" << endl;
		}
		else {
			displayErrorScreen();
		}
		system("PAUSE");
	} while (userWantsToGoAgain);
}

void AddressBook::addContact() {
	contactNode *newContact = new contactNode, *currNode = new contactNode;
	int hash = 0;

	cout << "::New Contact::\n" << endl;
	if (getNumberOfNodes() < MAX_ADDRESSES) {
		cout << "First Name: ";
		getUserSelection(newContact->FName, MAX_STRING_SIZE);

		cout << " Last Name: ";
		getUserSelection(newContact->LName, MAX_STRING_SIZE);

		cout << "   Address: ";
		getUserSelection(newContact->Address, MAX_STRING_SIZE);

		cout << "      City: ";
		getUserSelection(newContact->City, MAX_STRING_SIZE);

		cout << "     State: ";
		getUserSelection(newContact->State, STATE_STRING_SIZE);

		numberOfNodes++;
		newContact->next = nullptr;
		hash = createHash(newContact->LName);

		if (!keyExists(hash)) {
			hashedAddresses[hash] = newContact;
		}
		else {
			currNode = hashedAddresses[hash];

			// Cannot use NULL here in VB17
			while (currNode->next != nullptr) {
				currNode = currNode->next;
			}
			currNode->next = newContact;
		}

		cout << "\nNew contact, " << newContact->FName
			<< " " << newContact->LName << ", saved!" << endl;
	}
	else {
		cout << "Sorry, but you have stored the max amount of contacts." << endl;
	}
}

void AddressBook::displayAddressBook() {
	contactNode *currNode = nullptr;
	int listPos = 0;

	if (getNumberOfNodes() > 0) {
		for (int i = 0; i < MAX_HASHES; i++) {
			if (keyExists(i)) {
				listPos++;
				displayAddress(*hashedAddresses[i], listPos);

				currNode = hashedAddresses[i];
				while (currNode->next != nullptr) {
					listPos++;
					displayAddress(*currNode, listPos);
					currNode = currNode->next;
				}
				cout << endl;
			}
		}
	}
	else {
		cout << "Your address book is empty, why not add some contacts?" << endl;
	}
}

void AddressBook::displayAddress(contactNode address, int listPos) {
	cout << listPos << ". Name:    " << address.FName << " " << address.LName
		<< "\n   Address: " << address.Address
		<< "\n\t    " << address.City << ", " << address.State << endl << endl;
}

int AddressBook::createHash(char *key) {
	int strlength = strlen(key);
	long hash = 0;

	for (int i = 0; i < strlength; i++) {
		hash = (hash << 2) + key[i];
	}

	return abs(hash % MAX_HASHES);
}

bool AddressBook::keyExists(int hash) {
	// If the hash key is within the valid range and a value is associated with the key, return true
	return ((hash >= 0 && hash < MAX_HASHES) && (hashedAddresses[hash] != nullptr));
}

void AddressBook::getUserSelection(int *userInput) {
	int input = 0;

	cin >> input;
	cin.ignore();

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		displayErrorScreen();
	}
	else {
		*userInput = input;
	}
}

void AddressBook::getUserSelection(char *inputArr, int maxSize) {
	char *input = new char[maxSize];

	cin.getline(input, maxSize);

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "(NOTE: Only the first " << (maxSize - 1)
			<< " letters were saved)" << endl;
	}

	for (int i = 0; i < maxSize; i++) {
		inputArr[i] = input[i];
	}
}

void AddressBook::displayErrorScreen() {
	system("CLS");
	cout << "::Error::\n" << endl
		<< "Unrecognized selection. Please try again.\n" << endl;
}