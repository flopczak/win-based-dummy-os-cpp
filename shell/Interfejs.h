#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include "../Inklud.hpp"


using namespace std;



class Interfejs {
private:
	Procesor *proc;
	Assembler *assembler;
	Disk *dysk;
	Memory *mem;
	User *user;
	Acl *acl;
	Process_List *PL;
public:
	
	struct met {
		string skrot;
		string opis;
	};
	vector<met> metody;
	vector<string> kroki;

	Interfejs(Procesor *proc, Assembler *assembler, Disk *dysk, Memory *mem, User *user, Acl *acl, Process_List *PL) {
		this->proc = proc;
		this->mem = mem;
		this->acl = acl;
		this->assembler = assembler;
		this->dysk = dysk;
		this->user = user;
		this->PL = PL;
	}

	void DisplayLog(string msg) {
		kroki.push_back(msg);
	}

	/*void Wyswietl() {
		int ilosc=0;
		for (int i = 0; i < kroki.size(); i++) {
			cout << kroki[i] << endl;
			ilosc++;
		}
		kroki.erase(kroki.begin(), kroki.begin()+ilosc);
		cout << "Nacisnij dowolny klawisz aby kontynuowac..." << endl;
		cin.get();
	}*/

	void ChangeDisLog(vector<string> abc) {
		if (abc.size() > 2) {
			cout << "Za duzo parametrow, dostepne parametry to:\ntrue\nfalse" << endl;
		}
		string bulin = abc[0];
		if (bulin == "true") {
			//dislog = true;
			//DisplayLog("zmienilem wartosc dislog");
		}
		else if (bulin == "false") {
			//dislog = false;
		}
		else {
			cout << "Bledny parametr, dostepne parametry to:\ntrue\nfalse" << endl;
		}
	}

	void DisplayMethods() {
		cout << "Metody dostepne dla uzytkownika:\n------------------------------- " << endl;
		int x = metody.size();
		if (x == 0) {
			cout << "Brak metod dla uzytkownika" << endl;
			return;
		}
		for (int i = 0; i < x; i++) {
			cout << i + 1 << ". " << ToUp(metody[i].skrot) << " " << metody[i].opis << endl;
		}
		cout << endl;
	}

	void ZgrajZTxt() {
		ifstream plik;
		plik.open("metody.txt");
		if (!plik.good()) {
			cout << "blad odczytu pliku" << endl;
			return;
		}
		int i = 0;
		string napis;
		int x;
		while (!plik.eof()) {
			getline(plik, napis);
			x = napis.size();
			string delimiter = " ";
			string token = napis.substr(0, napis.find(delimiter));
			met temp;
			temp.skrot = token;
			int a = token.size();
			napis.erase(0, a + 1);
			temp.opis = napis;
			metody.push_back(temp);
			i++;
		}
	}
	void SetColor(vector<string> tab) {
		if (tab.size() > 2) {
			cout << "za duzo parametrow" << endl;
			return;
		}
		string color = tab[1];
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		string kolor = tab[0];
		int colour = stoi(color);
		if (colour >= 0 && colour < 16) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
		}
		else {
			cout << "Nie ma takiego koloru.\n Dostepne kolory to green blue red white oraz liczby 0-15 " << endl;
		}
	}

	string Wczytaj() {
		string msg;
		getline(cin, msg);
		return msg;
	}

	void cls() {
		system("cls");
	}

	void silnia(int x) {
		int wynik = 1;
		string str;
		for (int i = 1; i < x + 1; i++) {
			wynik *= i;
			str = to_string(wynik);
			DisplayLog(str);
		}
	}

	vector<string> Interpret(string msg) {
		if (msg == "") {
			cout << "Blad, pusta wiadomosc" << endl;
			vector<string> pusty;
			return pusty;
		}
		vector<string> tabmsg;
		//spacja ma kod ASCII 32
		string temp = "";
		int x = msg.size();
		for (int i = 0; i < x; i++) {
			if (msg[i] != 32) {
				temp = temp + msg[i];
			}
			if (msg[i] == 32) {
				tabmsg.push_back(temp);
				temp = "";
			}
		}
		if (temp != "") {
			tabmsg.push_back(temp);
		}
		string polecenie = tabmsg[0];
		x = tabmsg.size();
		if (x > 1) {
			for (int i = 1; i < x; i++) {
				tabmsg.push_back(tabmsg[i]);
			}
		}
		return tabmsg;
	}

	void Time() {
		time_t czas;
		time(&czas);
		czas = czas % 86400;
		int h, m, s;
		h = czas / 3600;
		czas = czas - h * 3600;
		m = czas / 60;
		czas = czas - m * 60;
		s = czas;
		cout << h + 1 << ":" << m << ":" << s << endl;
	}

	string ToUp(string s) {
		setlocale(LC_CTYPE, "pl_PL.UTF-8");
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = toupper(s[i]);
		}
		return s;
	}

	string ToDown(string s) {
		for (int i = 0; i < s.size(); i++)
		{
			s[i] = tolower(s[i]);
		}
		return s;
	}


	void Wywolaj(vector<string> tab)
	{
		int x = tab.size();
		if (x == 0) {
			cout << "Brak elementow do wywolania" << endl;
			return;
		}
		string polecenie = tab[0];
		polecenie = ToUp(polecenie);
		vector<string> parametry;
		if (x > 1) {
			for (int i = 1; i < x; i++) {
				parametry.push_back(tab[i]);
				parametry[i - 1] = ToDown(parametry[i - 1]);
			}
		}
		if (polecenie == "HELP") {
			DisplayMethods();
			return;
		}
		else if (polecenie == "GO") {
			return;
		}
		else if (polecenie == "COLOR") {
			SetColor(parametry);
			return;
		}
		else if (polecenie == "TK") {
			this->PL->findAndDisplayProcess(parametry);
			return;
		}
		else if (polecenie == "TKL") {
			this->PL->displayAll();
			return;
		}
		else if (polecenie == "TKK") {
			this->PL->terminateProcess(parametry);
		}
		else if (polecenie == "SS") {
			this->PL->setStatus(parametry);
			return;
		}
		else if (polecenie == "EXIT") {
			cin.get();
			exit(0);
		}
		else if (polecenie == "CLS") {
			cls();
			return;
		}
		else if (polecenie == "CU") {
			this->user->createUser();
			return;
		}
		else if (polecenie == "PCL") {
			this->user->printCurrentLoggedUser();
			return;
		}
		else if (polecenie == "LOG") {
			this->user->logIn();
			return;
		}
		else if (polecenie == "DU") {
			this->user->deleteUser(parametry);
			return;
		}
		else if (polecenie == "VUL") {
			this->user->viewUserList();
			return;
		}
		else if (polecenie == "VSUG") {
			this->user->viewStandardUserGroup();
			return;
		}
		else if (polecenie == "VAUG") {
			this->user->viewAdminUserGroup();
			return;
		}
		else if (polecenie == "AUTS") {
			this->user->addUserToStandardUserGroup(parametry);
			return;
		}
		else if (polecenie == "AUTA") {
			this->user->addUserToAdminGroup(parametry);
			return;
		}
		else if (polecenie == "VAL") {
			this->acl->viewAclList();
			return;
		}
		else if (polecenie == "VFA") {
			this->acl->viewFileAcl(parametry);
			return;
		}
		else if (polecenie == "SAP") {
			this->acl->setAdditionalPermissions(parametry);
			return;
		}
		else if (polecenie == "WZP") {
			this->memory->WypiszZasobPamieci();
			return;
		}
		else if (polecenie == "WF") {
			this->memory->WydrukujFIFO();
			return; 
		}
		/*else if (polecenie == "DD" && parametry.size()==0) {
			dysk.dodajDane();
			return;
		}*/
		else if (polecenie == "PB") {
			this->dysk->pobierzBlok(parametry);
			return;
		}
		else if (polecenie == "DD") {
			this->dysk->dodajDane(parametry);
			return;
		}
		else if (polecenie == "DP") {
			this->dysk->dodajPlik(parametry);
			return;
		}
		else if (polecenie == "WB") {
			this->dysk->wypiszBlok(parametry);
			return;
		}
		else if (polecenie == "WD") {
			this->dysk->wypiszDysk();
			return;
		}
		else if (polecenie == "WP") {
		this->dysk->wypiszPlik(parametry);
			return;
		}
		else if (polecenie == "DDP") {
		this->dysk->dopiszDoPliku(parametry);
			return;
		}
		else if (polecenie == "UP") {
		this->dysk->usunPlik(parametry);
			return;
		}
		else if (polecenie == "NP") {
		this->dysk->nadpiszPlik(parametry);
			return;
		}
		else if (polecenie == "WBI") {
		this->dysk->wypiszBlokIndeksowy();
			return;
		}
		else if (polecenie == "WK") {
			this->dysk->wypiszKatalog();
			return;
		}
		else if (polecenie == "FRMT") {
			this->dysk->formatuj();
			return;
		}
		else if (polecenie == "WPP") {
			this->proc->ramka();
			return;
		}
		else if (polecenie == "CP") {
			cout << "stworzylem proces" << endl;
			this->PL->createProcess(parametry);
			return;
		}
		else if (polecenie == "SP") {
			cout << "ustawilem priorytet" << endl;
			this->PL->setPriority(parametry);
			return;
		}
		else if (polecenie == "TIME") {
			Time();
			return;
		}
		else if (polecenie == "CHD") {
			ChangeDisLog(parametry);
			return;
		}
		else {
			DisplayMethods();
			return;
		}
	}
};

