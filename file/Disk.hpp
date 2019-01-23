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
	std::string pobierzBlok(int index);
	std::string wypiszPlik(int index);
	bool czyZaj(int index);
	int znajdzWolny(int index);
	void dodajDane(std::string name, std::string dane, int index);
	void dodajDane(std::string name, std::string dane);
	void dodajpPlik(std::string name);
	void wypiszBlok(int index);
	void wypiszDysk();
	void wypiszPlik(std::string name);
	void dopiszDoPliku(std::string name, std::string dane);
	void usunPlik(std::string name);
	bool open(std::string name);
	bool close(std::string name);
	bool status(std::string name);
	void nadpiszPlik(std::string name, std::string dane);
	bool czyMozna(std::string fname);
	void wypiszBlokIndeksowy(int index);
	void wypiszKatalog();
	void sciezkaDoPliku(std::string name);
	void zmienUprawnienia(std::string name, int al);
};
