#include "Sync.hpp"
#include "Process.hpp"

//=====================================================================================================// Konstruktor / Destruktor
Sync::Sync()
{
	this->lock=false;
	this->cond=false;
}

Sync::~Sync()
{

}
//=====================================================================================================// Metody dla Lock

void Sync::acquire(Process::Process*tempProcess)
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

void Sync::release(Process::Process*tempProcess)
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

int Sync::getLockID()
{
	return this->currentLockProcess->getPID(); // getPID() potrzebne!! @Blazej
}

bool Sync::getLock()
{
	return this->lock;
}

std::list<Process::Process*> Sync::getLPQ()
{
	return this->LockProcessQueue;
}

//=====================================================================================================// Metody dla Cond

int Sync::getCondID()
{
	return this->currentCondProcess->getPID(); // getPID() potrzebne!! @Blazej
}

bool Sync::getCond()
{
	return this->cond;
}

std::list<Process::Process*> Sync::getCPQ()
{
	return this->CondProcessQueue;
}