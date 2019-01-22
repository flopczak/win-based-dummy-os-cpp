#include "../file/Directory.hpp"


Directory::Directory()
{
	this->f = Files();
}


Directory::~Directory()
{
}

bool Directory::setName(std::string newname)
{
	this->name = newname;
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
