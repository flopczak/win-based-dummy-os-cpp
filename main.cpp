#include <iostream>
#include <vector>
#include <string>
#include "Inklud.hpp"

//TODO zmien umiejscowienie check

int main() {
	std::cout << "System start..." << std::endl;
	Procesor proc();
	Interfejs shell(&proc);

	while (proc.work == true)
	{
		

	
		proc.run();
		proc.displayMap();

	}


	return 0;
}