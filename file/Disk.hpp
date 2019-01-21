#include "Directory.hpp"

class Disk
{
private:
	char HDD[1024];
	bool zajBloki[32];
public:
	Disk();
	~Disk();
	std::string pobierzBlok(int);
	std::string wypiszPlik(int);
	bool czyZaj(int);
	int znajdzWolny(int);
	int dodajDane(std::string, int);

};