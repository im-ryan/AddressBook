/**
* Ryan Huett
* Date: 11/15/2018
* Visual Studio 2017
* Class AddressBook that handles address book contacts as a hashed linked list.
*/
#pragma once
#include<iostream>
#include<cstdlib>
using namespace std;

class AddressBook {
	static const int MAX_ADDRESSES = 20;
	static const int MAX_HASHES = 8;
	static const int MAX_STRING_SIZE = 21;
	static const int STATE_STRING_SIZE = 3;

	struct contactNode
	{
		char FName[MAX_STRING_SIZE];
		char LName[MAX_STRING_SIZE];
		char Address[MAX_STRING_SIZE];
		char City[MAX_STRING_SIZE];
		char State[STATE_STRING_SIZE];

		contactNode *next;
	};
	contactNode *hashedAddresses[MAX_HASHES];

	int numberOfNodes;

	int createHash(char *key);
	bool keyExists(int hash);

	// Helper functions
	void displayAddress(contactNode address, int listPos);
	void getUserSelection(int *inputVar);
	void getUserSelection(char *inputArr, int maxSize);
	void displayErrorScreen();

public:
	AddressBook();

	void displayMenu();
	void addContact();
	void displayAddressBook();

	int getNumberOfNodes() { return numberOfNodes; }
};