#pragma once
#include "File.hpp"
#include <vector>

class Files : public File
{
private:
	std::vector <File> files;
public:
	Files();
	~Files();
	bool fileExists(std::string);
	void mkfile(std::string, char data[]);
	std::string getFile(std::string);
	void showFiles();
	bool rmfile(std::string);
};

