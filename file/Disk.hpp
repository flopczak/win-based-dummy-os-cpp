#include "../file/Directory.hpp"


class Disk
{
private:
	char HDD[1024];
	bool zajeBloki[32];
public:
	Disk();
	~Disk();
	Directory root;
	void pobierzBlok(int index);
	void wypiszPlik(int index);
	bool czyZaj(int index);
	int znajdzWolny(int index);
	bool open(std::string name);
	bool close(std::string name);
	bool status(std::string name);
	bool czyMozna(std::string fname);
	void dodajpPlik(std::string name); // Przeciazona funkcja dla assemblera nie dla uzytkownika
	void Disk::nadpiszPlik(std::string name, std::string dane);
	void Disk::dopiszDoPliku(std::string name, std::string dane);
	void Disk::wypiszPlik(std::string name);
	void Disk::usunPlik(std::string name);
	// Do uzytku uzytkownika V
	void dodajDane(std::vector<std::string> vec);
	void dodajpPlik(std::vector<std::string> vec);
	void wypiszBlok(std::vector<std::string> vec);
	void wypiszDysk();
	void wypiszPlik(std::vector<std::string> vec);
	void dopiszDoPliku(std::vector<std::string> vec);
	void usunPlik(std::vector<std::string> vec);
	void nadpiszPlik(std::vector<std::string> vec);
	void wypiszBlokIndeksowy(std::vector<std::string> vec);
	void wypiszKatalog();
	void sciezkaDoPliku(std::vector<std::string> vec);
	void zmienUprawnienia(std::vector<std::string> vec);
};
