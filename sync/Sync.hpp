#pragma once
#include "Process.hpp"

class Sync
{
private:
	Process::Process*currentLockProcess;
	Process::Process*currentCondProcess;
	bool lock;
	bool cond;
	std::list<Process::Process*>LockProcessQueue;//Kolejka procesow oczekujacych na zamku
	std::list<Process::Process*>CondProcessQueue;//Kolejka procesow oczekujacych na zmiennej warunkowej
public:
	Sync();
	~Sync();
	//Metody do obslugi zamkow :
	void acquire(Process::Process*);
	void release(Process::Process*);
	int  getLockID();
	bool getLock();
	std::list<Process::Process*>getLPQ();

	//Metody do obslugi zmiennych warunkowych :
	void wait(Process::Process*);
	void signal();
	void broadcast();
	int  getCondID();
	bool getCond();
	std::list<Process::Process*>getCPQ();

};

