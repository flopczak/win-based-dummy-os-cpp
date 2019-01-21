#include "Disk.hpp"
#include  <math.h>

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
				if (HDD[j] != -1)
				{
					zawartosc += HDD[j];
				}
			}
		}
	}
	return zawartosc;
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

int Disk::dodajDane(std::string dane, int index)
{
	std::string temp = dane;
	if (temp.length() > 32 * 31)
	{
		//Interfejs DisplayLog("Rozmiar pliku przekracza maksymalna wartosc");
		return -1;
	}
	int blokI = znajdzWolny(index);
	if (blokI == -1)
	{
		//Interfejs DisplayLog("Brak wolnych blokow!");
		return  -1;
	}
	int pos = 0;
	int rozm = ceil(temp.length() / 32.0);
	zajBloki[blokI] = true;
	for (int i = blokI * 32; i < blokI * 32 + rozm * 32; i++)
	{
		if (pos < temp.length())
		{
			int blokD = znajdzWolny(blokI);
			if (blokD == -1)
			{
				//Interfejs DisplayLog("Brak wolnego miejsca na dysku");
				return -1;
			}
			HDD[i] = blokD;
			zajBloki[blokD] = true;
			for (int e = blokD * 32; e < blokD * 32 + 32; e++)
			{
				if (pos <= temp.length())
				{
					HDD[e] = temp.at(pos);
					pos++;
				}
				else
				{
					HDD[e] = -1;
				}
			}
		}
		else
		{
			break;
		}
	}
		return blokI;
}

