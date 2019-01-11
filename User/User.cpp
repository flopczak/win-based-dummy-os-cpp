#include "FileAccess.hpp"
#include "User.hpp"
#include <random>

User::User() {}
User::User(string username, string password) 
{
	this->username = username;
	this->password = password;
	this->generateSID();
	User::addToUserList(this);
}
User::~User() {}

//Deklaracja zmiennych statycznych
string User::currentLoggedUser = "";
vector<User*> User::userList = {};
vector<User*> User::standardUserGroup = {};
vector<User*> User::adminGroup = {};

void User::createAdmin()
{
	setUsername("Admin");
	setPassword("");
	setSID("a-1");
	addUserToAdminGroup(this);
}

//setters
void User::setUsername(string username) 
{
	this->username = username;
}
void User::setPassword(string password) 
{
	this->password = password;
}
void User::setSID(string SID) 
{
	this->SID = SID;
}
//Statyczna funkcja do przypisania obecnie "zalogowanego" uzytkownika
void User::setCurrentLoggedUser(string SID) 
{
	User::currentLoggedUser = SID;
}

//getters
string User::getUsername() 
{
	return username;
}
string User::getPassword() 
{
	return password;
}
string User::getSID() 
{
	return SID;
}
// Statyczna funkcja do pozyskania obecnie "zalogowanego" uzytkownika
string User::getCurrentLoggedUser() 
{
	return User::currentLoggedUser;
}
//other functions
void User::createUser() 
{
	string temp;
	std::cout << "Podaj nazwe uzytkownika: ";
	std::cin >> temp;
	this->setUsername(temp);
	std::cout << "\nPodaj haslo: ";
	std::cin >> temp;
	this->setPassword(temp);
	this->generateSID();
	addUserToStandardUserGroup(this);
	User::addToUserList(this);
}
void User::deleteUser(string username) 
{
	User* user = User::getUserbyName(username);
	if (currentLoggedGotAdminPermissions() == true) {
		if (user->getSID() == User::getCurrentLoggedUser()) {
			std::cout << "Uzytkownik jest obecnie zalogowany.\n";
			return;
		}
		if (user->getSID()[0] == 'a') {
			vector<User*>::iterator it;
			for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
				if ((*it)->getSID() == user->getSID()) {
					User::adminGroup.erase(it);
				}
			}
		}
		if (user->getSID()[0] == 's') {
			vector<User*>::iterator it;
			for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
				if ((*it)->getSID() == user->getSID()) {
					User::standardUserGroup.erase(it);
					break;
				}
			}
		}
		vector<User*>::iterator it;
		for (it = User::userList.begin(); it != User::userList.end(); it++) {
			if ((*it)->getSID() == user->getSID()) {
				User::userList.erase(it);
				break;
			}
		}
	}
	else {
		std::cout << "Wystapil blad. Brak uprawnien.\n";
		return;
	}
	std::cout << "Pomyslnie usunieto uzytkownika.\n";
	delete user;
}
void User::changePassword() 
{
	string check, temp;
	std::cout << "Podaj stare haslo: ";
	std::cin >> check;
	while (check != this->getPassword()) {
		std::cout << "\nBledne haslo! Sprobuj ponownie lub zakoncz wpisujac '0'.";
		std::cin >> check;
		if (check == "0") return;
	}
	std::cout << "Podaj nowe haslo: ";
	std::cin >> temp;
	std::cout << "\nPowtorz wprowadzone haslo:  ";
	std::cin >> check;
	while (check != temp) {
		std::cout << "\nWprowadzone hasla nie sa takie same.  Sprobuj ponownie lub zakoncz wpisujac '0'.";
		std::cin >> check;
		if (check == "0") return;
	}
	this->setPassword(temp);
	std::cout << "\nPoprawnie zmieniono haslo!\n";
}
void User::logOut() {
	User::setCurrentLoggedUser("-1");
	std::cout << "Wylogowano.\n";
}
void User::logIn() {
	User::logOut();
	string temp;
	std::cout << "Podaj nazwe uzytkownika: ";
	std::cin >> temp;
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == temp) {
			if ((*it)->getPassword() == "") break;
			else if ((*it)->getPassword() != "") {
				std::cout << "Podaj haslo: ";
				std::cin >> temp;
				while (temp != (*it)->getPassword()) {
					std::cout << "\nBledne haslo! Sprobuj ponownie lub zakoncz wpisujac '0'.";
					std::cin >> temp;
					if (temp == "0") return;
				}
				break;
			}
		}
	}
	if (it == User::userList.end()) {
		std::cout << "Bledna nazwa uzytkownika\n";
		return;
	}
	User::setCurrentLoggedUser((*it)->getSID());
	std::cout << "Pomyslnie zalogowano. Biezacy uzytkownik: "; User::printUser(*it);
	return;
}
void User::generateSID() 
{
	vector<User*>::iterator it;
	int random = rand() % 899 + 100;
	//std::cout << "Pierwszy rand: " << random;
	string strRandom = std::to_string(random);
	bool not_found = false;
	string tempSID;
	std::size_t found = 0;

	while (not_found != true) {
		for (it = User::userList.begin(); it != User::userList.end(); it++) {
			tempSID = (*it)->getSID();
			//std::cout<< "tempSID: " << tempSID << " (*it->getSID()): " << (*it)->getSID() << "\n";
			found = tempSID.find(strRandom);
			//std::cout << " found: " << found << "\n";
			if (found != std::string::npos) {
			//	std::cout << " Znalazlem! Przerywam." << std::endl;
				random = rand() % 899 + 100;
				strRandom = std::to_string(random);
			//	std::cout << "Przerwano wiec stworzylem nowy: " << strRandom;
				break;
			}
		}
		if (found == std::string::npos) {
		//	std::cout << "Za petelka, nie znalazlem wiec tworze i przydzielam!\n";
			not_found = true;
		}
	}
	this->setSID(strRandom);
}
void User::printUser(User* user) {
	std::cout << "Nazwa uzytkownika: " << user->getUsername() << " haslo: " << user->getPassword() << " SID: " << user->getSID() << "\n";
}
bool User::currentLoggedGotAdminPermissions()
{
	string temp = User::getCurrentLoggedUser();
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		if ((*it)->getSID() == temp) return true;
	}
	return false;
}
//Operations on Lists
User* User::getUserbyName(string name) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == name) {
			return *it;
		}
	}
	return nullptr;
}

void User::viewUserList() 
{
	std::cout << "Lista wszystkichh uzytkownikow: " << std::endl;
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		std::cout << "Nazwa uzytkownika: " << (*it)->getUsername() << " haslo: " << (*it)->getPassword() << " SID: " << (*it)->getSID() << "\n";
	}
}
void User::viewStandardUserGroup() 
{
	std::cout << "Lista standardowych uzytkownikow: " << std::endl;
	vector<User*>::iterator it;
	for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
		std::cout << "Nazwa uzytkownika: " << (*it)->getUsername() << " SID: " << (*it)->getSID() << "\n";
	}
}
void User::viewAdminUserGroup() 
{
	std::cout << "Lista Administratorow: \n";
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		std::cout << "Nazwa uzytkownika: " << (*it)->getUsername() << " SID: " << (*it)->getSID() << "\n";
	}
}

void User::addToUserList(User* user)
{
	User::userList.push_back(user);
}
void User::addUserToStandardUserGroup(User* user) 
{
	vector<User*>::iterator itS, itG;
		for (itS = User::standardUserGroup.begin(); itS != User::standardUserGroup.end(); itS++) {
			if (user->getSID() == (*itS)->getSID()) {
				std::cout << "Uzytkownik znajduje sie juz na liscie.\n"; 
				return;
			}
	}
		for(itG = User::adminGroup.begin(); itG!= User::adminGroup.end(); itG++)
		{
			if (user->getSID() == (*itG)->getSID()) {
				User::adminGroup.erase(itG);
			}
		}
		string temp = user->getSID();
		string ending;
		if (temp[0] == 'a') {
			ending.push_back(temp[2]);
			ending.push_back(temp[3]);
			ending.push_back(temp[4]);
			user->setSID("s-" + ending);
		}
		else user->setSID("s-" + user->getSID());
		User::standardUserGroup.push_back(user);
}
void User::addUserToAdminGroup(User* user) 
{
	vector<User*>::iterator itG,itS;
	if (currentLoggedGotAdminPermissions() == true) {
		for (itG = User::adminGroup.begin(); itG != User::adminGroup.end(); itG++) {
			if (user->getSID() == (*itG)->getSID()) {
				std::cout << "uzytkownik znajdujes sie juz na liscie Adminow.\n";
				return;
			}
		}
		for (itS = User::standardUserGroup.begin(); itS != User::standardUserGroup.end(); itS++) {
			if (user->getSID() == (*itS)->getSID()) {
				User::standardUserGroup.erase(itS);
				break;
			}
		}
		string temp = user->getSID();
		string ending;
		if (temp[0] == 's') {
			ending.push_back(temp[2]);
			ending.push_back(temp[3]);
			ending.push_back(temp[4]);
			user->setSID("a-" + ending);
		}
		User::adminGroup.push_back(user);
	}
	else  std::cout << "Obecnie zalogowany uzytkownik nie ma uprawnien administratora!.\n"; 
	
}

