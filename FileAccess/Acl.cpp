#include "Acl.hpp"
#include "User.hpp"
#include <string>
using namespace std;

Acl::Acl() {
	this->defineMask();
	this->owner = User::getUserBySID(User::getCurrentLoggedUser());
	this->setDefaultPermissions();
}
Acl::~Acl() {}

//Deklaracja zmiennych statycznych
map<string, Acl*> Acl::AclList{};
	//Setters

	//Getters
Mask Acl::getMask() {
	return mask;
}
string Acl::getOwner() {
	return this->owner;
}
	//Others
	void Acl::viewAclList() {
		map<string, Acl*>::iterator it = AclList.begin();
		for (it; it != AclList.end(); it++) {
			cout << it->first << "\n"; 
			it->second->viewCurrentFileAcl();
		}
	}
	void Acl::viewFileAcl(string file_name) {
		if (AclList.find(file_name) != AclList.end()) {
			map<string, Mask> temp;
			string fileOwner;
			cout << "\nFilename: " << file_name << "\n";
			temp = AclList[file_name]->Ace_container;
			fileOwner = AclList[file_name]->getOwner();
			cout << "File owner:" <<fileOwner << "\n" ;
			map<string, Mask>::iterator it = temp.begin();
			for (it; it != temp.end(); it++) {
				cout << it->first << " ";
				for (int i = 0; i <= 5; i++) {
					cout << it->second.values[i];
				}
				cout << "\n";
			}
		}
		else std::cout << "Nie znaleziono pliku\n";
	}
	void Acl::setAdditionalPermissions() {
		string currentLoggedUser = User::getUserBySID(User::getCurrentLoggedUser());
	}
	void Acl::deleteAceInAcl() {}

	void Acl::viewCurrentFileAcl() {
		cout << "File owner: " << getOwner() << "\n";
		map<string, Mask>::iterator it = Ace_container.begin();
		for (it; it != Ace_container.end(); it++) {
			cout << it->first << " ";
			for (int i = 0; i< 5; i++) {
				cout << it->second.values[i];
			}
			cout << "\n";
		}
	}
	void Acl::setDefaultPermissions() {
		Mask temp;
		string currentLoggedUser = User::getUserBySID(User::getCurrentLoggedUser());
		if (currentLoggedUser != "Guest") {
			permissionsToCharArray(ZERO, temp.values);
			Ace_container.insert(pair<string, Mask>("Guest", temp));
		}
		permissionsToCharArray(ADMIN_WRITE, temp.values);
		Ace_container.insert(pair<string, Mask>(currentLoggedUser, temp));
		permissionsToCharArray(ADMIN_WRITE, temp.values);
		Ace_container.insert(pair<string, Mask>("Administratorzy", temp));
		permissionsToCharArray(STANDARD_WRITE, temp.values);
		Ace_container.insert(pair<string, Mask>("Uzytkownicy", temp));
	}
	void Acl::defineMask() {
		this->mask.values[0] = ZERO;
		this->mask.values[1] = STANDARD_READ;
		this->mask.values[2] = STANDARD_WRITE;
		this->mask.values[3] = ADMIN_READ;
		this->mask.values[4] = ADMIN_WRITE;
	}
	void Acl::permissionsToCharArray(Permissions permissions, int* out) {
		for (int i = 0; i <= 4; i++) {
			out[i] = 0;
		}
		for (int i = 0; i < permissions; i++) {
			out[i] = 1;
		}
	}
	int Acl::readPermissions(string filename) {
		int permissions[5];
		int suma=0;
		string currentLoggedUser = User::getUserBySID(User::getCurrentLoggedUser());
		if (AclList.find(filename) != AclList.end()) {
			map<string, Mask> temp_container;
			string fileOwner;
			temp_container = AclList[filename]->Ace_container;
			fileOwner = AclList[filename]->getOwner();
			if (temp_container.find(currentLoggedUser) != temp_container.end()) {
				cout << "Znalazlem osobno \n";
				for (int i = 0; i <= 4; i++) {
					permissions[i] = temp_container[currentLoggedUser].values[i];
					suma += permissions[i];
				}
			}
			else {
				bool found = User::findInAdminUserGroup(currentLoggedUser);
				if (found) {
					cout << "Znalazlem w liscie Adminow";
					for (int i = 0; i <= 4; i++) {
						permissions[i] = temp_container["Administratorzy"].values[i];
						suma += permissions[i];
					}
				}
				 found = User::findInStandardUserGroup(currentLoggedUser);
				if (found) {
					cout << "Znalazlem w liscie standardowej";
					for (int i = 0; i <= 4; i++) {
						permissions[i] = temp_container["Uzytkownicy"].values[i];
						suma += permissions[i];
					}
				}
			}
		}
		else std::cout << "Nie znaleziono pliku\n";
		return suma;
	}
	int Acl::getUserPermissions() {
		string SID = User::getCurrentLoggedUser();
		if (SID[0] == 'a') return ADMIN_WRITE;
		else if (SID[0] == 's') return STANDARD_WRITE;
		else if (SID[0] == 'g') return ZERO;

		else {
			cout << "Blad przy pobieraniu uprawnien\n";
			return 0;
		}
	}