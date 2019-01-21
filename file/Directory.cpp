#include "Directory.hpp"



Directory::Directory(std::string name)
{
	this->name = name;
	this->files = Files();
}


Directory::~Directory()
{
}

bool Directory::setName(std::string newname)
{
	this->name = newname;
	if (this->name == newname) return true;
	return false;
}

std::string Directory::getName()
{
	return this->name;
}

Files Directory::getFiles()
{
	return this->files;
}
