#ifndef MREZA_H
#define MREZA_H
#include "Line.h"
#include "Station.h"
#include "Exceptions.h"
#include <map>
#include <set>
#include<iterator>
#include<fstream>
class Mreza {
public:
	string ucitajRec(string s, int& poz);
	void ucitajNizStanica(string s1, int& poz);
	void ucitajNizLinija(string s2, int& poz2);
	void namestiStanice();
	string stanicaUSifru(string imeStanice);
	int sifraUstanicu(string sifraStanice);
	string sifraUImeStanice(string sifraStanice);
	string linijaUSifru(string oznakaLinije);

	void informacijeOStanici(string sifra);
	void informacijeOLiniji(string sifra);
	void statistikaLinije(string oznaka);
	string susedneLinije(string sifra);
	

	void ispisiLiniju(string naziv);
	void ispisiStanicu(string sifra);
	int daLiSuSusedi(int a,int b);
	void namestiMapu();
	void namestiGraf();
	void namestiGraf2();
	pair<int, string> najmanjeRastojanjeIzmedjuSusednih(int t, string sif1, string sif2);

	void dijkstra(string pocetna,int t,string krajnja,int x);
	void bfs(string pocetni, string krajnji);
	void namestiVektor(int* predhodni, string* linijaDoPredhodnog,int poslednji, vector<pair<string, string>>& v);
	void namestiVektor2(int* predhodni, int poslednji, vector<string>& v);

	int pronadjiLinijuIzmedjuDve(string sifra1, string sifra2);
	int pronadjiMinimum(int* a,bool* b);

	bool proveriStanicu(string s);
	bool proveriLiniju(string s);
	bool proveriLinije(string s);
	bool proveriRed(string s);
	bool proveriVreme(string s);

	~Mreza();
private: 
	vector<Stanica*> nizStanica; //Cvorofi grafa
	vector<Linija*> nizLinija;
	//Mapa sifri stanica i odgovarajucih brojeva
	map<string, int> mapaIndeksa;
	//graf u kome su susedne linije povezane
	vector<pair<int,Linija*>> graf[100];
	//graf u kome su svake dve stanice na istoj liniji povezane
	vector<int> graf2[100];

};
#endif;
