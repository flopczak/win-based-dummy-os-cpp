#include "Disk.hpp"



Disk::Disk()
{
	for (int i; i < 1024; i++)
	{
		HDD[i] = -1;
	}
}


Disk::~Disk()
{
}

std::string Disk::pobierzBlok(int index)
{
	std::string zawartosc = "";
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		zawartosc += this->HDD[i];
	}
	return zawartosc;
}

std::string Disk::wypiszPlik(int index)
{
	std::string zawartosc = "";
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (HDD[i] != '-1')
		{
			for (int j = i * 32; j < (i * 32) + 32; j++)
			{
				zawartosc += HDD[j];
			}
		}
	}
	return std::string();
}

bool Disk::czyZaj(int index)
{
	return zajBloki[index];
}

int Disk::znajdzWolny(int index)
{
	for (int i = index; i < 32; i++) {
		if (!czyZaj(i)) {
			return i;
		}
	}
	for (int i = 0; i < index; i++) {
		if (!czyZaj(i)) {
			return i;
		}
	}
	return -1;
}

int Disk::dodajDane(char[] dane, int index)
{
	return 0;
}

