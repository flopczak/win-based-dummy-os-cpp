#include "Sync.hpp"

//=====================================================================================================// Konstruktor / Destruktor
Sync::Sync()
{
	this->lock=false;
	this->cond=false;
}

Sync::~Sync()
{

}

void Sync::lockFile(std::string nazwa, Process* tempP)
{
	if (Sync::zamkiNaPlikach.find(nazwa) == Sync::zamkiNaPlikach.end())
	{
		Sync tempS;
		Sync::zamkiNaPlikach[nazwa] = tempS;//dodanie nowego zamka do mapy
		Sync::zamkiNaPlikach[nazwa].acquire(tempP);// zajecie zamka 
	}
	else
	{
		Sync::zamkiNaPlikach[nazwa].acquire(tempP);
	}
}

void Sync::unlockFile(std::string nazwa, Process* tempP)
{
	Sync::zamkiNaPlikach[nazwa].release(tempP);//zwolnienie odpowiedniego zamku
}


//=====================================================================================================// Metody dla Lock

void Sync::acquire(Process*tempProcess)
{
	if (this->lock == true) 
	{
		tempProcess->setProcessStatus(OCZEKUJACY); // Process do stanu waiting. 
		LockProcessQueue.push_back(tempProcess);
	}

	else if (this->lock == false) 
	{
		this->lock = true;
		this->currentLockProcess = tempProcess;
		/*
		tempProcess->setProcessStatus("AKTYWNY"); //Process do stanu wykonywania.
		lub
		*/
		this->currentLockProcess->setProcessStatus(GOTOWY); //Process do stanu ready.  // raczej to
		//i po tym planista?
	}
}

void Sync::release(Process*tempProcess)
{
	if (this->getLockID() == tempProcess->getPID())	
	{
		if (LockProcessQueue.empty() == true)
		{ 
			this->lock = false; 
			this->currentLockProcess->setProcessStatus(GOTOWY); //Process do stanu ready.
		}

		else 
		{
			this->currentLockProcess->setProcessStatus(GOTOWY); //Process do stanu ready.
			this->currentLockProcess = LockProcessQueue.front();
			LockProcessQueue.pop_front();
			/*
			tempProcess->setProcessStatus("AKTYWNY"); //Process do stanu wykonywania.
			lub
			*/
			this->currentLockProcess->setProcessStatus(GOTOWY); //Process do stanu ready.  // raczej to 
			//i po tym planista?
			
		}
	}
	else
	{
		this->currentLockProcess.setProcessStatus(ZAKONCZONY); //Process do stanu terminated.
	}

}

int Sync::getLockID()
{
	return this->currentLockProcess->getPID();
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
//Cond jeszcze do kalibracji

int Sync::getCondID()
{
	return this->currentCondProcess->getPID();
}

bool Sync::getCond()
{
	return this->cond;
}

std::list<Process::Process*> Sync::getCPQ()
{
	return this->CondProcessQueue;
}


void Sync::wait(Process *tempProcess)
{
	if (this->cond == false)
	{
		tempProcess->setProcessStatus(OCZEKUJACY); // Process do stanu waiting. (+ Planista?)
		this->cond = true;
		this->currentCondProcess = tempProcess;
	}

	else if (this->cond == true)
	{
		tempProcess->setProcessStatus(OCZEKUJACY); // Process do stanu waiting. ( + Planista?)
		CondProcessQueue.push_back(tempProcess);
	}
}

void Sync::signal()
{
	if (this->cond == true && CondProcessQueue.empty() == false)
	{
		this->CondProcessQueue.front()->setProcessStatus(GOTOWY);// 1 z kolejki GOTOWY

		this->CondProcessQueue.pop_front();// Wywalamy 1 z kolejki

		if (CondProcessQueue.empty() == true)
		{
			this->cond = false;
			this->currentCondProcess->setProcessStatus(GOTOWY);// Proces ktory dal wait dajemy do stanu ready
		}
		else
		{
			this->cond = true;
		}
	}

	else
	{
		this->cond = false;
		this->currentCondProcess->setProcessStatus(GOTOWY);// Proces ktory dal wait dajemy do stanu ready
	}

}