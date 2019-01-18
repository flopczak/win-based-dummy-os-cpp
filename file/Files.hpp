#pragma once
#include "File.hpp"
#include <vector>

class Files :
	public File
{
private:
	std::vector <File> files;
public:
	Files();
	~Files();
	bool fileExists(std::string name);
	

	void mkfile(std::string name, char data[]);
};

