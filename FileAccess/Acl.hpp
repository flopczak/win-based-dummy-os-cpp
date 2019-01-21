#pragma once
#include "User.hpp"
#include <map>

using namespace std;

enum Permissions {
	ZERO = 1,
	STANDARD_READ = 2,
	STANDARD_WRITE = 3,
	ADMIN_READ = 4,
	ADMIN_WRITE = 5,
};

struct Mask {
	int values[5];
};

class Acl {

private:
	string owner;
	Mask mask;
	map<string, Mask> Ace_container;

public:
	static map<string, Acl*> AclList;
	Acl();  
	~Acl();
				//Setters

				//Getters
	Mask getMask();
	string getOwner();
				//Others
	static void viewAclList();													// Wyswietlenie wszystkich ACL powiazanych z plikami
	static void viewFileAcl(string file_name);									// Wyswietlenie ACL konkretnego pliku
				//
	void viewCurrentFileAcl();													// Wyswietlanie ACL bierzacego pliku
	void setDefaultPermissions();												// Ustanowienie podstawowych wpisow ACE
	static void setAdditionalPermissions(string file_name);						// Dodanie dodatkowych wpisów ACE 
	void defineMask();															// Inicjalizacja maski
	static void permissionsToCharArray(Permissions permissions, int* out);		// Translacja "Flagi" na odpowiednie wartosci w char array
	int readPermissions(string filename);										// zwraca uprawnienia w postaci inta
	static int getUserPermissions();											//Zwraca maks. poczatkowe uprawnienia obecnego uzytkownika
};