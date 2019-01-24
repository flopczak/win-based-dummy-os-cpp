#include <iostream>
#include "Acl.hpp"
#include "User.hpp"
#include <random>
#include <time.h>

User::User() {
	//this->interfejs = new Interfejs();
}
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
}
void User::createGuest() {
	setUsername("Guest");
	setPassword("");
	setSID("g-1");
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
	if (getCurrentLoggedUser()[0] == 'g') {
		cout << "\nGosc nie moze tworzyc uzytkownikow";
		return;
	}
	string temp_name, temp_pass;
	User* temporary = new User();
	cout <<"\nPodaj nazwe uzytkownika: ";
	std::cin >> temp_name;
	while (findInUserGroup(temp_name)) {
		cout <<"\nUzytkownik o podanej nazwie juz istnieje. Podaj nazwe uzytkownika: ";
		cin >> temp_name;
	}
	temporary->setUsername(temp_name);
	cout <<"\nPodaj haslo: ";
	std::cin >> temp_pass;
	temporary->setPassword(temp_pass);
	temporary->generateSID();
	string temp = temporary->getSID();
	string ending;
		ending.push_back(temp[0]);
		ending.push_back(temp[1]);
		ending.push_back(temp[2]);
		temporary->setSID("s-" + ending);
	User::standardUserGroup.push_back(temporary);
	User::addToUserList(temporary);
	cout << "\nPomyslnie utworzono uzytkownika\n";
}
void User::deleteUser(string username)
{	
	if (getCurrentLoggedUser()[0] == 'g') {
		cout <<"\nGosc nie moze usuwac uzytkownikow";
		return;
	}
	if (username == "Guest") {
		cout <<"\nGosc nie moze zostac usuniety";
		return;
	}
	if (username == "Admin" ) {
		cout <<"\nAdmin nie moze zostac usuniety";
		return;
	}
	if (!User::findInUserGroup(username)) {
		cout <<"\nUzytkownik nie istnieje";
		return;
	}
	User* user = User::getUserbyName(username);
	if (username == user->getUsername()) {
		cout << "\n Uzytkownik jest administratorem. Nie moze zostac usuniety\n";
		return;
	}
	if (currentLoggedGotAdminPermissions() == true) {
			if (user->getSID() == User::getCurrentLoggedUser()) {
				cout <<"\nUzytkownik jest obecnie zalogowany.";
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
		cout <<"\nWystapil blad. Brak uprawnien admina.";
		return;
	}
	cout <<"\nPomyslnie usunieto uzytkownika.";
}
void User::changePassword() 
{
	if (getCurrentLoggedUser()[0] == 'g') {
		cout << "Gosc nie moze zmieniac hasla";
		return;
	}
	string check, temp;
	//Interfejs::DisplayLog("\nPodaj stare haslo: ");
	std::cin >> check;
	while (check != this->getPassword()) {
		//Interfejs::DisplayLog("\nBledne haslo! Sprobuj ponownie lub zakoncz wpisujac '0'.");
		std::cin >> check;
		if (check == "0") return;
	}
	//Interfejs::DisplayLog("\nPodaj nowe haslo: ");
	std::cin >> temp;
	//Interfejs::DisplayLog("\nPowtorz wprowadzone haslo: ");
	std::cin >> check;
	while (check != temp) {
		//Interfejs::DisplayLog("\nWprowadzone hasla nie sa takie same.  Sprobuj ponownie lub zakoncz wpisujac '0'.");
		std::cin >> check;
		if (check == "0") return;
	}
	this->setPassword(temp);
	//Interfejs::DisplayLog("\nPoprawnie zmieniono haslo!");
}
void User::logOut() {
	User::setCurrentLoggedUser("-1");
	cout <<"\nWylogowano.";
}
void User::logIn() {
	User::logOut();
	string temp;
	cout <<"\nPodaj nazwe uzytkownika: ";
	std::cin >> temp;
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == temp) {
			if ((*it)->getPassword() == "") break;
			else if ((*it)->getPassword() != "") {
				cout <<"\nPodaj haslo: ";
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
		std::cout << "\nBledna nazwa uzytkownika.";
		return;
	}
	User::setCurrentLoggedUser((*it)->getSID());
	cout << "\nPomyslnie zalogowano uzytkownika\n";
	return;
}
void User::generateSID() 
{
	vector<User*>::iterator it;
	srand(time(NULL));
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
	string napis = "\nNazwa uzytkownika: " + user->getUsername() + " haslo: " + user->getPassword() + " SID: " + user->getSID();
	//interfejs->DisplayLog(napis);
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
string User::getUserBySID(string sid) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getSID() == sid) {
			return (*it)->getUsername();
		}
	}
	return "";
}

void User::viewUserList() 
{
	cout <<"\nLista wszystkich uzytkownikow: \n";
	vector<User*>::iterator it; string napis;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		napis = "\n| Nazwa uzytkownika: " + (*it)->getUsername() + " | Haslo: " + (*it)->getPassword() + " | SID: " + (*it)->getSID();
		cout << napis <<"\n";
		cout << "---------------------------------------------------------------------";
	}
	cout <<"\n";
}
void User::viewStandardUserGroup() 
{
	cout <<"\nLista standardowych uzytkownikow: \n";
	vector<User*>::iterator it; string napis;
	for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {	
		napis = "\n| Nazwa uzytkownika: " + (*it)->getUsername() + " | Haslo: " + (*it)->getPassword() + " | SID: " + (*it)->getSID();
		cout << napis << "\n";
		cout << "---------------------------------------------------------------------";
	}
	cout <<"\n";
}
void User::viewAdminUserGroup() 
{
	cout <<"\nLista Administratorow: \n";
	vector<User*>::iterator it; string napis;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		napis = "\n| Nazwa uzytkownika: " + (*it)->getUsername() + " | Haslo: " + (*it)->getPassword() + " | SID: " + (*it)->getSID();
		cout << napis << "\n";
		cout << "---------------------------------------------------------------------";
	}
	cout <<"\n";
}
bool User::findInAdminUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::adminGroup.begin(); it != User::adminGroup.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}
bool User::findInStandardUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::standardUserGroup.begin(); it != User::standardUserGroup.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}
bool User::findInUserGroup(string username) {
	vector<User*>::iterator it;
	for (it = User::userList.begin(); it != User::userList.end(); it++) {
		if ((*it)->getUsername() == username) {
			return true;
		}
	}
	return false;
}

void User::addToUserList(User* user)
{
	User::userList.push_back(user);
}
void User::addUserToStandardUserGroup(string username)
{
	User* user = new User();
	user = User::getUserbyName(username);
	if (getCurrentLoggedUser()[0] == 'g') {
		cout << "Gosc nie moze dodawac do grup\n";
		return;
	}
	vector<User*>::iterator itS, itG;
	for (itS = User::standardUserGroup.begin(); itS != User::standardUserGroup.end(); itS++) {
		if (user->getSID() == (*itS)->getSID()) {
			std::cout << "Uzytkownik znajduje sie juz na liscie.\n";
			return;
		}
	}
	for (itG = User::adminGroup.begin(); itG != User::adminGroup.end(); itG++)
	{
		if (user->getSID() == (*itG)->getSID()) {
			User::adminGroup.erase(itG);
			break;
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
	cout << "\nPomyslnie dodano uzytkownika\n";
}
void User::addUserToAdminGroup(string username)
{
	User* user = new User();
	user = User::getUserbyName(username);
	vector<User*>::iterator itG, itS;
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
	cout << "\nPomyslnie dodano uzytkownika\n";
}
void User::UserStart() {
	User* admin = new User();
	admin->createAdmin();
	User::adminGroup.push_back(admin);
	User::userList.push_back(admin);
	User::setCurrentLoggedUser(admin->getSID());

	User* guest = new User();
	guest->createGuest();
	User::userList.push_back(guest);
	cout << "POMYSLNIE WYSTARTOWANO MODUL\n";
}
void User::printCurrentLoggedUser() {
	cout <<"\nObecnie zalogowany uzytkownik: ";
	vector<User*>::iterator it;
	for (it = userList.begin(); it != userList.end(); it++) {
		if ((*it)->getSID() == User::getCurrentLoggedUser()) {
			cout << (*it)->getUsername();
		}
	}
}

