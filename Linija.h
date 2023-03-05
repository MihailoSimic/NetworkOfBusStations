#ifndef LINIJA_H
#define LINIJA_H
#include "Stanica.h"
#include "Izuzeci.h"
#include <string>
#include<vector>;
using namespace std;
class Linija {
public:
	Linija();
	Linija(string brojLinije, string pocetnoVreme, string krajnjeVreme, string korak);
	string ucitajRec(string s, int& poz2);
	string broj1Linije();
	void ucitajNizSifri(string s, int& poz, vector<Stanica*> nizStanica);
	bool proveriStanicu(string sifra, vector<Stanica*> nizStanica);
	bool autobusJeNaLiniji(string sifra);
	bool daLiSuNaLiniji(string sifra1, string sifra2);
	string ispisiPutIzmedjuStanica(string sifra1, string sifra2);
	string sifraLinije();
	void ispisiLiniju();
	int brojPolazaka();
	int vremeUMinute(string vreme);
	bool proveriLiniju(string s);
	bool proveriRed(string s);

	bool daLiSuSusedi(string a, string b);
	vector<string> niz();

	void namestiNizPolazaka();
	void namestiNizPovrataka();

	int cekanjeAutobusa(int vreme, string stanica);
	int cekanjeAutobusa2(int vreme, string stanica);

	vector<string> vratiNizSifri();
	int koJeIspred(string stanica1, string stanica2);

	~Linija();
private:
	string brojLinije;
	string pocetnoVreme;
	string krajnjeVreme;
	string korak;
	vector<string> nizSifri;
	vector<int> nizPolazaka;
	vector<int> nizPovrataka;
};

#endif // !

