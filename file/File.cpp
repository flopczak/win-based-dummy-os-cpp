#include "File.hpp"



File::File(std::string name)
{
	std::istringstream f(name);
	std::string temp;
	std::getline(f, temp, '.');
	this->name = temp;
	std::getline(f, temp);
	this->ext = temp;
}


File::~File()
{
}

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
	if (this->name + "." + this->ext == newname)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string File::getExt()
{
	return this->ext;
}

bool File::setExt(std::string newext)
{
	this->ext = newext;
	if (this->ext == newext)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int File::getSize()
{
	return this->size;
}

bool File::setSize(int newsize)
{
	this->size = newsize;

	if (this->size = newsize)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int File::getIndexBlock()
{
	return this->indexBlock;
}

bool File::setIndexBlock(int newiblock)
{
	this->indexBlock = newiblock;
	if (this->indexBlock == newiblock)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int File::getAccessLevel()
{
	return this->accessLevel;
}

bool File::setAccessLevel(int newAL)
{
	this->accessLevel = newAL;

	if (this->accessLevel == newAL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
