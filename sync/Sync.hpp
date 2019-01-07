#pragma once
#include "Process.hpp"

// getPID() potrzebne!! @Blazej

class Sync
{
private:
	Process*currentLockProcess;
	Process*currentCondProcess;
	bool lock;
	bool cond;
	std::list<Process*>LockProcessQueue;//Kolejka procesow oczekujacych na zamku
	std::list<Process*>CondProcessQueue;//Kolejka procesow oczekujacych na zmiennej warunkowej
public:
	Sync();
	~Sync();
	//Metody do obslugi zamkow :
	void acquire(Process*);
	void release(Process*);
	int  getLockID();
	bool getLock();
	std::list<Process*>getLPQ();

	//Metody do obslugi zmiennych warunkowych :
	void wait(Process*);
	void signal();
	void broadcast();
	int  getCondID();
	bool getCond();
	std::list<Process*>getCPQ();

};

