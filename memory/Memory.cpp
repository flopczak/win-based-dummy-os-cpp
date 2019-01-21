#include "Memory.h"

void Memory::PrzeStroPWymDoPam(Process * pcb, int nr) {

	STRON * TabStron = pcb->PobTabStronic();
	ZapewnijWolnaRame(); //sprawiamy, ze na pewno pojawi sie wolna ramka pamieci

	int NowoZajRama = PobierzWolRamePamieci();
	int NowoWolnaRamaPWym = TabStron[nr].RamaZajeta; //zmiana stronicy z SF do RAM
	WolneRamkiPlikuWymiany.push_front(NowoWolnaRamaPWym);
	PrzeZawPWymDoPam(NowoWolnaRamaPWym, NowoZajRama); //ustawiamy indeks aktualnej strony w RAM

	TabStron[nr].RamaZajeta = NowoZajRama; //nowa ramka w RAM
	TabStron[nr].wPam = true; //strona jest w RAM

	DodajDoFifo(FIFO_entry(pcb, nr)); //dodanie procesu do FIFO
}
//
void Memory::PrzeStroPamDoPWym(Process * pcb, int nr) {
	STRON * TabStron = pcb->PobTabStronic();

	if (WolneRamkiPlikuWymiany.empty()) //jezeli brak wolnych ramek w pliku wymiany, to mamy problem
	{
		pcb->errorCode = static_cast<int>(BledyPam::OUT_OF_MEM); // nie powinno nigdy sie stac
		return;
	}

	int NowaWolnaRama = TabStron[nr].RamaZajeta; //jezeli trafimy na strone w pamieci RAM to wysylamy ja do pliku wymiany
	WolneRamki.push_back(NowaWolnaRama); //wolna ramke ram dodajemy do listy wolnych ramek

	int NowoZajetaRamaPWym = PobierzWolnaRamePWym();

	PrzeZawPamDoPWym(NowaWolnaRama, NowoZajetaRamaPWym); //przenosimy strone

	TabStron[nr].RamaZajeta = NowoZajetaRamaPWym; //nowa ramka w SwapFile
	TabStron[nr].wPam = false; //strona nie jest w RAM
}
//
void Memory::PrzeZawPamDoPWym(int RamaPam, int RamaPWy) {
	int IndeksPWym = RamaPWy * WIE_RAM;
	int IndeksPam = RamaPam * WIE_RAM;
	int IndeksKPWym = IndeksPWym + WIE_RAM;
	int IndeksKPam = IndeksPam + WIE_RAM;

	while (IndeksPam < IndeksKPam && IndeksPWym < IndeksKPWym)
	{
		PlikWymiany[IndeksPWym] = RAM[IndeksPam];
		RAM[IndeksPam] = ' ';
		IndeksPam++;
		IndeksPWym++;
	}
}
//
void Memory::PrzeZawPWymDoPam(int RamaPWy, int RamaPam) {
	int IndeksPWym = RamaPWy * WIE_RAM;
	int IndeksPam = RamaPam * WIE_RAM;
	int IndeksKPWym = IndeksPWym + WIE_RAM;
	int IndeksKPam = IndeksPam + WIE_RAM;

	while (IndeksPam < IndeksKPam && IndeksPWym < IndeksKPWym)
	{
		RAM[IndeksPam] = PlikWymiany[IndeksPWym];
		PlikWymiany[IndeksPWym] = ' ';
		IndeksPam++;
		IndeksPWym++;
	}
}
//
void Memory::ZapiszDoPlikuWym(int nr, string Zaw) {
	int IndeksPWym = nr * WIE_RAM;
	int IndeksStringa = 0;

	while (IndeksStringa < Zaw.size())
	{
		PlikWymiany[IndeksPWym] = Zaw[IndeksStringa];
		IndeksPWym++;
		IndeksStringa++;
	}
}
//
int Memory::ObliczOffset(int addr1) {
	return addr1 % WIE_RAM;
}
//
int Memory::ObliczNumerStrony(int addr1) {
	return addr1 / WIE_RAM;
}
//
int Memory::ObliczAdresFizyczny(Process * pcb, int addr1) {
	STRON * TablicaStronic = pcb->PobTabStronic();
	int NumerStrony = ObliczNumerStrony(addr1);
	int offset = ObliczOffset(addr1);
	int NumerRamy = TablicaStronic[NumerStrony].RamaZajeta;
	return NumerRamy * WIE_RAM + offset;
}
//
int Memory::ObliczTabliceStronic(int siBytes) {
	double wielkoscRamy = static_cast<double>(WIE_RAM);
	double CalkowitaWielkosc = static_cast<double>(siBytes);
	double wynik = ceil(CalkowitaWielkosc/ wielkoscRamy);
	return static_cast<int>(wynik);
}
//
char Memory::OdczytajZPamieci(Process * pcb, int addr1) {
	if (BrakMieWPowAdr(pcb, addr1)) {
		pcb->errorCode = static_cast<int>(BledyPam::OUT_OF_RANGE);
		return ' ';
	}
	ZapewnijStroneWPamieci(pcb, addr1);
	int AddrP = ObliczAdresFizyczny(pcb, addr1);
	return RAM[AddrP];
}
//
void Memory::ZapiszWPamieci(Process * pcb, int addr1, char element) {
	if (BrakMieWPowAdr(pcb, addr1)) {
		pcb->errorCode = static_cast<int>(BledyPam::OUT_OF_RANGE);
		return ;
	}
	ZapewnijStroneWPamieci(pcb, addr1);
	int p_Addr = ObliczAdresFizyczny(pcb, addr1);
	RAM[p_Addr] = element;
}
//
void Memory::ZapewnijStroneWPamieci(Process * pcb, int AdresLogiczny) {
	STRON * TabelaStron = pcb->PobTabStronic();

	int NumerPam = ObliczTabliceStronic(AdresLogiczny);

	if (TabelaStron[NumerPam].wPam == false) {
		PrzeStroPWymDoPam(pcb, NumerPam);
	}
}
//
int Memory::PobierzWolnaRamePWym() {
	int WolnaRama = WolneRamkiPlikuWymiany.front();
	WolneRamkiPlikuWymiany.pop_front();
	return WolnaRama;
}
//
int Memory::PobierzWolRamePamieci() {
	int WolnaRama = WolneRamki.front();
	WolneRamki.pop_front();
	return WolnaRama;
}
//
void Memory::ZapewnijWolnaRame() {
	while (WolneRamki.empty())
	{
		//nie ma wolnych ramek wiec usuwamy metoda FIFO najstarszy Process
		FIFO_entry victim = FIFO.front();
		FIFO.pop_front();
		PrzeStroPamDoPWym(victim.pcb, victim.pageNumber);
	}
}
//
void Memory::DodajDoFifo(FIFO_entry entry) {
	FIFO.push_back(entry);
}
//
bool Memory::BrakMieWPowAdr(Process * pcb, int AdresLogiczny) {
	int NumerStrony = ObliczNumerStrony(AdresLogiczny);
	if (NumerStrony >= pcb->PobWielTabStronic())
		return true;
	else
		return false;
}
//
void Memory::PrzydzialPamieci(Process * pcb, string proces, int size) {
	//ilosc stronic potrzebynch do alokacji
	int WieTabStron = ObliczTabliceStronic(size);
	STRON * TablicaStron = new STRON[WieTabStron];
	int PoczatekStr = 0;

	for (int NrStr = 0; NrStr < WieTabStron; WieTabStron++) {
		//jezeli plik wymiany jest pelny
		if (WolneRamkiPlikuWymiany.empty())
		{
			pcb->errorCode = static_cast<int>(BledyPam::OUT_OF_MEM);;//blad, nie da sie zaalokowac
			return;
		}
		int NowoZajetaRamaPWym = PobierzWolnaRamePWym();

		TablicaStron[NrStr].RamaZajeta = NowoZajetaRamaPWym;
		TablicaStron[NrStr].wPam = false;

		string pageContent = proces.substr(PoczatekStr, WieTabStron);
		proces.erase(PoczatekStr, WIE_RAM);
		WpiszZasobPamDoPWym(NowoZajetaRamaPWym, pageContent);
	}

	pcb->UstTabStronic(TablicaStron);
	pcb->UstWielTabStronic(WieTabStron);
}

string Memory::odczytajString(Process * pcb, int Addr) {
	int WielkoscTablicyStron = pcb->PobWielTabStronic();
	string result = "";
	char byte;
	int LimitAddr = WielkoscTablicyStron * WIE_RAM;
	//powtarzej dopoki adres logiczny nie wskazuje na ' ' i nie przekroczyl logicznej pamieci
	while (Addr < LimitAddr)
	{
		byte = OdczytajZPamieci(pcb, Addr);
		if (byte == ' ')
			break;
		result += byte;
		Addr++;
	}
	return result;
}
//
void Memory::zapiszString(Process * pcb, int Addr, string Zaw) {
	for (int IndeksZaw = 0; IndeksZaw < Zaw.size(); IndeksZaw++)
	{
		ZapiszWPamieci(pcb, Addr + IndeksZaw, Zaw[IndeksZaw]);
	}
}
//
void Memory::WypiszZasobPamieci(int DoWypis) {
	if (DoWypis <= 0 || DoWypis > ILOSC_RAM)
		DoWypis = ILOSC_RAM;

	for (int i = 0; i < DoWypis; i++)
	{
		WydrukujRame(i);
	}
}
//
void Memory::WpiszZasobPamDoPWym(int nr, string zasobPam)
{
	int IndeksPlikuWym = nr * WIE_RAM;
	int IndeksSTR = 0;

	while (IndeksSTR < zasobPam.size())
	{
		PlikWymiany[IndeksPlikuWym] = PlikWymiany[IndeksPlikuWym];
		IndeksPlikuWym++;
		IndeksSTR++;
	}
}
void Memory::WydrukujProcesy(Process * pcb, bool wRamie) {

	if (pcb == nullptr)
	{
		cout << "Nie ma takiego procesu.\n";
		return;
	}

	STRON * StronProc = pcb->PobTabStronic();
	int WieStronProc = pcb->PobWielTabStronic();

	cout << " --- Pamiec zarezerwowana przez proces: " << pcb->GetPID() << " ---\n";
	for (int i = 0; i < WieStronProc; i++)
	{
		if (StronProc[i].wPam)
		{
			WydrukujRame(StronProc[i].RamaZajeta, i); //Jezeli strona znajduje sie w pamieci
		}
		else if (!wRamie) //jezeli nie chcemy wypisywac ramek w SF
		{
			WydrukujRamePWym(StronProc[i].RamaZajeta, i); //Jezeli strona znajduje sie w SF
		}
	}
}
//
void Memory::WydrukujFIFO() {
	cout << "Stan algorytmu FIFO. Element po lewej zostanie usuniety, w przypadku braku miejsca w pamieci." << endl
		<< "Format: [{PID_procesu},{numer strony}]" << endl;
	for (auto entry : FIFO)
	{
		cout << "[" << entry.pcb->GetPID() << "," << entry.pageNumber << "] ";
	}
	cout << endl;
}
//
bool Memory::CzyAdrWPowAdresss(Process * pcb, int AddrLog) {
	int NrStrony = ObliczNumerStrony(AddrLog);
	if (NrStrony < pcb->PobWielTabStronic())
		return true;
	else
		return false;
}
//
bool Memory::CzyZasiegAdrWPowAdres(Process * pcb, int AddrLog, int zasieg) {
	int AddrKon = zasieg + AddrLog;
	while (AddrLog < AddrKon)
	{
		if (CzyAdrWPowAdresss(pcb, AddrLog))
			return false;
		AddrLog++;
	}
	return true;
}
//
void Memory::WydrukujRamePWym(int RamaNr, int StronaNr) {
	int addr = RamaNr * WIE_RAM;
	string space = "        ";
	cout << "Ramka pliku wymiany nr: " << RamaNr;
	if (StronaNr >= 0)
	{
		cout << ", zawiera strone nr: " << StronaNr;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyzwietla gore ramki
	cout << space << (char)CharTable::CTL;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::HLB;
	}
	for (int j = 0; j < 5; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::CTR << endl;
	// ----------------------------------------------------------------------
	// wyzwietla indeksy RAM
	cout << space << (char)CharTable::VL;
	for (int i = 0; i < WIE_RAM; i++)
	{
		if (addr + i < 10)
			printf("  %d  ", addr + i);
		else if (addr + i < 100)
			printf("  %d ", addr + i);
		else if (addr + i < 1000)
			printf(" %d ", addr + i);
		else
			printf("%5d", addr + i);
		cout << (char)CharTable::VL;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyswietla srodek ramki
	cout << space << (char)CharTable::VLR;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::Cross;
	}
	for (int j = 0; j < 5; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::VLL << endl;
	// ----------------------------------------------------------------------
	// wyswietla zawartosc RAMu
	addr = RamaNr * WIE_RAM;
	cout << space << (char)CharTable::VL;
	for (int i = 0; i < WIE_RAM; i++)
	{
		//rlutil::setColor(rlutil::GREY);
		printf("  %c  ", PlikWymiany[addr + i]);
		//rlutil::setColor(rlutil::LIGHTGREEN);
		cout << (char)CharTable::VL;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyswietla spod ramki
	cout << space << (char)CharTable::CBL;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::HLT;
	}
	for (int j = 0; j < 5; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::CBR << endl;
}
//
void Memory::WydrukujRame(int RamaNr, int StronaNr)
{
	int addr = RamaNr * WIE_RAM;
	string space = "        ";
	cout << "Ramka nr: " << RamaNr;
	if (StronaNr >= 0)
	{
		cout << ", zawiera strone nr: " << StronaNr;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyzwietla gore ramki
	cout << space << (char)CharTable::CTL;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::HLB;
	}
	for (int j = 0; j < 3; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::CTR << endl;
	// ----------------------------------------------------------------------
	// wyzwietla indeksy RAM
	cout << space << (char)CharTable::VL;
	for (int i = 0; i < WIE_RAM; i++)
	{
		if (addr + i < 10)
			printf(" %d ", addr + i);
		else
			printf("%3d", addr + i);
		cout << (char)CharTable::VL;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyzwietla srodek ramki
	cout << space << (char)CharTable::VLR;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::Cross;
	}
	for (int j = 0; j < 3; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::VLL << endl;
	// ----------------------------------------------------------------------
	// wyzwietla zawartosc RAMu
	addr = RamaNr * WIE_RAM;
	cout << space << (char)CharTable::VL;
	for (int i = 0; i < WIE_RAM; i++)
	{
		printf(" %c ", RAM[addr + i]);
		cout << (char)CharTable::VL;
	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyzwietla spod ramki
	cout << space << (char)CharTable::CBL;
	for (int i = 0; i < WIE_RAM - 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << (char)CharTable::HL;
		}
		cout << (char)CharTable::HLT;
	}
	for (int j = 0; j < 3; j++)
	{
		cout << (char)CharTable::HL;
	}
	cout << (char)CharTable::CBR << endl;
}

void Memory::WyczyscRamPlikuWym(int NrRamy) {
	int IndeksRamy = NrRamy * WIE_RAM;
	int IndeksKRamy = NrRamy + WIE_RAM;
	while (IndeksRamy < IndeksKRamy)
	{
		PlikWymiany[IndeksKRamy] = ' ';
		IndeksRamy++;
	}
}
//
void Memory::zwolnieniePamieci(Process * pcb) {
	STRON * TablicaStron = pcb->PobTabStronic();
	int WTablicyStron = pcb->PobWielTabStronic();
	int NrStrony = 0;

	while (NrStrony < WTablicyStron) //usuwanie informacji z pamieci i stronic
	{
		if (TablicaStron[NrStrony].wPam) //wysylamy ramki z pamieci do pliku wymiany
		{
			PrzeStroPamDoPWym(pcb, NrStrony);
		}

		FIFO.remove_if([pcb](const FIFO_entry &victim) {return victim.pcb == pcb; }); //usuwamy z kolejki FIFO pcb

		int frameToFree = TablicaStron[NrStrony].RamaZajeta;
		WyczyscRamPlikuWym(frameToFree);
		WolneRamkiPlikuWymiany.push_back(frameToFree);

		NrStrony++;
	}

	delete[] TablicaStron;

	pcb->UstTabStronic(nullptr);
	pcb->UstWielTabStronic(0);
}
//
void Memory::WydrukujTabliceStronic(Process * pcb) {
	if (pcb == nullptr)
	{
		//rlutil::setColor(rlutil::LIGHTRED);
		cout << "Nie ma takiego procesu.\n";
		//rlutil::setColor(rlutil::LIGHTGREEN);
		return;
	}

	STRON * TablicaStron = pcb->PobTabStronic();
	int WTablicyStron = pcb->PobWielTabStronic();

	cout << " --- Tablica stron procesu: " << pcb->GetPID() << " ---\n";
	//cout << " Nr strony " << (char)CharTable::VL << " Nr  ramki " << (char)CharTable::VL << " Czy w pamieci?\n";

	for (int page = 0; page < WTablicyStron; page++)
	{
		cout << "     " << page;
		for (int i = 0; i < (6 - to_string(page).size()); i++)
		{
			cout << " ";
		}
		//cout << (char)CharTable::VL;
		if (TablicaStron[page].wPam == true)
		{
			cout << "     " << TablicaStron[page].RamaZajeta << "     " << (char)CharTable::VL;
			cout << "      Tak      \n";
		}
		else
		{
			cout << "           " << (char)CharTable::VL;
			cout << "      Nie      \n";
		}
	}
}
//
Memory::Memory()
{
	RAM = new char[WIE_PAM];
	PlikWymiany = new char[WIE_P_WYMIANY];
	for (int i = 0; i < WIE_PAM; i++)
	{
		RAM[i] = ' ';
	}
	for (int i = 0; i < ILOSC_RAM; i++)
		WolneRamki.push_back(i);
	for (int i = 0; i < WIE_P_WYMIANY; i++)
	{
		PlikWymiany[i] = ' ';
	}
	for (int i = 0; i < ILOSC_RAM_P_WYMIANY; i++)
	{
		WolneRamkiPlikuWymiany.push_back(i);
	}
}
Memory::~Memory()
{
	delete[] RAM;
	delete[] PlikWymiany;
}

