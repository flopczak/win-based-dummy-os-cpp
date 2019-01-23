#include "../file/Directory.hpp"


Directory::Directory()
{
	this->f = Files();
	////("Utworzono katalog");
	std::cout << "Utworzono katalog" << std::endl;
}


Directory::~Directory()
{
}

bool Directory::setName(std::string newname)
{
	this->name = newname;
	////("Ustawiono nazwe katalogu na " + newname);
	std::cout << "Ustawiono nazwe katalogu na " + newname << std::endl;
	return this->name == newname;
}

std::string Directory::getName()
{
	return this->name;
}

Files Directory::getFiles()
{
	return this->f;
}
