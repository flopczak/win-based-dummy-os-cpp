#pragma once
#include "Files.hpp"

class Directory :public Files
{
private:
	std::string name;
	Files files;
public:
	Directory(std::string);
	~Directory();
	bool setName(std::string);
	std::string getName();
	Files getFiles();
};

