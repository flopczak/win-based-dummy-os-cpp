#include "../file/Directory.hpp"


Directory::Directory()
{
	this->f = Files();
	DisplayLog("Utworzono katalog");
}


Directory::~Directory()
{
}

bool Directory::setName(std::string newname)
{
	this->name = newname;
	DisplayLog("Ustawiono nazwe katalogu na " + newname);
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
