#include "../file/Files.hpp"


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
		if (comp == name)
		{
			DisplayLog("Znaleziono wpis katalogowy pliku o podanej nazwie: " + name);
			return e.getIndexBlock();
		}
		comp = "";
	}
	DisplayLog("Nie znaleziono wpisu katalogowego pliku o podanej nazwie: " + name);
	return -1;
}


void Files::mkfile(std::string name, int bloki)
{
	Acl* usr = new Acl();
	File newf = File(name);
	newf.setIndexBlock(bloki);
	newf.setAccessLevel(usr->getUserPermissions());
	//std::cout << newf.getAccessLevel();
	files.push_back(newf);
	//DisplayLog("Stworzono nowy plik o nazwie: " + name);
	delete usr;
}

void Files::showFiles()
{
	for (File e : files)
	{
		DisplayLog(
			"Plik " + e.getName() + "." + e.getExt() + " IB[" + to_string(e.getIndexBlock()) + "] ACL[" + to_string(
				e.getAccessLevel()) + "]");
	}
}

bool Files::rmfile(std::string name)
{
	std::string comp;
	int pos = 0;
	for (File e : files)
	{
		if ((comp += e.getName() + "." + e.getExt()) == name)
		{
			files.erase(files.begin() + pos);
			DisplayLog("Usunieto wpis katalogowy pliku: " + name);
			return true;
		}
		comp = "";
		pos++;
	}
	DisplayLog("Brak wpisu katalogowego pliku: " + name);
	return false;
}
