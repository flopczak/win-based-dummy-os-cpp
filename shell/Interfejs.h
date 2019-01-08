#include <iostream>
#include <vector>
#include <string>

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

	string Wczytaj() {
		string msg;
		getline(cin, msg);
	}

	vector<string> Interpret(string msg) {
		if (msg == "") {
			cout << "Blad" << endl;
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


	void Wywolaj(vector<string> tab){
		int x = tab.size();
		if (x == 0) {
			cout << "Brak elementow do wywolania" << endl;
			return;
		}
		string pocelenie = tab[0];
		vector<string> parametry;
		if (x > 1) {
			for (int i = 1; i < x; i++) {
				parametry.push_back(tab[i]);
			}
		}

		
	}

};


