#include "Directory.hpp"
#include <string>

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
	std::string wypiszBlok(int index);
	void wypiszDysk();

};
