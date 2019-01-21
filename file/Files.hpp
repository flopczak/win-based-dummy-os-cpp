#pragma once
#include "File.hpp"

class Files : public File
{
public:
	std::vector <File> files;
	std::map <Files, bool> openFiles;
	Files();
	~Files();
	bool fileExists(std::string name);
	void mkfile(std::string name, int blokI);
	std::string getFile(std::string name);
	void showFiles();
	bool rmfile(std::string name);
};

