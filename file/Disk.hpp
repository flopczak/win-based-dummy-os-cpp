#include "Directory.hpp"



class Disk
{
private:
	char HDD[1024];
	bool zajBloki[32];
public:
	Disk();
	~Disk();
	Directory root;
	std::string pobierzBlok(int index);
	std::string wypiszPlik(int index);
	bool czyZaj(int index);
	int znajdzWolny(int index);
	int dodajDane(std::string name, std::string dane, int index);
	int dodajpPlik(std::string name);
	std::string wypiszBlok(int index);
	void wypiszDysk();
	void wypiszPlik(std::string name);
	void dopiszDoPliku(std::string name, std::string dane);
	void usunPlik(std::string name); // usunac z tablicy otwartosci
	bool open(std::string name);
	bool close(std::string name);
	bool status(std::string name);
	void nadpiszPlik(std::string name, std::string dane);
	bool czyMozna(std::string fname);
};
