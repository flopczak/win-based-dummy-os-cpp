#pragma once
#include"../process management/Process.hpp"
#include <list>
#include <map>
#include <string>


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
	static map<string, Sync> zamkiNaPlikach;
	Sync();
	~Sync();
	static void lockFile(string, Process*);
	static void unlockFile(string, Process*);
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

