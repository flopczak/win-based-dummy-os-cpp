#pragma once
#include "Procesor.hpp"

class Sync
{
private:
	Procesor::Process*currentLockProcess;
	Procesor::Process*currentCondProcess;
	bool lock;
	bool cond;
	std::list<Procesor::Process*>LockProcessQueue;//Kolejka procesow oczekujacych na zamku
	std::list<Procesor::Process*>CondProcessQueue;//Kolejka procesow oczekujacych na zmiennej warunkowej
public:
	Sync();
	~Sync();
	//Metody do obslugi zamkow :
	void acquire(Procesor::Process*);
	void release(Procesor::Process*);
	int  getLockID();
	bool getLock();
	std::list<Procesor::Process*>getLPQ();

	//Metody do obslugi zmiennych warunkowych :
	void wait(Procesor::Process*);
	void signal();
	void broadcast();
	int  getCondID();
	bool getCond();
	std::list<Procesor::Process*>getCPQ();

};

