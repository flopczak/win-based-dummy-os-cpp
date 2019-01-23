#include "../file/Disk.hpp"

Disk::Disk()
{
	for (int i = 0; i < 1024; i++)
	{
		this->HDD[i] = -1;
	}
	this->root = Directory();
	this->root.setName("root");
}


Disk::~Disk()
{
	////("Usunieto dysk :C");
	std::cout << "Usunieto dysk :C" << std::endl;
}

// NIE UZYTKOWNIK
void Disk::pobierzBlok(int index)
{
	////("Odczytuje zawartosc bloku o indeksie: " + to_string(index));
	std::cout << "Odczytuje zawartosc bloku o indeksie: " + to_string(index) << std::endl;

	std::string zawartosc;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		zawartosc += this->HDD[i];
	}
	std::cout << zawartosc << std::endl;
}

void Disk::wypiszPlik(int index)
{
	std::string zawartosc;
	////("Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index));
	std::cout << "Wypisuje plik o podanym numerze bloku indeksowego: " + to_string(index) << std::endl;
	for (int i = index * 32; i < (index * 32) + 32; i++)
	{
		if (this->HDD[i] != -1)
		{
			////("Przechodze do bloku danych numer: " + HDD[i]);
			std::cout << "Przechodze do bloku danych numer: " + to_string(HDD[i]) << std::endl;
			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				if (this->HDD[j] != -1)
				{
					zawartosc += this->HDD[j];
				}
			}
		}
	}
	std::cout << zawartosc << std::endl;
}

bool Disk::czyZaj(int index)
{
	////("Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny.");
	std::cout << "Sprawdzam czy blok o indeksie " + to_string(index) + " jest wolny." << std::endl;
	return zajeBloki[index];
}

int Disk::znajdzWolny(int index)
{
	////("Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index));
	std::cout << "Szukam pierwszego wolnego bloku od podanego indeksu " + to_string(index) << std::endl;
	for (int i = index; i < 32; i++)
	{
		if (!czyZaj(i))
		{
			////("Znaleziono wolny blok o numerze " + to_string(i));
			std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	for (int i = 0; i < index; i++)
	{
		if (!czyZaj(i))
		{
			////("Znaleziono wolny blok o numerze " + to_string(i));
			std::cout << "Znaleziono wolny blok o numerze " + to_string(i) << std::endl;
			return i;
		}
	}
	////("Nie znaleziono wolnego bloku.");
	std::cout << "Nie znaleziono wolnego bloku." << std::endl;
	return -1;
}

bool Disk::open(std::string name)
{
	////("Otwieram plik o podanej nazwie " + name);
	std::cout << "Otwieram plik o podanej nazwie " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				////("Plik "+ name +" juz jest otwarty");
				std::cout << "Plik " + name + " juz jest otwarty" << std::endl;
				return false;
			}
		}
		root.f.openFiles.push_back(name);
		////("Pomyslnie otworzono plik " + name);
		std::cout << "Pomyslnie otworzono plik " + name << std::endl;
		return true;
	}
	////("Brak pliku o podanej nazwie " + name);
	std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	return false;
}

bool Disk::close(std::string name)
{
	////("Zamykam plik " + name);
	std::cout << "Zamykam plik " + name << std::endl;
	if (root.f.fileExists(name) != -1)
	{
		int pos = 0;
		for (auto e : root.f.openFiles)
		{
			if (e == name)
			{
				root.f.openFiles.erase(root.f.openFiles.begin() + pos);
				////("Zamknieto plik " + name);
				std::cout << "Zamknieto plik" + name << std::endl;
				return true;
			}
			pos++;
		}
		////("Plik "+ name +" nawet nie byl otwarty.");
		std::cout << "Plik " + name + " nawet nie byl otwarty." << std::endl;
		return false;
	}
	////("Brak pliku o podanej nazwie " + name);
	std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
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
				////("Plik "+ name +" jest juz otwarty.")
				std::cout << "Plik " + name + " jest juz otwarty." << std::endl;
				return true;
			}
		}
		////("Plik "+name+" nie jest otwarty.")
		std::cout << "Plik " + name + " nie jest otwarty." << std::endl;
		return false;
	}
	////("Plik o podanej nazwie nie istnieje.");
	std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
	return false;
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
				Acl *a = new Acl();
				int sranko = a->readPermissions(fname);
				if (sranko < e.getAccessLevel())
				{
					////("Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname);
					std::cout << "Obecny uzytkownik nie ma wystarczajacych uprawnien do pliku " + fname + " poziom dostepu " + to_string(sranko) << std::endl;
					return false;
				}
				////("Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname);
				std::cout << "Obecny uzytkownik posiada wystarczajace uprawnienia do pliku " + fname << std::endl;
				return true;
			}
			comp = "";
		}
		return false;
	}
	////("Plik o podanej nazwie nie istnieje " + fname);
	std::cout << "Plik o podanej nazwie nie istnieje " + fname << std::endl;
	return false;
}

void Disk::wypiszBlok(int index)
{
	////("Wypisuje blok o podanym indeksie " + to_string(index));
	//std::cout << "Wypisuje blok o podanym indeksie " + to_string(index) << std::endl;
	std::string temp;
	if (index != -1) {
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) temp += '-';
			else
			{
				temp += this->HDD[i];
			}
		}
		std::cout << temp;
	}
}

//


// Metoda przeciazona dla interpretera nie dla interfejsu

void Disk::dodajpPlik(std::string name)
{
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			//DisplayLog("Brak wolnych blokow!");
			return;
		}
		zajeBloki[blokI] = true;
		root.mkfile(name, blokI);
		//DisplayLog("Stworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI));
		return;
	}
	//DisplayLog("Plik o podanej nazwie juz istnieje" + name);
	return;
}

void Disk::nadpiszPlik(std::string name, std::string dane)
{
	int blokI = root.f.fileExists(name);
	if (!czyMozna(name)) return;
	if (blokI == -1)
	{
		////("Plik o podanej nazwie nie istnieje " + name);
		std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (koniec == false)
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					this->HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					this->HDD[j] = -1;
					koniec = true;
				}
			}
		}
		else
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			zajeBloki[i] = false;
			this->HDD[i] = -1;
		}
	}
}

void Disk::dopiszDoPliku(std::string name, std::string dane)
{

	////("Dopisuje do pliku " + name);
	std::cout << "Dopisuje do pliku " + name << std::endl;

	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		////("Podany plik "+name+" nie istnieje");
		std::cout << "Podany plik " + name + " nie istnieje" << std::endl;
		return;
	}
	if (!czyMozna(name)) return;
	std::vector<int> wolne;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (this->HDD[i] == -1)
		{
			wolne.push_back(i);
		}
	}
	if (wolne.empty())
	{
		////("Plik "+ name +" osiagnal maksymalny rozmiar.");
		std::cout << "Plik " + name + " osiagnal maksymalny rozmiar." << std::endl;
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		////("Dane zbyt duze.");
		std::cout << "Dane zbyt duze." << std::endl;
		return;
	}
	int pos = 0;
	////("Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny");
	std::cout << "Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny" << std::endl;
	if (wolne.size() != 32)
	{
		int temp = this->HDD[wolne[0] - 1];
		for (int i = temp * 32; i < (temp * 32) + 32; i++)
		{
			if (this->HDD[i] == -1)
			{
				if (pos >= dane.length()) return;
				this->HDD[i] = dane.at(pos);
				pos++;
			}
		}
	}
	////("Dopisujemy do pliku " + name);
	std::cout << "Dopisujemy do pliku " + name << std::endl;
	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			////("Brak wolnych blokow.");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokD] = true;
		this->HDD[e] = blokD;

		for (int e = blokD * 32; e < blokD * 32 + 32; e++)
		{
			if (pos < dane.length())
			{
				this->HDD[e] = dane[pos];
				pos++;
			}
			else
			{
				this->HDD[e] = -1;
				return;
			}
		}
	}
}

void Disk::wypiszPlik(std::string name)
{
	////("Wypisuje plik " + name);
	std::cout << "Wypisuje plik " + name << std::endl;
	int i = root.f.fileExists(name);
	if (i != -1)
	{
		//Brak pliku o podanej nazwie
	}
	if (!czyMozna(name)) return; // nie mozna;
	wypiszPlik(i);
}

void Disk::usunPlik(std::string name)
{
	////("Usuwam plik " + name);
	int blokI = root.f.fileExists(name);

	if (blokI == -1)
	{
		std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	}
	if (!czyMozna(name)) return;
	std::cout << "Usuwam plik " + name << std::endl;

	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{

		if (this->HDD[i] != -1)
		{
			zajeBloki[this->HDD[i]] = false;

			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			this->HDD[i] = -1;
		}
	}
	zajeBloki[blokI] = false;
	root.f.rmfile(name);
	int pos = 0;
	for (auto e : root.f.openFiles)
	{
		if (e == name)
		{
			root.f.openFiles.erase(root.f.openFiles.begin() + pos);
			////("Usunieto plik "+ name +" z tablicy otwartosci.");
			std::cout << "Usunieto plik " + name + " z tablicy otwartosci." << std::endl;
			break;
		}
		pos++;
	}

	////("Plik o podanej nazwie nie istnieje " + name);
	std::cout << "Plik o podanej nazwie juz nie istnieje " + name << std::endl;
}


//////
// FUNKCJE INTERFEJSU

void Disk::dodajDane(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;

	std::string name = vec[0];
	std::string dane = vec[1];
	if (vec.size() == 3)
	{

		int index = stoi(vec[2]);
		if (name.length() == 0)
		{
			////("Nie podano nazwy pliku!");
			std::cout << "Nie podano nazwy pliku!" << std::endl;
			return;
		}
		if (root.f.fileExists(name) == -1)
		{
			std::string temp = dane;
			if (temp.length() > 32 * 31)
			{
				////("Rozmiar pliku przekracza maksymalna wartosc.");
				std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
				return;
			}
			int blokI = znajdzWolny(index);
			//std::cout << blokI << std::endl;
			if (blokI == -1)
			{
				////("Brak wolnych blokow!");
				std::cout << "Brak wolnych blokow!" << std::endl;
				return;
			}
			unsigned int pos = 0;
			int rozm = ceil(temp.length() / 32.0);
			zajeBloki[blokI] = true;
			for (int i = blokI * 32; i < blokI * 32 + rozm * 32; i++)
			{
				if (pos < temp.length())
				{
					int blokD = znajdzWolny(blokI);
					if (blokD == -1)
					{
						////("Brak wolnego miejsca na dysku!");
						std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
						return;
					}
					this->HDD[i] = blokD;
					zajeBloki[blokD] = true;
					for (int e = blokD * 32; e < blokD * 32 + 32; e++)
					{
						if (pos < temp.length())
						{
							this->HDD[e] = temp.at(pos);
							pos++;
						}
						else
						{
							this->HDD[e] = -1;
						}
					}
				}
				else
				{
					break;
				}
			}
			root.f.mkfile(name, blokI);
			////("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
			std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " + to_string(blokI) << std::endl;
			return;
		}
		////("Plik o podanej nazwie ju¿ istnieje! " + name);
		std::cout << "Plik o podanej nazwie ju¿ istnieje! " + name << std::endl;
		return;
	}
	else
	{
		if (name.length() == 0)
		{
			////("Nie podano nazwy pliku!");
			std::cout << "Nie podano nazwy pliku!" << std::endl;
			return;
		}
		if (root.f.fileExists(name) == -1)
		{
			std::string temp = dane;
			if (temp.length() > 32 * 31)
			{
				////("Rozmiar pliku przekracza maksymalna wartosc.");
				std::cout << "Rozmiar pliku przekracza maksymalna wartosc." << std::endl;
				return;
			}
			int blokI = znajdzWolny(0);
			//std::cout << blokI << std::endl;
			if (blokI == -1)
			{
				////("Brak wolnych blokow!");
				std::cout << "Brak wolnych blokow!" << std::endl;
				return;
			}
			unsigned int pos = 0;
			int rozm = ceil(temp.length() / 32.0);
			zajeBloki[blokI] = true;
			for (int i = blokI * 32; i < blokI * 32 + rozm * 32; i++)
			{
				if (pos < temp.length())
				{
					int blokD = znajdzWolny(blokI);
					if (blokD == -1)
					{
						////("Brak wolnego miejsca na dysku!");
						std::cout << "Brak wolnego miejsca na dysku!" << std::endl;
						return;
					}
					this->HDD[i] = blokD;
					zajeBloki[blokD] = true;
					for (int e = blokD * 32; e < blokD * 32 + 32; e++)
					{
						if (pos < temp.length())
						{
							this->HDD[e] = temp.at(pos);
							pos++;
						}
						else
						{
							this->HDD[e] = -1;
						}
					}
				}
				else
				{
					break;
				}
			}
			root.f.mkfile(name, blokI);
			////("Utworzono plik o podanej nazwie z podanymi danymi o bloku indeksowym " + to_string(blokI) );
			std::cout << "Utworzono plik o podanej nazwie " + name + " z podanymi danymi o bloku indeksowym " + to_string(blokI) << std::endl;
			return;
		}
		////("Plik o podanej nazwie ju¿ istnieje! " + name);
		std::cout << "Plik o podanej nazwie ju¿ istnieje! " + name << std::endl;
		return;
	}
}

void Disk::dodajpPlik(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	if (root.f.fileExists(name) == -1)
	{
		int blokI = znajdzWolny(0);
		if (blokI == -1)
		{
			////("Brak wolnych blokow!");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokI] = true;
		root.mkfile(name, blokI);
		////("Stworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI));
		std::cout << "Utworzono plik o podanej nazwie " + name + " z blokiem indeksowym o numerze " + to_string(blokI) << std::endl;
		return;
	}
	////("Plik o podanej nazwie juz istnieje" + name);
	std::cout << "Plik o podanej nazwie juz istnieje" + name << std::endl;
	return;
}

void Disk::wypiszBlok(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	int index = stoi(vec[0]);
	////("Wypisuje blok o podanym indeksie " + to_string(index));
	//std::cout << "Wypisuje blok o podanym indeksie " + to_string(index) << std::endl;
	std::string temp;
	if (index != -1) {
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) temp += '-';
			else
			{
				temp += this->HDD[i];
			}
		}
		std::cout << temp;
	}
}

void Disk::wypiszDysk()
{

	////("Wypisuje zawartosc calego dysku.");
	std::cout << "Wypisuje zawartosc calego dysku." << std::endl;
	for (int i = 0; i < 32; i++)
	{
		wypiszBlok(i); // U mnie dziala
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Disk::wypiszPlik(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	////("Wypisuje plik " + name);
	std::cout << "Wypisuje plik " + name << std::endl;
	int i = root.f.fileExists(name);
	if (i != -1)
	{
		//Brak pliku o podanej nazwie
	}
	if (!czyMozna(name)) return; // nie mozna;
	wypiszPlik(i);
}

void Disk::dopiszDoPliku(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	if (vec.size() == 1)
	{
		////("Nie mam co dopisac, brak danch.");
		std::cout << "Nie mam co dopisac, brak danch." << std::endl;
		return;
	}
	std::string dane = vec[1];
	////("Dopisuje do pliku " + name);
	std::cout << "Dopisuje do pliku " + name << std::endl;

	int blokI = root.f.fileExists(name);
	if (blokI == -1)
	{
		////("Podany plik "+name+" nie istnieje");
		std::cout << "Podany plik " + name + " nie istnieje" << std::endl;
		return;
	}
	if (!czyMozna(name)) return;
	std::vector<int> wolne;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (this->HDD[i] == -1)
		{
			wolne.push_back(i);
		}
	}
	if (wolne.empty())
	{
		////("Plik "+ name +" osiagnal maksymalny rozmiar.");
		std::cout << "Plik " + name + " osiagnal maksymalny rozmiar." << std::endl;
		return;
	}
	if (sizeof(wolne) * 32 < dane.length())
	{
		////("Dane zbyt duze.");
		std::cout << "Dane zbyt duze." << std::endl;
		return;
	}
	int pos = 0;
	////("Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny");
	std::cout << "Sprawdzamy czy mozemy dopisac do zajetego bloku danych, ktory moze nie byc pelny" << std::endl;
	if (wolne.size() != 32)
	{
		int temp = this->HDD[wolne[0] - 1];
		for (int i = temp * 32; i < (temp * 32) + 32; i++)
		{
			if (this->HDD[i] == -1)
			{
				if (pos >= dane.length()) return;
				this->HDD[i] = dane.at(pos);
				pos++;
			}
		}
	}
	////("Dopisujemy do pliku " + name);
	std::cout << "Dopisujemy do pliku " + name << std::endl;
	for (auto e : wolne)
	{
		int blokD = znajdzWolny(0);
		if (blokD == -1)
		{
			////("Brak wolnych blokow.");
			std::cout << "Brak wolnych blokow!" << std::endl;
			return;
		}
		zajeBloki[blokD] = true;
		this->HDD[e] = blokD;

		for (int e = blokD * 32; e < blokD * 32 + 32; e++)
		{
			if (pos < dane.length())
			{
				this->HDD[e] = dane[pos];
				pos++;
			}
			else
			{
				this->HDD[e] = -1;
				return;
			}
		}
	}
}

void Disk::usunPlik(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	////("Usuwam plik " + name);
	int blokI = root.f.fileExists(name);

	if (blokI == -1)
	{
		std::cout << "Brak pliku o podanej nazwie " + name << std::endl;
	}
	if (!czyMozna(name)) return;
	std::cout << "Usuwam plik " + name << std::endl;

	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{

		if (this->HDD[i] != -1)
		{
			zajeBloki[this->HDD[i]] = false;

			for (int j = this->HDD[i] * 32; j < (this->HDD[i] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			this->HDD[i] = -1;
		}
	}
	zajeBloki[blokI] = false;
	root.f.rmfile(name);
	int pos = 0;
	for (auto e : root.f.openFiles)
	{
		if (e == name)
		{
			root.f.openFiles.erase(root.f.openFiles.begin() + pos);
			////("Usunieto plik "+ name +" z tablicy otwartosci.");
			std::cout << "Usunieto plik " + name + " z tablicy otwartosci." << std::endl;
			break;
		}
		pos++;
	}

	////("Plik o podanej nazwie nie istnieje " + name);
	std::cout << "Plik o podanej nazwie juz nie istnieje " + name << std::endl;
}

void Disk::nadpiszPlik(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	std::string dane = vec[1];
	int blokI = root.f.fileExists(name);
	if (!czyMozna(name)) return;
	if (blokI == -1)
	{
		////("Plik o podanej nazwie nie istnieje " + name);
		std::cout << "Plik o podanej nazwie nie istnieje " + name << std::endl;
		return;
	}
	int pos = 0;
	bool koniec = false;
	for (int i = blokI * 32; i < (blokI * 32) + 32; i++)
	{
		if (koniec == false)
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				if (pos < dane.length())
				{
					this->HDD[j] = dane.at(pos);
					pos++;
				}
				else
				{
					this->HDD[j] = -1;
					koniec = true;
				}
			}
		}
		else
		{
			for (int j = this->HDD[i] * 32; j < (this->HDD[j] * 32) + 32; j++)
			{
				this->HDD[j] = -1;
			}
			zajeBloki[i] = false;
			this->HDD[i] = -1;
		}
	}
}

void Disk::wypiszBlokIndeksowy(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	int index = stoi(vec[0]);
	std::cout << "Wypisuje zawartosc bloku indeksowego nr " + to_string(index) << std::endl;
	if (index != -1) {
		for (int i = index * 32; i < (index * 32) + 32; i++)
		{
			if (this->HDD[i] == -1) std::cout << '-';
			else
			{
				std::cout << static_cast<int>(this->HDD[i]) << "";
			}
		}
		std::cout << std::endl;
	}
}

void Disk::wypiszKatalog()
{
	this->root.f.showFiles();
}

void Disk::sciezkaDoPliku(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	std::string path;
	if (root.f.fileExists(name) != -1)
	{
		std::cout << root.getName() + ":\\" + name << std::endl;
	}
	std::cout << "Plik o podanej nazwie nie istnieje." << std::endl;
}

void Disk::zmienUprawnienia(std::vector<std::string> vec)
{
	if (vec.size() == 0) return;
	std::string name = vec[0];
	int al = stoi(vec[1]);
	if (al > 5) return; //kurwa co za pojebany lvl
	std::vector<File>::iterator it;
	std::string comp;
	if (root.f.fileExists(name) == -1) return; // Brak pliku
	if (Acl::getUserPermissions() == 5)
	{
		for (it = root.f.files.begin(); it != root.f.files.end(); it++)
		{

			comp += (*it).getName() + "." + (*it).getExt();
			if (comp == name)
			{
				(*it).setAccessLevel(al);
				return;
			}
			comp = "";
		}
	}
	else
	{
		//brak uprawnien
		return;
	}
}
