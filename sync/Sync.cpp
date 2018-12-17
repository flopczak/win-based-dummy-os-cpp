#include "Sync.hpp"
#include "Procesor.hpp"


Sync::Sync()
{
	this->lock=false;
	this->cond=false;
}


Sync::~Sync()
{
}

void acquire(Procesor::Process*tempProcess)
{
	if (this->lock == true) 
	{
		tempProcess->setProcessStatus("OCZEKUJACY"); // Process do stanu waiting. 
		LockProcessQueue.push_back(tempProcess);
	}
	else if (this->lock == false) 
	{
		this->lock = true;
		this->currentLockProcess->setPID(tempProcess->pID);
		this->currentLockProcess = tempProcess;
	}

}

void release(Procesor::Process*tempProcess)
{
	if (this->getLockID() == tempProcess->pID)	
	{
		if (LockProcessQueue.empty() == true)
		{ 
			this->lock = false; 
		}

		else 
		{
			this->currentLockProcess = LockProcessQueue.front();
			LockProcessQueue.pop_front();
			this->currentLockProcess->setProcessStatus("GOTOWY") //Process do stanu ready.
			this->currentLockProcess->setPID(tempProcess->getPID()); // setPID() potrzebne!! @Blazej
		}
	}
	else this->synchProces.setProcessStatus("ZAKONCZONY"); //Process do stanu terminated.
	

}

int getLockID()
{
	return this->currentLockProcess->getPID(); // getPID() potrzebne!! @Blazej
}

bool getLock()
{
	return this->lock;
}