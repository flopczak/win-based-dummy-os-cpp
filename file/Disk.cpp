#include "../file/Disk.hpp"

Disk::Disk()
{
	for (int i = 0; i < 1024; i++)
	{
		HDD[i] = -1;
	}
	this->root = Directory();
	this->root.setName("root");
}


Disk::~Disk()
{
}

std::string Disk::pobierzBlok(int index)
{
	std::string zawartosc;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		zawartosc += this->HDD[i];
	}
	return zawartosc;
}

std::string Disk::wypiszPlik(int index)
{
	std::string zawartosc;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (HDD[i] != -1)
		{
			for (int j = HDD[i] * 32; j < (HDD[i] * 32) + 32; j++)
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
	for (int i = index; i < 32; i++)
	{
		if (!czyZaj(i))
		{
			return i;
		}
	}
	for (int i = 0; i < index; i++)
	{
		if (!czyZaj(i))
		{
			return i;
		}
	}
	return -1;
}

int Disk::dodajDane(std::string name, std::string dane, int index)
{
	if (name.length() == 0)
	{
		//DisplayLog("Podano nieprawidlowa nazwe pliku!")
		return -1;
	}
	if (root.f.fileExists(name) == -1)
	{
		std::string temp = dane;
		if (temp.length() > 32 * 31)
		{
			//Interfejs DisplayLog("Rozmiar pliku przekracza maksymalna wartosc");
			return -1;
		}
		int blokI = znajdzWolny(index);
		//std::cout << blokI << std::endl;
		if (blokI == -1)
		{
			//Interfejs DisplayLog("Brak wolnych blokow!");
			return -1;
		}
		unsigned int pos = 0;
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
					if (pos < temp.length())
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
		root.f.mkfile(name, blokI);
		return blokI;
	}
	//Plik istnieje
	return -1;
}

int Disk::dodajpPlik(std::string name)
{
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			//Brak wolnych blokow
			return -1;
		}
		zajBloki[blokI] = true;
		root.mkfile(name, blokI);
		return blokI;
	}
	//Plik juz istnieje
	return -1;
}

std::string Disk::wypiszBlok(int index)
{
	std::string temp;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (HDD[i] == -1) temp += '-';
		else
		{
			temp += HDD[i];
		}
	}
	return temp;
}

void Disk::wypiszDysk()
{
	for (int i = 0; i < 32; i++)
	{
		std::cout << "Blok nr " << i << std::endl;
		std::cout << wypiszBlok(i) << std::endl;
	}
}

void Disk::wypiszPlik(std::string name)
{
	int i = root.f.fileExists(name);
	if (i != -1)
	{
		std::cout << "";
	}
	std::cout << wypiszPlik(i);
}

void Disk::dopiszDoPliku(std::string name, std::string dane)
{
	if (dane.length() == 0) return;
	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		//Podany plik nie istnieje
		return;
	}
	std::vector<int> wolne;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (HDD[i] == -1)
		{
			wolne.push_back(i);
		}
	}
	if (sizeof(wolne) == 0)
	{
		//Plik osiagnal maksymalny rozmiar
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		//Dane zbyt duze
		return;
	}
	int pos = 0;
	//Sprawdzamy czy mozemy dopisac do zajetego bloku danych ktory moze nie byc pelny
	if (sizeof(wolne) != 32)
	{
		int temp = wolne[0];
		for (int i = temp * 32; i < (temp * 32) + 32; i++)
		{
			if (HDD[i] == -1)
			{
				if (pos >= dane.length()) return;
				HDD[i] = dane.at(pos);
				pos++;
			}
		}
	}

	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			//Brak wolnych blokow
			return;
		}
		zajBloki[blokD] = true;
		HDD[e] = blokD;

		for (int e = blokD * 32; e < blokD * 32 + 32; e++)
		{
			if (pos < dane.length())
			{
				HDD[e] = dane[pos];
				pos++;
			}
			else
			{
				HDD[e] = -1;
				return;
			}
		}
	}
}

void Disk::usunPlik(std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		int blokI = root.f.fileExists(name);
		if (blokI != -1)
		{
			for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
			{
				zajBloki[i] = false;
				for (int j = HDD[i] * 32; j < (HDD[i] * 32) + 32; j++)
				{
					HDD[j] = -1;
				}
				HDD[i] = -1;
			}
			zajBloki[blokI] = false;
			root.f.rmfile(name);
			int pos = 0;
			for (auto e : root.f.openFiles)
			{
				if (e == name)
				{
					
					root.f.openFiles.erase(root.f.openFiles.begin() + pos);
					//Usunieto plik z tablicy otwartosci
					break;
				}
				pos++;
			}
		}
	}
}

bool Disk::open(std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				//Plik o podanej nazwie juz jest otwarty
				return false;
			}
		}
		root.f.openFiles.push_back(name);
		return true;
	}
	//Brak pliku o podanej nazwie
	return false;
}

bool Disk::close(std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		int pos = 0;
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				//Plik o podanej nazwie jest otwarty
				root.f.openFiles.erase(root.f.openFiles.begin() + pos);
				return true;
				//Zamknieto plik
			}
			pos++;
		}
		return false;
		//Plik nawet nie byl otwarty
	}
	//Brak pliku o podanej nazwie
	return false;
}

bool Disk::status (std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				//Plik o podanej nazwie juz jest otwarty
				return true;
			}
		}
		return false;
	}
	return false;
}

void Disk::nadpiszPlik(std::string name, std::string dane)
{
	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		//Plik o podanej nazwue nie istnieje
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (koniec == false)
		{
			for (int j = HDD[i] * 32; j < (HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					HDD[j] = -1;
					koniec = true;
				}
			}
		}
		else
		{
			for (int j = HDD[i] * 32; j < (HDD[j] * 32) + 32; j++)
			{
				HDD[j] = -1;
			}
			zajBloki[i] = false;
			HDD[i] = -1;
		}
	}
}

bool Disk::czyMozna(std::string fname)
{
	std::string comp;
	if (root.f.fileExists(fname) != -1)
	{
		for (auto e : root.f.files)
		{
			comp += e.getName() + "." + e.getExt();
			if (comp == fname)
			{
				Acl acl = Acl();
				int facl  = acl.readPermissions(fname);
				if(facl > acl.getUserPermissions())
				{
					
				}
				//Plik o podanej nazwie juz jest otwarty
				return true;
			}
			comp = "";
		}
		return false;
	}
	return false;
}
