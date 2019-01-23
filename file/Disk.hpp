#include "../file/Directory.hpp"


class Disk
{
	char HDD[1024];
	bool zajBloki[32];
public:
	Disk();
	~Disk();
	Directory root;
	/*
	std::string pobierzBlok(int index);
	std::string wypiszPlik(int index);
	bool czyZaj(int index);
	int znajdzWolny(int index);
	int dodajDane(std::string name, std::string dane, int index);
	int dodajDane(std::string name, std::string dane);
	int dodajpPlik(std::string name);
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
	std::string sciezka(std::string name);
	void formatuj();
	*/
	std::string pobierzBlok(std::vector v);
	std::string wypiszPlik(std::vector v);
	bool czyZaj(std::vector v);
	int znajdzWolny(std::vector v);
	int dodajDane(std::vector v);
	int dodajDane(std::vector v);
	int dodajpPlik(std::vector v);
	void wypiszBlok(std::vector v);
	void wypiszDysk();
	void wypiszPlik(std::vector v);
	void dopiszDoPliku(std::vector v);
	void usunPlik(std::vector v);
	bool open(std::vector v);
	bool close(std::vector v);
	bool status(std::vector v);
	void nadpiszPlik(std::vector v);
	bool czyMozna(std::vector v);
	void wypiszBlokIndeksowy(std::vector v);
	void wypiszKatalog();
	std::string sciezka(std::vector v);
	void formatuj();
};
