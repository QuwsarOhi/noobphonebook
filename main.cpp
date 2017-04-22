#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <stdlib.h>
#include "contact.h"		//self-made library
#include "trie.h"			//self-made library

using namespace std;

Contact contacts;			//contact list saver object
Trie* trie = new Trie();	//contact search trie object	

void importContact();	//imports contact(s) from file
void exportContact();	//export contact(s) to file
int mainMenu();			//contains main menu options
void runner();			//main display function
void clearscrn();		//clears screen
void setupTrie();		//trie building from contact list
void searchContact();	//contact search function

int main()
{	
	importContact();	//import contacts from file
	setupTrie();		//builds up trie in memory
	runner();			//main run funtion that shows options and menus
	exportContact();	//saves all contact number to file
	delete trie;		//release trie pointer memory
	return 0;
}



void importContact()							//imports contacts from file
{
	fstream file;
	file.open("contacts.txt", ios::in);
	
	if(!file.is_open())
		return;
		
	string name, number;
	
	while(!file.eof()) {
		file >> name >> number;
		contacts.saveContact(name, number);		//contacts are saved in contacts object
	}

	file.close();
}

void exportContact()						//export contacts in file
{
	fstream file;
	file.open("contacts.txt", ios::out);
	
	if(!file.is_open())
		return;
	
	contacts.setIterator();
	
	while(!contacts.isEndContact()) {
		file << contacts.nameThrower() << " " << contacts.numberThrower() << endl;		//name number
		contacts.nextIterator();
	}
	
	file.close();
}

int mainMenu()									//main menu options printer function
{
	cout << "+*+*Main Menu*+*+" << endl;
	cout << endl;
	cout << "Enter choice : " << endl;
	cout << "1. Add Contact" << endl;			//done
	cout << "2. Show All Contacts" << endl;		//done
	cout << "3. Search Contact" << endl;		//done
	cout << "4. Delete Contact" << endl;		//done
	cout << "5. Reset Contact Database" << endl;
	cout << "6. Exit" << endl;					//done
	int input;
	cin >> input;
	return input;
}


void showAllContact()
{
	cin.ignore();
	cout << "+-----------+-------------+" << endl;
	cout << "|" << setw(11) << "Name" << "|"  << setw(13) << "Number" << "|" <<  endl;
	cout << "+-----------+-------------+" << endl;
	contacts.setIterator();
	while(!contacts.isEndContact()) {
		cout << "|" <<setw(11) << contacts.nameThrower() << "|" << setw(13) << contacts.numberThrower() << "|" << endl;
		cout << "+-----------+-------------+" << endl;
		contacts.nextIterator();
	}
	cin.get();
}

void newContact()
{
	string name, number, ans;
	
	cout << "Enter Name : ";
	cin >> name;
	cout << "Enter Number : ";
	cin >> number;
	if(!contacts.isNewContact(name, number)) {
		if(contacts.isDuplicateName(name, number)) {
			cout << "Same name already exists in saved contacts!" << endl;
			cout << "Do you want to overwrite it ? (Y/N)" << endl;
			cin >> ans;
			if(ans == "Y") {
				contacts.saveContact(name, number);
				trie->addWord(name);
				cout << "Saved Successfuly!" << endl;
			}
		}
		else {
			cout << "Same number with different name (" << contacts.getName(number) << ") exists" << endl;
			cout << "Do you wan to delete the previous one and save the new one? (Y/N)" << endl;
			cin >> ans;
			if(ans == "Y") {
				contacts.deleteByNumber(number);
				contacts.saveContact(name, number);
				trie->addWord(name);
				cout << "Saved Successfuly!" << endl;
			}
		}
	}
	else {
		contacts.saveContact(name, number);
		cout << "Saved Successfuly!" << endl;
	}
}

void deleteContact()				//deletes contact from contact object
{
	string name, number;
	int ans;
	cout << "1. Delete by contact name" << endl;
	cout << "2. Delete by contact number" << endl;
	cin >> ans;
	
	if(ans == 1) {
		cout << "Enter contact name to delete : ";
		cin >> name;
		contacts.deleteByName(name);		//remove from contact object
		trie->deleteWord(name);				//remove from trie
	}
	else if(ans == 2) {
		cout << "Enter contact number to delete : ";
		cin >> name;
		contacts.deleteByNumber(number);			//remove from contact object
		trie->deleteWord(contacts.getName(number));	//remove from trie
	}
	else
		return;
}

void runner()			//main menue functionality
{
	clearscrn();
	cout << "				+-------------------+" << endl;
	cout << "				|     PhoneBook     |" << endl;
	cout << "				+-------------------+" << endl;
	cout << "\n\n";
	cout << "\n";
	int input = mainMenu();
	cout << "\n";
	
	if(input == 1) {
		//system("CLS");
		clearscrn();
		newContact();
		cin.ignore();
		runner();
	}
	else if(input == 2) {
		//system("CLS");
		clearscrn();
		showAllContact();
		cin.ignore();
		runner();
	}
	else if(input == 3){
		searchContact();
		cin.ignore();
		runner();
	}
	else if(input == 4) {
		//system("CLS");
		clearscrn();
		deleteContact();
		cin.ignore();
		runner();
	}
	else
		return;
}

void clearscrn()			//clears screen
{
	#ifdef OS_WINDOWS		//checking if it is windows machine
		system("CLS");
	#else 					//assuming it is a linux machine
		system("clear");
	#endif
}

void setupTrie() {				//sets up trie from contact list
	contacts.setIterator();
	while(!contacts.isEndContact()) {
		trie->addWord(contacts.nameThrower());		//adding words to trie
		contacts.nextIterator();
	}
}


void searchContact() {			//search function
	clearscrn();
	string name;
	cout << "\nEnter name to search : [Enter '0' to exit]" << endl;
	cin >> name;
	
	if(name.length() == 1 && name[0] == '0')
		return;
	
	if(!contacts.findContact(name))
		cout << "No direct match found!" << endl;
	else
		cout << "Direct match : \n\t" << name << " : " << contacts.getNumber(name) << endl;
	
	cout << "\n";
	
	queue<string>q = trie->findAll(name);
	string actual_name = name;
	
	if(q.size() == 1 && contacts.findContact(name))
		cout << "No partial match found!\n";
	else{
		cout << "Partial match : \n";
		while(!q.empty()) {
			name = q.front();
			q.pop();
			if(name == actual_name)
				continue;
			cout << "\t" << name << " : " << contacts.getNumber(name) << endl;
		}
	}
	
	cout << "\n\nTo search again press 1" << endl;
	
	cin.ignore();
	char x = cin.get();
	if(x == '1')
		searchContact();
	return;
}
	
