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
	std::string pobierzBlok(std::vector<std::string> v);
	std::string wypiszPlik(std::vector<std::string> v);
	bool czyZaj(std::vector<std::string> v);
	int znajdzWolny(std::vector<std::string> v);
	int dodajDane(std::vector<std::string> v);
	//int dodajDane(std::vector<std::string> v);
	int dodajpPlik(std::vector<std::string> v);
	void wypiszBlok(std::vector<std::string> v);
	void wypiszDysk();
	//void wypiszPlik(std::vector<std::string> v);
	void dopiszDoPliku(std::vector<std::string> v);
	void usunPlik(std::vector<std::string> v);
	bool open(std::vector<std::string> v);
	bool close(std::vector<std::string> v);
	bool status(std::vector<std::string> v);
	void nadpiszPlik(std::vector<std::string> v);
	bool czyMozna(std::vector<std::string> v);
	void wypiszBlokIndeksowy(std::vector<std::string> v);
	void wypiszKatalog();
	std::string sciezka(std::vector<std::string> v);
	void formatuj();
};
