#pragma once
#include "Inc.hpp"
class File
{
private:
	std::string name;
	std::string ext;
	int size;
	int indexBlock;
	int accessLevel;
public:
	File(std::string);
	File() = default;
	~File();
	std::string getName();
	bool setName(std::string newname);
	std::string getExt();
	bool setExt(std::string newext);
	int getSize();
	bool setSize(int newsize);
	int getIndexBlock();
	bool setIndexBlock(int newiblock);
	int getAccessLevel();
	bool setAccessLevel(int newAL);

	std::string getSpecName(std::string);

};

