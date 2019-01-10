#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <cstdlib>

using namespace std;

class Interfejs {
private:
	struct his {
		int numer_metody;
		string parametr;
	};
	struct met {
		string skrot;
		string opis;
	};
	const bool dislog = true;
	vector<met> metody;
public:
	vector<his> historia;

	void DisplayLog(string msg) {
		if (dislog) {
			cout << msg << endl;
		}
	}

	void DisplayMethods() {
		cout << "Metody dostepne dla uzytkownika: " << endl;
		int x = metody.size();
		if (x == 0) {
			cout << "Brak metod dla uzytkownika" << endl;
			return;
		}
		for (int i = 0; i < x; i++) {
			cout << i + 1 << ". " << metody[i].opis << endl;
		}
	}
	void DisplayHistory() {
		int x = historia.size();
		if (x == 0) {
			cout << "Historia jest pusta" << endl;
			return;
		}
		for (int i = x - 1; i<-1; i--) {
			cout << i + 1 << ". " << metody[historia[i].numer_metody].opis << " " << historia[i].parametr << endl;
		}
	}
	void DisplayHistory(int y) {
		int x = historia.size();
		if (y > x) {
			cout << "Historia nie posiada tylu elementów" << endl;
			return;
		}
		for (int i = x - 1; i<-1; i--) {
			cout << i + 1 << ". " << metody[historia[i].numer_metody].opis << " " << historia[i].parametr << endl;
		}

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
			cout << napis << endl;
			x = napis.length;
			string temp = "";
			bool koniec = false;
			string delimiter = " ";
			string token = napis.substr(0, napis.find(delimiter));
			metody[i].skrot = token;
			metody[i].opis = napis;
			i++;
		}
	}
	void SetColor(vector<string> tab) {
		if (tab.size() > 1) {
			cout << "za duzo parametrow" << endl;
			return;
		}
		string kolor = tab[0];
		switch (kolor) {
		case red:
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			break;
		case blue:
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			break;
		case green:
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			break;
		case default:
			cout << "nie ma takiego koloru" << endl;
			break;
		}
	}

	string Wczytaj() {
		string msg;
		getline(cin, msg);
		return msg;
	}

	void cls() {
		System("cls");
	}

	vector<string> Interpret(string msg) {
		if (msg == "") {
			cout << "Blad, pusta wiadomosc" << endl;
			return;
		}
		vector<string> tabmsg;
		//spacja ma kod ASCII 32
		string temp = "";
		int x = msg.length;
		for (int i = 0; i < x; i++) {
			if (msg[i] != 32) {
				temp = temp + msg[i];
			}
			if (msg[i] == 32) {
				tabmsg.push_back(temp);
				temp = "";
			}
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
		printf("Czas lokalny: %s\n", ctime(&czas));
	}

	string ToUp(string s) {
		setlocale(LC_CTYPE, "pl_PL.UTF-8");
		for (int i = 0; i < s.length(); i++)
		{
			s[i] = toupper(s[i]);
		}
		return s;
	}

	string ToDown(string s) {
		for (int i = 0; i < s.length(); i++)
		{
			s[i] = toupper(s[i]);
		}
		return s;
	}


	void Wywolaj(vector<string> tab){
		int x = tab.size();
		if (x == 0) {
			cout << "Brak elementow do wywolania" << endl;
			return;
		}
		string pocelenie = tab[0];
		polecenie = ToDown(polecenie);
		vector<string> parametry;
		if (x > 1) {
			for (int i = 1; i < x; i++) {
				parametry.push_back(tab[i]);
			}
		}
		
		switch (polecenie) {
		case time:
			Time();
			break;
		case xyz:
			break;
		case exit:
			break;
		case mkdir:
			break;
		case rmdir:
			break;
		case sp:
			break;
		case cp:
			break;
		case cls:
			cls();
			break;
		case help:
			DisplayMethods();
			break;
		case of:
			break;
		case clf:
			break;
		case ren:
			break;
		case exit:
			break;
		case default:
			cout << "Nie ma takiego polecenia" << endl;
			break;
		}

		
	}

};


