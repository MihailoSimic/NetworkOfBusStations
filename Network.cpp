#include "Network.h"

string Mreza::ucitajRec(string s, int& poz)
{
		string rec = "";
		while (s[poz] != '\n' && s[poz] != ' ' && s[poz] != '\0') {
			rec += s[poz];
			poz++;
		}
		if (s[poz] != '\0') poz++;
		return rec;
}

void Mreza::ucitajNizStanica(string s1, int& poz)
{
	//red po red ucitavaju se stanice sa sifrom i nazivom
	while (s1[poz] != '\0') {
		string sifra, ime = "";
		//ucitava do prvog razmaka
		sifra = ucitajRec(s1, poz);
		for (int i = 0; i < sifra.size(); i++) {
			//Ako sifra stanice sadrzi karakter koji nije cifra
			if (sifra[i] < '0' || sifra[i]>'9') throw new losaSifraStanice();
		}
		while (s1[poz] != '\n' && s1[poz] != '\0') {
			ime += s1[poz];
			poz++;
		}
		if (s1[poz] != '\0') poz++;
		Stanica* s = new Stanica(sifra, ime);
		this->nizStanica.push_back(s);
	}
}

void Mreza::ucitajNizLinija(string s2, int& poz2)
{
	//red po red ucitava linije dok ne stigne do kraja
	while (s2[poz2] != '\0') {
		string autobus;
		autobus = ucitajRec(s2, poz2);
		int brojac = 1;
		string vreme, pocetnoVreme, krajnjeVreme, korak;
		vreme = ucitajRec(s2, poz2);
		while (vreme[brojac] != '-') {
			pocetnoVreme += vreme[brojac];
			brojac++;
		}
		brojac++;
		while (vreme[brojac] != '#') {
			krajnjeVreme += vreme[brojac];
			brojac++;
		}
		brojac++;
		while (vreme[brojac] != ']') {
			korak += vreme[brojac];
			brojac++;
		}
		//ucitavanje linije i namestanje svih njenih parametara
		Linija* l = new Linija(autobus, pocetnoVreme, krajnjeVreme, korak);
		
		l->ucitajNizSifri(s2, poz2,nizStanica);
		l->namestiNizPolazaka();
		l->namestiNizPovrataka();
		this->nizLinija.push_back(l);
	}
}

void Mreza::namestiStanice()
{

	for (int k = 0; k < this->nizStanica.size(); k++) {

		for (int i = 0; i < nizLinija.size(); i++) {

			if (nizLinija[i]->autobusJeNaLiniji(nizStanica[k]->sifraStanice())) {
				nizStanica[k]->ubaciStanicu(nizLinija[i]->sifraLinije());
			}
		}
		nizStanica[k]->sortirajAutobuse();
	}
}

string Mreza::stanicaUSifru(string imeStanice)
{
	for (int i = 0; i < nizStanica.size(); i++) {
		if (imeStanice == nizStanica[i]->imeStanice()) {
			return nizStanica[i]->sifraStanice();
		}
	}

}

int Mreza::sifraUstanicu(string sifraStanice)
{
	for (int i = 0; i < nizStanica.size(); i++) {
		if (sifraStanice == nizStanica[i]->sifraStanice()) {
			return i;
		}
	}
}

string Mreza::sifraUImeStanice(string sifraStanice)
{
	for (int i = 0; i < nizStanica.size(); i++) {
		if (sifraStanice == nizStanica[i]->sifraStanice()) {
			return nizStanica[i]->imeStanice();
		}
	}
	return string();
}

string Mreza::linijaUSifru(string oznakaLinije)
{
	for (int i = 0; i < nizLinija.size(); i++) {

		if (nizLinija[i]->broj1Linije() == oznakaLinije) return nizLinija[i]->sifraLinije();
	}
	return string();
}

void Mreza::informacijeOStanici(string sifra)
{
	//prolazi kroz spisak stanica nalazi odgovarajucu za ispis i ispisuje je
	for (int i = 0; i < nizStanica.size(); i++) {
		if (nizStanica[i]->sifraStanice() == sifra) {
			nizStanica[i]->ispisiStanicu();
		}
	}
}

void Mreza::informacijeOLiniji(string sifra)
{
	//prolazi kroz spisak linija nalazi odgovarajucu za ispis i ispisuje je
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->sifraLinije() == sifra) {
			ispisiLiniju(sifra);
		}
	}
	cout << endl;
}

void Mreza::statistikaLinije(string oznaka)
{
	int brojPolazaka;
	string oznakaLinije;
	string sifra = linijaUSifru(oznaka);
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->sifraLinije() == oznaka) {
			brojPolazaka = nizLinija[i]->brojPolazaka();
			oznakaLinije = nizLinija[i]->sifraLinije();
			
		}
	}
	ofstream izlaz;
	string nazivFajla;
	nazivFajla = "statistika_" + oznaka+".txt";
	izlaz.open(nazivFajla);
	izlaz << oznaka << endl;
	izlaz << susedneLinije(oznaka)<<endl;
	izlaz<< brojPolazaka<<endl;
	izlaz.close();
}

string Mreza::susedneLinije(string sifra)
{
	int broj;
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->sifraLinije() == sifra) {
			broj = i;
			break;
		}
	}
	string s = "",s2="";
	vector<string> niz;
	for (int i = 0; i < nizLinija.size(); i++) {

		if (nizLinija[i]->sifraLinije() == sifra) continue;
		vector<string> pomocni;
		pomocni = nizLinija[i]->vratiNizSifri();

		for (int j = 0; j < pomocni.size(); j++) {

			if (nizLinija[broj]->autobusJeNaLiniji(pomocni[j])) {
				niz.push_back(nizLinija[i]->sifraLinije());
				s += nizLinija[i]->sifraLinije() + " ";
				break;
			}
		}
	}
	string pom;
	for (int i = 0; i < niz.size(); i++) {
		for (int j = i; j < niz.size(); j++) {
			if (niz[i] > niz[j]) {
				pom = niz[i];
				niz[i] = niz[j];
				niz[j] = pom;
			}
		}
	}

	for (int i = 0; i < niz.size(); i++) {
		s2 += niz[i];
		if (i != niz.size() - 1) s2 += " ";
	}
	return s2;
}



void Mreza::ispisiLiniju(string naziv)
{
	Linija* l;
	vector<string> n;
	string nazivFajla;
	nazivFajla = "linija_" + naziv+".txt";
	ofstream izlaz;
	izlaz.open(nazivFajla);
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->sifraLinije() == naziv) {
			l = nizLinija[i];
			n = l->niz();
			break;
		}
	}
	
	izlaz << naziv << " " << sifraUImeStanice(n[0]) << "->" << sifraUImeStanice(n[n.size()-1]) << endl;
	for (int i = 0; i < n.size(); i++) {
		izlaz << n[i] << " " << sifraUImeStanice(n[i]);
		if (i != n.size() - 1) izlaz << endl;
	}
	izlaz.close();
}

void Mreza::ispisiStanicu(string sifra)
{
	for (int i = 0; i < nizStanica.size(); i++) {
		if (nizStanica[i]->sifraStanice() == sifra) nizStanica[i]->ispisiStanicu();
	}
}

int Mreza::daLiSuSusedi(int a, int b)
{
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->daLiSuSusedi(nizStanica[a]->sifraStanice(), nizStanica[b]->sifraStanice()) == true) return i;
		i++;
	}
	return -1;
}

void Mreza::namestiMapu()
{
	//stanice dobijaju redom vrednosti od 0 do n
	for (int i = 0; i < nizStanica.size(); i++) {
		mapaIndeksa.insert(pair<string,int>(nizStanica[i]->sifraStanice(), i));
	}
}

void Mreza::namestiGraf()
{
	vector<string> niz;
	//prolazi kroz sve linije i redom spaja susedne stanice u oba smera
	for (int i = 0; i < nizLinija.size(); i++) {

		niz = nizLinija[i]->vratiNizSifri();

		for (int j = 0; j < niz.size()-1; j++) {

			pair<int, Linija*> p(mapaIndeksa[niz[j + 1]], nizLinija[i]);
			pair<int, Linija*> p2(mapaIndeksa[niz[j]], nizLinija[i]);
			graf[mapaIndeksa[niz[j] ] ].push_back(p);
			graf[mapaIndeksa[niz[j + 1]]].push_back(p2);
		}
	}
}

void Mreza::namestiGraf2()
{
	vector<string> niz;
	int probni1,probni2;
	//redom prolazi kroz linije i spaja sve grane sa jedne linije medjusobno
	for (int i = 0; i < nizLinija.size(); i++) {

		niz = nizLinija[i]->vratiNizSifri();

		for (int j = 0; j < niz.size(); j++) {
			for (int k = j+1; k < niz.size(); k++) {
				probni1 = mapaIndeksa[niz[k]];
				probni2 = mapaIndeksa[niz[j]];
				graf2[probni1].push_back(probni2);
				graf2[probni2].push_back(probni1);
			}
		}
	}

}

pair<int,string> Mreza::najmanjeRastojanjeIzmedjuSusednih(int t, string sif1, string sif2)
{
	int sifra1 = mapaIndeksa[sif1];
	int sifra2 = mapaIndeksa[sif2];
	int minimum = 99999,rastojanje;
	string linija;
	for (int i = 0; i < graf[sifra1].size(); i++) {
		if (graf[sifra1][i].first == sifra2) {
			if(graf[sifra1][i].second->koJeIspred(sif1,sif2)==1){
			rastojanje = graf[sifra1][i].second->cekanjeAutobusa(t, sif1);
			}
			if (graf[sifra1][i].second->koJeIspred(sif1, sif2) == 2) {
				rastojanje = graf[sifra1][i].second->cekanjeAutobusa2(t, sif1);
			}

		if (rastojanje < minimum) {
			minimum = rastojanje;
			linija = graf[sifra1][i].second->sifraLinije();
		}
		}
	}
	pair<int, string> p(minimum + 3, linija);
	return p;
}


void Mreza::dijkstra(string pocetni,int t,string krajnji,int x)
{
	int pocetna = mapaIndeksa[pocetni];
	int krajnja = mapaIndeksa[krajnji];
	//niz rastojanja(na pocetku beskonacno veliki)
	int* rastojanje=new int[nizStanica.size()];
	//niz koji govori koji cvorovi su poseceni u grafu(na pocetku nijedan)
	bool* poseceni=new bool[nizStanica.size()];
	//lista koja nam govori o predhodno posecenoj stanici, bitno za pronalazak puta
	int* predhodni=new int[nizStanica.size()];

	//prati kojom autobuskom linijom smo dosli do odredjene stanice
	string* linijaDoPrethodnog = new string[nizStanica.size()];
	//pocetni uslovi
	for (int i = 0; i < nizStanica.size(); i++) {
		poseceni[i] = false;
		rastojanje[i] = 9999;
		predhodni[i] = -1;
		linijaDoPrethodnog[i] = "";
	}
	//rastojanje do stanice od koje smo krenuli je 0
	rastojanje[pocetna] = 0;



	for (int i = 0; i < nizStanica.size()-1; i++) {
		//za sledeci cvor uzimamo onaj koji trenutno ima najmanje rastojanje od pocetnog
		int u = pronadjiMinimum(rastojanje, poseceni);
		poseceni[u] = true;

		for (int j = 0; j < graf[u].size(); j++) {
			
			if (poseceni[graf[u][j].first] == false) {
				//pronalazi najmanje rastojanje u funkciji od vremena u kom se nalazimo na stanici i odredjuje sa koje stanice smo dosli
				int x = najmanjeRastojanjeIzmedjuSusednih(t + rastojanje[u], nizStanica[u]->sifraStanice(), nizStanica[graf[u][j].first]->sifraStanice()).first;
				string l = najmanjeRastojanjeIzmedjuSusednih(t + rastojanje[u], nizStanica[u]->sifraStanice(), nizStanica[graf[u][j].first]->sifraStanice()).second;
				//promena vrednosti za rastojanje u slucaju da smo pronasli kraci put
				if (poseceni[graf[u][j].first] == false && rastojanje[u] != 9999 && rastojanje[u] + x < rastojanje[graf[u][j].first]) {
					rastojanje[graf[u][j].first] = rastojanje[u] + x;
					predhodni[graf[u][j].first] = u;
					linijaDoPrethodnog[graf[u][j].first] = l;
				}
			}
		}


	}
	vector<pair<string, string>> v;
	namestiVektor(predhodni, linijaDoPrethodnog, krajnja,v);

	ofstream izlaz;
	string nazivFajla;
	//da bi se ispisala oba fajla kasnije
	if(x==0)nazivFajla = "putanja_" + pocetni + "_" + krajnji + ".txt";
	if(x==1)nazivFajla = "najkraca_putanja_" + pocetni + "_" + krajnji + ".txt";

	izlaz.open(nazivFajla);
	//ispis puta nakon dijkstrinog algoritma
	for (int i = 0; i < v.size(); i++) {
		if (i == 0) {
			izlaz << "->" << v[i].second << endl;
			izlaz << nizStanica[ pocetna]->sifraStanice() << "," << v[i].first;
		}
		if (i != 0 && v[i].second == v[i - 1].second) {
			izlaz << "," << v[i].first;
		}
		if (i != 0 && v[i].second != v[i - 1].second) {
			izlaz << endl << "->" << v[i].second << endl;
			izlaz << v[i - 1].first << "," << v[i].first;
		}
	}
	izlaz.close();
	delete[] rastojanje;
	delete[] poseceni;
	delete[] predhodni;
	delete[] linijaDoPrethodnog;
}

//Najkraci put u grafu, ovaj algoritam se vrsi nad grafom 2
//prolazi kroz susede od pocetnog pa susede od suseda itd... Racuna rastojanje od pocetnog do svih
//Graf 2 nije tezinski za razliku od grafa 1 ne treba nam vremenski parametar svi susedi su jednako udaljeni
void Mreza::bfs(string pocetni, string krajnji)
{
	int pocetna = sifraUstanicu(pocetni);
	int krajnja = sifraUstanicu(krajnji);
	//niz posecenih na pocetku prazan
	bool* posecen = new bool[nizStanica.size()];
	//niz koji nam govori o tome iz kog cvora smo dosli
	int* prethodni = new int[nizStanica.size()];
	//pocetni uslovi
	for (int i = 0; i < nizStanica.size(); i++) {
		posecen[i] = false;
		prethodni[i] = -1;
	}
	vector<int> niz;
	posecen[pocetna] = true;
	niz.push_back(pocetna);
	int brojac = 0;
	while (brojac != nizStanica.size()) {

		int s = niz[brojac];
		for (int i = 0; i < graf2[s].size(); i++) {
			if (posecen[graf2[s][i]] == false) {
				niz.push_back(graf2[s][i]);
				posecen[graf2[s][i]] = true;
				prethodni[graf2[s][i]] = s;
			}
		}
		brojac++;
	}
	vector<string> v;
	string s = "";
	v.push_back(nizStanica[pocetna]->sifraStanice());
	namestiVektor2(prethodni, krajnja, v);
	//ispis nakon izvrsenog algoritma
	for (int i = 0; i < v.size() - 1; i++) {
		int k = pronadjiLinijuIzmedjuDve(v[i], v[i + 1]);
		s += nizLinija[k]->ispisiPutIzmedjuStanica(v[i], v[i + 1]);
	}
	ofstream izlaz;
	string nazivFajla;
	nazivFajla = "putanja_sa_najmanje_presedanja_od_" + pocetni + "_do_" + krajnji+".txt";
	izlaz.open(nazivFajla);
	izlaz << s;
	izlaz.close();
}


void Mreza::namestiVektor(int* predhodni, string* linijaDoPredhodnog,int poslednji, vector<pair<string, string>> &v)
{
	if (predhodni[poslednji] == -1) return;


	namestiVektor(predhodni, linijaDoPredhodnog, predhodni[poslednji],v);
		
			pair<string, string> p(nizStanica[poslednji]->sifraStanice(), linijaDoPredhodnog[poslednji]);
			v.push_back(p);
}

void Mreza::namestiVektor2(int* predhodni, int poslednji, vector<string>& v)
{
	if (predhodni[poslednji] == -1) return;

	namestiVektor2(predhodni, predhodni[poslednji], v);
	v.push_back(nizStanica[poslednji]->sifraStanice());
}


int Mreza::pronadjiLinijuIzmedjuDve(string sifra1, string sifra2)
{
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->daLiSuNaLiniji(sifra1, sifra2)) return i;
	}
	return -1;
}

int Mreza::pronadjiMinimum(int* a,bool*b)
{
		int minimum = 9999;
		int indeks = -1;
		for (int i = 0; i < nizStanica.size(); i++) {
			if (a[i] <= minimum && b[i] == false) {
				minimum = a[i];
				indeks = i;
			}
		}
		return indeks;
}

bool Mreza::proveriStanicu(string s)
{
	for (int i = 0; i < nizStanica.size(); i++) {
		if (nizStanica[i]->sifraStanice() == s) return true;
	}
	return false;
}

bool Mreza::proveriLiniju(string s)
{
	for (int i = 0; i < nizLinija.size(); i++) {
		if (nizLinija[i]->sifraLinije() == s) return true;
	}
	return false;
}

bool Mreza::proveriLinije(string s)
{
	ifstream ulaz;
	ulaz.open(s);
	string red;
	while (getline(ulaz, red)) {
		if (!proveriRed(red)) return false;
	}


	ulaz.close();
	return true;
}

bool Mreza::proveriRed(string s)
{
	int poz = 0;
	this->ucitajRec(s, poz);
	string pomocni;
	pomocni = this->ucitajRec(s, poz);
	if (pomocni[0] != '[') return false;
	if (pomocni[pomocni.size() - 1] != ']') return false;
	if (pomocni[3] != ':' || pomocni[6] != '-' || pomocni[9] != ':' || pomocni[12] != '#') return false;

	if (pomocni[1] < '0' || pomocni[2]>'9') return false;
	if (pomocni[2] < '0' || pomocni[2]>'9') return false;
	if (pomocni[4] < '0' || pomocni[2]>'9') return false;
	if (pomocni[5] < '0' || pomocni[2]>'9') return false;
	if (pomocni[7] < '0' || pomocni[2]>'9') return false;
	if (pomocni[8] < '0' || pomocni[2]>'9') return false;
	if (pomocni[10] < '0' || pomocni[2]>'9') return false;
	if (pomocni[11] < '0' || pomocni[2]>'9') return false;

	return true;
}

bool Mreza::proveriVreme(string s)
{
	if (s.size() != 5) return false;
	if (s[0] < '0' || s[0]>'2') return false;
	if (s[1] < '0' || s[1]>'9') return false;
	if (s[3] < '0' || s[3]>'5') return false;
	if (s[4] < '0' || s[4]>'9') return false;
	if (s[2]!=':') return false;
	
	return true;
}

Mreza::~Mreza()
{
	for (int i = 0; i < this->nizStanica.size(); i++) {
		delete nizStanica[i];
	}
	for (int j = 0; j < this->nizLinija.size(); j++) {
		delete nizLinija[j];
	}
	
	delete this;
}






