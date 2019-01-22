#include "Files.hpp"





Files::Files()
{
	
}


Files::~Files()
= default;

int Files::fileExists(std::string name)
{
	std::string comp;
		for (File e : files)
		{
			comp += e.getName() + "." + e.getExt();
			if (comp == name) return e.getIndexBlock();
			else
			{
				comp = "";
			}
		}
	return -1;
}


void Files::mkfile(std::string name, int bloki)
{
	if (name.length() == 0)
	{
		//DisplayLog("Podano nieprawidlowa nazwe pliku!")
	}
	if (fileExists(name))
	{
		//DisplayLog("Plik o podanej nazwie juz istnieje!");
	}
	File newf = File(name);
	newf.setIndexBlock(bloki);
	files.push_back(newf);
	//DisplayLog("Stworzono nowy plik o nazwie: " + name);

}


std::string Files::getFile(std::string name)
{
	std::string comp = getSpecName(name);
	for (File e : files)
	{
		if (e.getName() == comp)
		{
			// return zawartosc pliku e.getIndexBlock();
		}
	}
		//DisplayLog("Plik o podanej nazwie nie istnieje!");
		return "";
}


void Files::showFiles()
{
	for (File e : files)
	{
		std::cout << "Plik " << e.getName() << "." << e.getExt() << " indeks " << e.getIndexBlock() << std::endl;
	}
}

bool Files::rmfile(std::string name)
{
	std::string comp;
	int pos = 0;
	for (File e : files) {
		if ((comp += e.getName() + "." + e.getExt()) == name) {
			//Disk.remove(e.getIndexBlock());
			files.erase(files.begin()+pos);
			//DisplayLog("Usunieto plik: " + name);
			return true;
		}
		comp = "";
		pos++;
	}
	//DisplayLog("Brak pliku o podanej nazwie: " + name);
	return false;
}

