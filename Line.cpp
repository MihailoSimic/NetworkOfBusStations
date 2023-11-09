#include "Line.h"

Linija::Linija()
{
}

Linija::Linija(string brojLinije, string pocetnoVreme, string krajnjeVreme, string korak)
{
	this->brojLinije = brojLinije;
	this->pocetnoVreme = pocetnoVreme;
	this->krajnjeVreme = krajnjeVreme;
	this->korak = korak;
}

string Linija::ucitajRec(string s, int& poz2)
{
	string rec = "";
	while (s[poz2] != '\n' && s[poz2] != ' ' && s[poz2] != '\0') {
		rec += s[poz2];
		poz2++;
	}
	if (s[poz2] != '\0') poz2++;
	return rec;
}

string Linija::broj1Linije()
{
	return brojLinije;
}

void Linija::ucitajNizSifri(string s, int& poz2, vector<Stanica*> nizStanica)
{
	string probni;
	while (s[poz2] != '\0' && s[poz2-1] !='\n') {
			probni = ucitajRec(s, poz2);
			//U slucaju da je uneta nepostojeca stanica izbacuje se greska
			if (proveriStanicu(probni, nizStanica) == false) {
				cout << "Stanica "<<probni<<" ne postoji." << endl;
				throw new LoseUnetaLinija();
			}
			this->nizSifri.push_back(probni);
		}

	}

bool Linija::proveriStanicu(string sifra, vector<Stanica*> nizStanica)
{
		for (int i = 0; i < nizStanica.size(); i++) {
			if (nizStanica[i]->sifraStanice() == sifra) return true;
		}
		
	return false;
}

bool Linija::autobusJeNaLiniji(string sifra)
{
	for (int i = 0; i < nizSifri.size(); i++) {
		if (nizSifri[i] == sifra) return true;
	}
	return false;
}

bool Linija::daLiSuNaLiniji(string sifra1, string sifra2)
{
	if (autobusJeNaLiniji(sifra1) && autobusJeNaLiniji(sifra2)) return true;
	return false;
}

string Linija::ispisiPutIzmedjuStanica(string sifra1, string sifra2)
{
	string ispis = "";
	if (daLiSuNaLiniji(sifra1, sifra2)) {
		int brojac = 0;
		ispis =ispis+ "->" + brojLinije +"\n";
		for (int i = 0; i < nizSifri.size(); i++) {
			if (nizSifri[i] == sifra1|| nizSifri[i]==sifra2) brojac++;
			if (brojac == 1) ispis= ispis+nizSifri[i]+" ";
			if (brojac == 2) {
				ispis=ispis+ nizSifri[i]+"\n";
				break;
			}
		}
	}
	return ispis;
}

string Linija::sifraLinije()
{
	return this->brojLinije;
}

void Linija::ispisiLiniju()
{
}

int Linija::brojPolazaka()
{	
	return this->nizPolazaka.size();
}

int Linija::vremeUMinute(string vreme)
{
	int a = 0;
	string probni = "";
	probni += vreme[0];
	probni += vreme[1];
	a += stoi(probni) * 60;
	probni = "";
	probni += vreme[3];
	probni += vreme[4];
	a += stoi(probni);
	return a;
}

bool Linija::daLiSuSusedi(string a, string b)
{
	if (a == b) return true;
	for (int i = 1; i < nizSifri.size(); i++) {
		if (nizSifri[i - 1] == a && nizSifri[i] == b) return true;
		if (nizSifri[i - 1] == b && nizSifri[i] == a) return true;
	}
	return false;
}

vector<string> Linija::niz()
{
	return nizSifri;
}
//Formira niz polazaka autobusa zavisno od reda voznje
void Linija::namestiNizPolazaka()
{
	int pocetno, krajnje, k;
	pocetno = vremeUMinute(pocetnoVreme);
	krajnje = vremeUMinute(krajnjeVreme);
	k = stoi(korak);
	while (krajnje >= pocetno) {
		nizPolazaka.push_back(pocetno);
		pocetno = pocetno + k;
	}
}
//Program radi kao da autobusi idu u oba smera
void Linija::namestiNizPovrataka()
{
	int pocetno, krajnje, k,brojStanica;
	pocetno = vremeUMinute(pocetnoVreme);
	krajnje = vremeUMinute(krajnjeVreme);
	k = stoi(korak);
	brojStanica = nizSifri.size();
	//Vreme kad autobus krece sa poslednje stanice
	pocetno += 3 * brojStanica;
	krajnje += 3 * brojStanica;
	while (krajnje >= pocetno) {
		nizPovrataka.push_back(pocetno);
		pocetno +=k;
	}
}

int Linija::cekanjeAutobusa(int vreme, string stanica)
{
	int broj=-1;
	for (int i = 0; i < nizSifri.size(); i++) {
		if (nizSifri[i] == stanica) broj = i;
	}
	if (broj != -1) {
		for (int i = 0; i < nizPolazaka.size(); i++) {
			
			if (nizPolazaka[i]+broj*3 >= vreme) {
				//return vreme - nizPolazaka[i - 1]-broj*3;
				return nizPolazaka[i] - vreme + broj * 3;
			}

		}
	}
	return -1;
}

int Linija::cekanjeAutobusa2(int vreme, string stanica)
{
	int broj = -1;
	for (int i = 0; i < nizSifri.size(); i++) {
		if (nizSifri[i] == stanica) broj = nizSifri.size()-i+1;
	}
	if (broj != -1) {
		for (int i = 0; i < nizPolazaka.size(); i++) {
			if (nizPovrataka[i] + broj * 3 >= vreme) {
				
				return nizPovrataka[i] - vreme + broj * 3;
			}

		}
	}
	return -1;
}


vector<string> Linija::vratiNizSifri()
{
	return nizSifri;
}

int Linija::koJeIspred(string stanica1, string stanica2)
{
	//Ako nisu susedi vraca vrednost - 1 ako je prva ispred druge vraca vrednost 1 a ako je druga ispred prve vraca vrednost 2
	if (daLiSuSusedi(stanica1, stanica2) == true) {
		for (int i = 0; i < nizSifri.size();i++) {
			if (nizSifri[i] == stanica1 && nizSifri[i + 1] == stanica2) return 1;
			if (nizSifri[i] == stanica2 && nizSifri[i + 1] == stanica1) return 2;
		}
	}
return -1;
}

Linija::~Linija()
{
	delete this;
}




