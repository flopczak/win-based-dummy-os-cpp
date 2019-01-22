#include "File.hpp"


File::File(std::string name)
{
	std::istringstream f(name);
	std::string temp;
	std::getline(f, temp, '.');
	this->name = temp;
	std::getline(f, temp);
	this->ext = temp;
	//this->accessLevel = getUserPermissions();
}


File::~File()
= default;

std::string File::getName()
{
	return this->name;
}

bool File::setName(std::string newname)
{
	std::istringstream f(newname);
	std::string temp;
	std::getline(f, temp, '.');
	this->name = temp;
	std::getline(f, temp);
	this->ext = temp;
	return this->name + "." + this->ext == newname;
}

std::string File::getExt()
{
	return this->ext;
}

bool File::setExt(std::string newext)
{
	this->ext = newext;
	return this->ext == newext;
}



int File::getIndexBlock()
{
	return this->indexBlock;
}

bool File::setIndexBlock(int newiblock)
{
	this->indexBlock = newiblock;
	return this->indexBlock == newiblock;
}

int File::getAccessLevel()
{
	return this->acl;
}

bool File::setAccessLevel(int newAL)
{
	this->acl = newAL;
	return this->acl == newAL;
}

std::string File::getSpecName(std::string name)
{
	std::istringstream f(name);
	std::string temp;
	std::getline(f, temp, '.');
	return temp;
}
