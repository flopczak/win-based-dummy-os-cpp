#include <iostream>
#include <vector>
#include <string>
#include "Inklud.hpp"
#include "shell\Interfejs.h"

//TODO zmien umiejscowienie check

int main() {
	std::cout << "System start..." << std::endl;
	User user();
	Acl acl();
	Disk dysk = Disk();
	Process_List PL();
	Sync sync();
	Memory memory;
	Assembler assem(&memory, &dysk, &PL);
	Procesor proc(&assem, &memory, &dysk);
	Interfejs shell(&memory, &PL, &user, &acl, &dysk, &proc, &sync);

	while (proc.work == true)
	{
		

	
		proc.run();
		proc.displayMap();

	}


	return 0;
}