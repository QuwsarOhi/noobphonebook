//#include <iostream>
//#include <string>
//#include <map>
#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED

using namespace std;

//Contains All the contacts

class Contact {

private:
    map<string, string>name_to_number;      //name(key), number(value)
    map<string, string>number_to_name;      //number(key), name(value)
    map<string, string> :: iterator it;
    //int size;

public:
	Contact();
    bool isNewContact(string, string);      //checks if the contact is not saved previously
    void saveContact(string, string);       //save the number in contact
    string getNumber(string);               //returns number of a contact name
    string getName(string);                 //returns name of a contact number
    bool isEndContact();					//check if the end iterator is reached
    string nameThrower();					//returns the name
    string numberThrower();					//returns the number
    void setIterator();						//resets the iterator
    void nextIterator();					//increment iterator by one
    int contactSize();						//returns the size
    bool isDuplicateName(string, string);
    bool isDuplicateNumber(string, string);
    void deleteByName(string);
    void deleteByNumber(string);
    bool findContact(string);
};

Contact :: Contact()
{
	name_to_number.clear();
	number_to_name.clear();
	//size = 0;
}

void Contact :: setIterator()
{
	it = name_to_number.begin();
}

void Contact :: nextIterator()
{
	it++;
}

bool Contact :: isNewContact(string name, string number)
{
    if(name_to_number.find(name) == name_to_number.end() && number_to_name.find(number) == number_to_name.end())
		return true;
		
	return false;
}

void Contact :: saveContact(string name, string number)
{
    name_to_number[name] = number;
    number_to_name[number] = name;
}

string Contact :: getNumber(string name)
{
    return name_to_number[name];
}

string Contact :: getName(string number)
{
    return number_to_name[number];
}

bool Contact :: isEndContact()
{
	if(it == name_to_number.end())
		return true;

	return false;
}

string Contact :: nameThrower()
{
	return it->first;
}

string Contact :: numberThrower()
{
	return it->second;
}
		
int Contact :: contactSize()
{
	int Size = name_to_number.size();
	//cout << "name to number " <<  name_to_number.size() << endl;
	//cout << "number to name " << number_to_name.size() << endl;
	return Size;
}

bool Contact :: isDuplicateName(string name, string number)
{
	if(name_to_number[name] != number)
		return true;
	return false;
}

bool Contact :: isDuplicateNumber(string name, string number)
{
	if(number_to_name[number] != name)
		return true;
	return false;
}

void Contact :: deleteByNumber(string number)
{
	if(isNewContact("", number))
		return;

	map<string, string> :: iterator it;
	it = name_to_number.find(number_to_name[number]);
	name_to_number.erase(it);
	number_to_name.erase(number);
}

void Contact :: deleteByName(string name)
{
	if(isNewContact(name, ""))
		return;

	map<string, string> :: iterator it;
	it = number_to_name.find(name_to_number[name]);
	name_to_number.erase(name);
	number_to_name.erase(it);
}

bool Contact :: findContact(string name) {
	if(name_to_number.find(name) == name_to_number.end())
		return false;
		
	return true;
}

#endif // CONTACT_H_INCLUDED
