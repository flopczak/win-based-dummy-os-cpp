#include <iostream>
#include <vector>
#include <string>
#include "process management/Process.hpp"
#include "process management/Process_List.hpp"

#include "processor/Procesor.hpp"

//TODO zmien umiejscowienie check

int main() {
	std::cout << "System start..." << std::endl;
	Procesor proc;
	Assembler asm;

	while (proc.work == true)
	{
		

	
		proc.run();
		proc.displayMap();

	}


	return 0;
}