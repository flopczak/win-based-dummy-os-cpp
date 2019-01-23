#pragma once
#ifndef Files_H
#define Files_H
#include "../file/File.hpp"

class Files : public File
{
public:
	std::vector<File> files;
	std::vector<std::string> openFiles;
	Files();
	~Files();
	int fileExists(std::string name);
	int getFileIndex(std::string name);
	void mkfile(std::string name, int blokI);
	std::string getFile(std::string name);
	void showFiles();
	bool rmfile(std::string name);
};
#endif