#pragma once
#ifndef Dir_h
#define Dir_h
#include "../file/Files.hpp"

class Directory : public Files
{
public:
	std::string name;
	Files f;
	Directory();
	~Directory();
	bool setName(std::string newname);
	std::string getName();
	Files getFiles();
};
#endif