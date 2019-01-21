#pragma once
#include<string>
#include <sstream>
#include <iostream>

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
	File() {};
	~File();

	std::string getName();
	bool setName(std::string);
	std::string getExt();
	bool setExt(std::string);
	int getSize();
	bool setSize(int);
	int getIndexBlock();
	bool setIndexBlock(int);
	int getAccessLevel();
	bool setAccessLevel(int);

	std::string getSpecName(std::string);

};

