#include "Files.hpp"
#include "C:\Users\Andrzej\source\repos\win-based-dummy-os-cpp\shell\Interfejs.h"


Files::Files()
{
	this->files = std::vector<File>();
}


Files::~Files()
{
}

bool Files::fileExists(std::string name)
{
		std::string comp = getSpecName(name);
		for (File e : files)
		{
			if (e.getName() == comp) return true;
		}
	return false;
}

void Files::mkfile(std::string name, char data[])
{
	if (name.length() == 0)
	{
		DisplayLog("Podano nieprawidlowa nazwe pliku!")
	}
	if (fileExists(name))
	{
		DisplayLog("Plik o podanej nazwie juz istnieje!");
	}
	File newf = File(name);
	//newF.setIndexBlock();
	newf.setSize(sizeof(data));
	files.push_back(newf);
	DisplayLog("Stworzono nowy plik o nazwie: " + name);

}

std::string Files::getFile(std::string name)
{
	std::string comp = getSpecName(name);
	for (File e : files)
	{
		if (e.getName == comp)
		{
			// return zawartosc pliku e.getIndexBlock();
		}
	}
		DisplayLog("Plik o podanej nazwie nie istnieje!");
		return "";
}

void Files::showFiles()
{
	for (File e : files)
	{
		DisplayLog("Plik " + e.getName() + "." + e.getExt() + " rozmiar " + (char) e.getSize());
	}
}

bool Files::rmfile(std::string name)
{
	std::string comp = getSpecName(name);
	int pos = 0;
	for (File e : files) {
		if (e.getName() == comp) {
			Disk.remove(e.getIndexBlock());
			files.erase(files.begin()+pos);
			DisplayLog("Usunieto plik: " + name);
			return true;
		}
		pos++;
	}
	DisplayLog("Brak pliku o podanej nazwie: " + name);
	return false;
}

