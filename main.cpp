#include <iostream>
#include "process management\Process_List.hpp"
#include "process management\Process.hpp"
#include "processor\Procesor.hpp"



int main() {
	std::cout << "System start..." << std::endl;

	Process_List b_list;
	Procesor proc;
	b_list.createProcess("DUMMY", 0);
	//b_list.createProcess("PCB1", 3);
	//b_list.createProcess("PCB2", 4);
	//b_list.createProcess("PCB2", 2);
	//proc->temporary = b_list->getReady(); //TODO to musi by� w mainie �eby za ka�dym razem uzupe�nia� mape
	//TODO wgl zapytaj blazeja jak on widzi liste bo na odwrot dodajesz i usuwasz

	while (proc.work == true)
	{
		//tu jaki� b��d
		//string nazwa = b_list.getReady().front().process_name;
		//cout <<"pierwszy element listy b_list: " << nazwa << endl;




		//proc.temporary.resize(b_list.getReady().size());
		proc.temporary = b_list.getReady(); //TODO to musi by� w mainie �eby za ka�dym razem uzupe�nia� mape
		if (b_list.PrcList.front().process_priority != 0)
			b_list.PrcList.pop_front();//musi by� zeby caly czas nie uzupelniac ta sama lista
		else
			cout << "procesor zostal oddany dummy..." << endl;

		proc.add();
		proc.run();

	}


	return 0;
}