#include <iostream>
#include <vector>
#include <string>
#include "process management/Process.hpp"
#include "process management/Process_List.hpp"
#include "processor/Procesor.hpp"

//TODO zmien umiejscowienie check

int main() {
	std::cout << "System start..." << std::endl;

	Process_List b_list;
	Procesor proc;
	vector<string>p1;
	p1.push_back("PCB2");
	p1.push_back("4");
	vector<string>p2;
	p2.push_back("PCB3");
	p2.push_back("2");
	vector<string>v3;
	b_list.terminateProcess(v3);

	b_list.createProcess(p1);
	b_list.createProcess(p2);
	//proc->temporary = b_list->getReady(); //TODO to musi byæ w mainie ¿eby za ka¿dym razem uzupe³niaæ mape
	//TODO wgl zapytaj blazeja jak on widzi liste bo na odwrot dodajesz i usuwasz

	while (proc.work == true)
	{
		//tu jakiœ b³¹d
		//string nazwa = b_list.getReady().front().process_name;
		//cout <<"pierwszy element listy b_list: " << nazwa << endl;




		//proc.temporary.resize(b_list.getReady().size());
		//proc.temporary = b_list.getReady(); //TODO to musi byæ w mainie ¿eby za ka¿dym razem uzupe³niaæ mape
		/*
		for (int a = 0; a < b_list.PrcList.size(); a++)											//musi byæ zeby caly czas nie uzupelniac ta sama lista
		{
			if (b_list.PrcList.front().process_priority = !0)
			{
				b_list.PrcList.pop_front();
			}
		}
		*/

	
		proc.run();
		proc.displayMap();

	}


	return 0;
}