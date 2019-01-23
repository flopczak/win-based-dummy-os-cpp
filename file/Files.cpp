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
			////("Znaleziono wpis katalogowy pliku o podanej nazwie: " + name);
			std::cout << "Znaleziono wpis katalogowy pliku o podanej nazwie: " + name << std::endl;
			return e.getIndexBlock();
		}
		comp = "";
	}
	////("Nie znaleziono wpisu katalogowego pliku o podanej nazwie: " + name);
	std::cout << "Nie znaleziono wpisu katalogowego pliku o podanej nazwie: " + name << std::endl;
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
	////("Stworzono nowy plik o nazwie: " + name);
	std::cout << "Stworzono nowy plik o nazwie: " + name << std::endl;
	delete usr;
}

void Files::showFiles()
{
	for (File e : files)
	{
		////(
		//	"Plik " + e.getName() + "." + e.getExt() + " IB[" + to_string(e.getIndexBlock()) + "] ACL[" + to_string(
		//		e.getAccessLevel()) + "]");
		std::cout << "Plik " + e.getName() + "." + e.getExt() + " IB[" + to_string(e.getIndexBlock()) + "] ACL[" +
			to_string(e.getAccessLevel()) + "]" << std::endl;
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
			////("Usunieto wpis katalogowy pliku: " + name);
			std::cout << "Usunieto wpis katalogowy pliku: " + name << std::endl;
			return true;
		}
		comp = "";
		pos++;
	}
	////("Brak wpisu katalogowego pliku: " + name);
	std::cout << "Brak wpisu katalogowego pliku: " + name << std::endl;
	return false;
}
