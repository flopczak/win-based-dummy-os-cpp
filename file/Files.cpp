#include "Files.hpp"



Files::Files()
{
	this->files = std::vector<File>();
}


Files::~Files()
{
}

bool Files::fileExists(std::string name)
{
	{
		std::istringstream f(name);
		std::string temp;
		std::getline(f, temp, '.');
		for (File e : files) {
			if (e.getName() == temp)
			{
				return true;
			}
		}
		return false;
	}
}

void Files::mkfile(std::string name, char data[])
{
	if (name.length() == 0)
	{
		Interfejs.DisplayLog("Podano nieprawidlowa nazwe pliku")
	}
	if (fileExists(name))
	{
		Interfejs.DisplayLog("Plik o podanej nazwie juz istnieje");
	}
	File newf = File(name);
	newF.setIndexBlock();
	newF.setSize(sizeof(data));
	files.push_back(newf);
	Interfejs.DisplayLog("Stworzono nowy plik o nazwie: " + name);

}
