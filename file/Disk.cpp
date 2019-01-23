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
	DisplayLog("Usunieto dysk :C");
	formatuj();
	//std::cout << "Usunieto dysk :C" << std::endl;
}


std::string Disk::pobierzBlok(int index)
{
	DisplayLog("Odczytuje zawartosc bloku o indeksie: " + to_string(index));
	//std::cout << "Odczytuje zawartosc bloku o indeksie: " + to_string(index) << std::endl;

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
	DisplayLog("Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index));
	//std::cout << "Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index) << std::endl;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (HDD[i] != -1)
		{
			//DisplayLog("Przechodze do bloku danych numer: " + HDD[i]);
			//std::cout << "Przechodze do bloku danych numer: " + to_string(HDD[i]) << std::endl;
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
	DisplayLog("Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny.");
	//std::cout << "Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny." << std::endl;
	return zajBloki[index];
}

int Disk::znajdzWolny(int index)
{
	DisplayLog("Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index));
	//std::cout << "Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index) << std::endl;
	for (int i = index; i < 32; i++)
	{
		if (!czyZaj(i))
		{
			DisplayLog("Znaleziono wolny blok o numerze " + to_string(i));
			//std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	for (int i = 0; i < index; i++)
	{
		if (!czyZaj(i))
		{
			DisplayLog("Znaleziono wolny blok o numerze " + to_string(i));
			//std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	DisplayLog("Nie znaleziono wolnego bloku.");
	//std::cout << "Nie znaleziono wolnego bloku." << std::endl;
	return -1;
}

int Disk::dodajDane(std::string name, std::string dane, int index)
{
	if (name.length() == 0)
	{
		DisplayLog("Nie podano nazwy pliku!");
		//std::cout << "Nie podano nazwy pliku!" << std::endl;
		return -1;
	}
	if (root.f.fileExists(name) == -1)
	{
		std::string temp = dane;
		if (temp.length() > 32 * 31)
		{
			DisplayLog("Rozmiar pliku przekracza maksymalna wartosc.");
			//std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
			return -1;
		}
		int blokI = znajdzWolny(index);
		//std::cout << blokI << std::endl;
		if (blokI == -1)
		{
			DisplayLog("Brak wolnych blokow!");
			//std::cout << "Brak wolnych blokow!" << std::endl;
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
					DisplayLog("Brak wolnego miejsca na dysku!");
					//std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
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
		DisplayLog("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
		//std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " +
			to_string(blokI) << std::endl;
		return blokI;
	}
	DisplayLog("Plik o podanej nazwie ju¿ istnieje! " + name);
	//std::cout << "Plik o podanej nazwie ju¿ istnieje! " + name << std::endl;
	return -1;
}

int Disk::dodajDane(std::string name, std::string dane)
{
	if (name.length() == 0)
	{
		DisplayLog("Nie podano nazwy pliku!");
		//std::cout << "Nie podano nazwy pliku!" << std::endl;
		return -1;
	}
	if (root.f.fileExists(name) == -1)
	{
		std::string temp = dane;
		if (temp.length() > 32 * 31)
		{
			DisplayLog("Rozmiar pliku przekracza maksymalna wartosc.");
			//std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
			return -1;
		}
		int blokI = znajdzWolny(0);
		//std::cout << blokI << std::endl;
		if (blokI == -1)
		{
			DisplayLog("Brak wolnych blokow!");
			//std::cout << "Brak wolnych blokow!" << std::endl;
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
					DisplayLog("Brak wolnego miejsca na dysku!");
					//std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
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
		DisplayLog("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
		//std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " +
			//to_string(blokI) << std::endl;
		return blokI;
	}
	DisplayLog("Plik o podanej nazwie ju¿ istnieje! " + name);
	//std::cout << "Plik o podanej nazwie ju¿ istnieje! " + name << std::endl;
	return -1;
}

int Disk::dodajpPlik(std::string name)
{
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			DisplayLog("Brak wolnych blokow!");
			//std::cout << "Brak wolnych blokow!" << std::endl;
			return -1;
		}
		zajBloki[blokI] = true;
		root.mkfile(name, blokI);
		DisplayLog("Stworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI));
		//std::cout << "Utworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI)
		//	<< std::endl;
		return blokI;
	}
	DisplayLog("Plik o podanej nazwie juz istnieje" + name);
	//std::cout << "Plik o podanej nazwie juz istnieje" + name << std::endl;
	return -1;
}

void Disk::wypiszBlok(int index)
{
	DisplayLog("Wypisuje blok o podanym indeksie " + to_string(index));
	//std::cout << "Wypisuje blok o podanym indeksie " + to_string(index) << std::endl;
	std::string temp;
	if (index != -1)
	{
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (HDD[i] == -1) temp += '-';
			else
			{
				temp += HDD[i];
			}
		}
		std::cout << temp;
	}
}

void Disk::wypiszDysk()
{
	DisplayLog("Wypisuje zawartosc calego dysku.");
	//std::cout << "Wypisuje zawartosc calego dysku." << std::endl;
	for (int i = 0; i < 32; i++)
	{
		wypiszBlok(i);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Disk::wypiszPlik(std::string name)
{
	if (!czyMozna(name))
	{
		DisplayLog("Brak uprawnien do operacji.");
		return;
	}
	DisplayLog("Wypisuje plik " + name);
	//std::cout << "Wypisuje plik " + name << std::endl;
	int i = root.f.fileExists(name);
	if (i != -1)
	{
		std::cout << "";
	}
	std::cout << wypiszPlik(i) << std::endl;
}

void Disk::dopiszDoPliku(std::string name, std::string dane)
{
	if (!czyMozna(name))
	{
		DisplayLog("Brak uprawnien do operacji.");
		return;
	}
	DisplayLog("Dopisuje do pliku " + name);
	//std::cout << "Dopisuje do pliku " + name << std::endl;
	if (dane.length() == 0)
	{
		DisplayLog("Nie mam co dopisac, brak danch.");
		//std::cout << "Nie mam co dopisac, brak danch." << std::endl;
		return;
	}
	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		DisplayLog("Podany plik "+name+" nie istnieje");
		//std::cout << "Podany plik " + name + " nie istnieje" << std::endl;
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
	if (wolne.empty())
	{
		DisplayLog("Plik "+ name +" osiagnal maksymalny rozmiar.");
		//std::cout << "Plik " + name + " osiagnal maksymalny rozmiar." << std::endl;
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		DisplayLog("Dane zbyt duze.");
		//std::cout << "Dane zbyt duze." << std::endl;
		return;
	}
	int pos = 0;
	DisplayLog("Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny");
	//std::cout << "Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny" << std::endl;
	if (wolne.size() != 32)
	{
		int temp = HDD[wolne[0] - 1];
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
	DisplayLog("Dopisujemy do pliku " + name);
	//std::cout << "Dopisujemy do pliku " + name << std::endl;
	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			DisplayLog("Brak wolnych blokow.");
			//std::cout << "Brak wolnych blokow!" << std::endl;
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
	if (!czyMozna(name))
	{
		DisplayLog("Brak uprawnien do operacji.");
		return;
	}
	DisplayLog("Usuwam plik " + name);
	int blokI = root.f.fileExists(name);
	//std::cout << "Usuwam plik " + name << std::endl;
	if (blokI != -1)
	{
		for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
		{
			if (HDD[i] != -1)
			{
				zajBloki[HDD[i]] = false;

				for (int j = HDD[i] * 32; j < (HDD[i] * 32) + 32; j++)
				{
					HDD[j] = -1;
				}
				HDD[i] = -1;
			}
		}
		zajBloki[blokI] = false;
		root.f.rmfile(name);
		int pos = 0;
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				root.f.openFiles.erase(root.f.openFiles.begin() + pos);
				DisplayLog("Usunieto plik "+ name +" z tablicy otwartosci.");
				//std::cout << "Usunieto plik " + name + " z tablicy otwartosci." << std::endl;
				break;
			}
			pos++;
		}
	}
	DisplayLog("Plik o podanej nazwie juz nie istnieje " + name);
	//std::cout << "Plik o podanej nazwie juz nie istnieje " + name << std::endl;
}

bool Disk::open(std::string name)
{
	DisplayLog("Otwieram plik o podanej nazwie " + name);
	//std::cout << "Otwieram plik o podanej nazwie " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				DisplayLog("Plik "+ name +" juz jest otwarty");
				std::cout << "Plik " + name + " juz jest otwarty" << std::endl;
				return false;
			}
		}
		root.f.openFiles.push_back(name);
		DisplayLog("Pomyslnie otworzono plik " + name);
		//std::cout << "Pomyslnie otworzono plik " + name << std::endl;
		return true;
	}
	DisplayLog("Brak pliku o podanej nazwie " + name);
	//std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	return false;
}

bool Disk::close(std::string name)
{
	DisplayLog("Zamykam plik " + name);
	//std::cout << "Zamykam plik " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		int pos = 0;
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				root.f.openFiles.erase(root.f.openFiles.begin() + pos);
				DisplayLog("Zamknieto plik " + name);
				//std::cout << "Zamknieto plik" + name << std::endl;
				return true;
			}
			pos++;
		}
		DisplayLog("Plik "+ name +" nawet nie byl otwarty.");
		//std::cout << "Plik " + name + " nawet nie byl otwarty." << std::endl;
		return false;
	}
	DisplayLog("Brak pliku o podanej nazwie " + name);
	//std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	return false;
}

bool Disk::status(std::string name)
{
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				DisplayLog("Plik "+ name +" jest juz otwarty.");
				//std::cout << "Plik " + name + " jest juz otwarty." << std::endl;
				return true;
			}
		}
		DisplayLog("Plik "+name+" nie jest otwarty.");
		//std::cout << "Plik " + name + " nie jest otwarty." << std::endl;
		return false;
	}
	DisplayLog("Plik o podanej nazwie nie istnieje.");
	//std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
	return false;
}

void Disk::nadpiszPlik(std::string name, std::string dane)
{
	if (!czyMozna(name))
	{
		DisplayLog("Brak uprawnien do operacji.");
		return;
	}
	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		DisplayLog("Plik o podanej nazwie nie istnieje " + name);
		//std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
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
				int facl = acl.readPermissions(fname);
				if (facl > acl.getUserPermissions())
				{
					DisplayLog("Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname);
					//std::cout << "Obecny uzytkownik nie ma wystarczajacych uprawnien  do pliku " + fname << std::endl;
					//std::cout << facl << " > " << acl.getUserPermissions() << std::endl;
					return false;
				}
				DisplayLog("Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname);
				//std::cout << "Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname << std::endl;
				//std::cout << facl << " < " << acl.getUserPermissions() << std::endl;
				return true;
			}
			comp = "";
		}
		return false;
	}
	DisplayLog("Plik o podanej nazwie nie istnieje " + fname);
	//std::cout << "Plik o podanej nazwie nie istnieje " + fname << std::endl;
	return false;
}

void Disk::wypiszBlokIndeksowy(int index)
{
	DisplayLog("Wypisuje zawartosc bloku indeksowego nr " + to_string(index));
	//std::cout << "Wypisuje zawartosc bloku indeksowego nr " + to_string(index) << std::endl;
	if (index != -1)
	{
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (HDD[i] == -1) std::cout << '-';
			else
			{
				std::cout << static_cast<int>(HDD[i]) << "";
			}
		}
		std::cout << std::endl;
	}
}

void Disk::wypiszKatalog()
{
	this->root.f.showFiles();
}

std::string Disk::sciezka(std::string name)
{
	std::string path;
	if (root.f.fileExists(name) != -1)
	{
		return root.getName() + ":\\" + name;
	}
	DisplayLog("Plik o podanej nazwie nie istnieje.");
	//std::cout << "Plik o podanej nazwie nie istnieje." << std::endl;
	return "";
}

void Disk::formatuj()
{
	Acl acl = Acl();
	if (acl.getUserPermissions() == 5)
	{
		root.f.openFiles.clear();
		root.f.files.clear();
		for (int i = 0; i < 1024; i++)
		{
			HDD[i] = -1;
		}
		for (int i = 0; i < 32; i++)
		{
			zajBloki[i] = false;
		}
	}
	else
	{
		DisplayLog("Brak uprawnien do operacji.");
	}
}
