#pragma once
class Sync
{
private:
	bool lock;
	bool cond;
	std::list<PCB*>LockProcessQueue;//Kolejka procesow oczekujacych na zamku
	std::list<PCB*>CondProcessQueue;//Kolejka procesow oczekujacych na zmiennej warunkowej
public:
	Sync();
	~Sync();
	//Metody do obslugi zamkow :
	void acquire(PCB*);
	void release(PCB*);
	int  getLockID();
	bool getLock();
	std::list<PCB*>getLPQ();

	//Metody do obslugi zmiennych warunkowych :
	void wait(PCB*);
	void signal();
	void broadcast();
	int  getCondID();
	bool getCond();
	std::list<PCB*>getCPQ();

};

