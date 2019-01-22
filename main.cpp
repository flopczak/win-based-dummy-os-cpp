#include <iostream>
#include "../win-based-dummy-os-cpp/process management/Process_List.hpp"
#include "processor\Procesor.hpp"
#include "process management\Process.hpp"

//TODO zmien umiejscowienie check

int main() {
	std::cout << "System start..." << std::endl;

	Process_List b_list;
	Procesor proc;

	b_list.createProcess("PCB2", 4);
	b_list.createProcess("PCB3", 2);
	//proc->temporary = b_list->getReady(); //TODO to musi byæ w mainie ¿eby za ka¿dym razem uzupe³niaæ mape
	//TODO wgl zapytaj blazeja jak on widzi liste bo na odwrot dodajesz i usuwasz

	while (proc.work == true)
	{
		//tu jakiœ b³¹d
		//string nazwa = b_list.getReady().front().process_name;
		//cout <<"pierwszy element listy b_list: " << nazwa << endl;




		//proc.temporary.resize(b_list.getReady().size());
		proc.temporary = b_list.getReady(); //TODO to musi byæ w mainie ¿eby za ka¿dym razem uzupe³niaæ mape
		for (int a = 0; a < b_list.PrcList.size(); a++)											//musi byæ zeby caly czas nie uzupelniac ta sama lista
		{
			if (b_list.PrcList.front().process_priority = !0)
			{
				b_list.PrcList.pop_front();
			}
		}


		proc.add();
		proc.run();
		proc.displayMap();

	}


	return 0;
}