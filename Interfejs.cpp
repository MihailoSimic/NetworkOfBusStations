#include "Interfejs.h"

Interfejs::Interfejs()
{
	this->M = new Mreza;
}

void Interfejs::pokreniInterfejs()
{
	try {
		int n, n2, poz = 0;
		string s1, s2;
		cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:" << endl;
		cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
		cout << "0. Kraj rada" << endl;
		cin >> n;
		if (n == 0) {
			cout << "Koriscenje programa je zavrseno." << endl;
			return;
		}
		if (n == 1) {
			cout << "Molimo Vas, unesite putanju do fajla sa stajalistima :" << endl;
			cin >> s1;
			string s = "", s3;
			ifstream ulaz1;
			ulaz1.open(s1);
			//Ceo ulazni fajl se ubacuje u string s koji se parsira
			while (getline(ulaz1, s3)) {
				s += s3 + "\n";
			}

			ulaz1.close();
			int poz = 0;
			M->ucitajNizStanica(s, poz);
			cout << endl << " Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza :" << endl;
			cin >> s2;
			if (M->proveriLinije(s2) == false) throw new LoseUnetaLinija();
			s = "";
			ifstream ulaz2;
			ulaz2.open(s2);
			//Ceo ulazni fajl se ubacuje u string s koji se parsira
			while (getline(ulaz2, s3)) {
				s += s3 + "\n";
			}

			ulaz2.close();
			poz = 0;
			M->ucitajNizLinija(s, poz);
			M->namestiStanice();
			M->namestiMapu();
			M->namestiGraf();
			M->namestiGraf2();
			cout << "Mreza gradskog prevoza je uspesno ucitana.Molimo Vas, odaberite opciju :" << endl;
			cout << "1. Prikaz informacija o stajalistu" << endl;
			cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
			cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
			cout << "4. Pronalazak putanje izmedju dva stajalista" << endl;
			cout << "0. Kraj rada" << endl;
			while (true) {
				cin >> n2;
				if (n2 == 0) {
					cout << "Koriscenje programa je zavrseno.";
					break;
				}
				if (n2 == 1) {
					cout << "Molimo Vas, unesite sifru stajalista cije informacije zelite da prikazete." << endl;
					string sifra;
					cin >> sifra;
					//provera da li uneta stanica postoji
					if (M->proveriStanicu(sifra) == false) {
						throw new loseUnetaStanica();
					}
					M->informacijeOStanici(sifra);
				}
				if (n2 == 2) {
					cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
					string oznaka;
					cin >> oznaka;
					//provera da li uneta linija postoji
					if (M->proveriLiniju(oznaka) == false) throw new losaLinija();
					M->informacijeOLiniji(oznaka);
				}
				if (n2 == 3) {
					cout << "Molimo Vas, unesite oznaku linije ciju statistiku zelite da prikazete." << endl;
					string oznaka;
					cin >> oznaka;
					//provera da li uneta linija postoji
					if (M->proveriLiniju(oznaka) == false) throw new losaLinija();
					M->statistikaLinije(oznaka);

				}
				if (n2 == 4) {
					string sifra1, sifra2;
					cout << "Molimo Vas, unesite šifru pocetnog i krajnjeg stajalista." << endl;
					cin >> sifra1 >> sifra2;

					if (M->proveriStanicu(sifra1) == false) throw new loseUnetaStanica();
					if (M->proveriStanicu(sifra2) == false) throw new loseUnetaStanica();
					cout << endl << "Molimo Vas, unesite vreme polaska u fromatu xx:yy." << endl;
					int t = 0;
					string vreme;
					cin >> vreme;
					//provera da li je vreme uneto u dobrom formatu
					if (M->proveriVreme(vreme) == false) throw new loseUnetoVreme();
					string probni = "";
					//konvertovanje u minute
					probni += vreme[0];
					probni += vreme[1];
					t += stoi(probni) * 60;
					probni = "";
					probni += vreme[3];
					probni += vreme[4];
					t += stoi(probni);

					//bilo koji put
					M->dijkstra(sifra1, t, sifra2,0);

					//najbrzi put
					M->dijkstra(sifra1, t, sifra2,1);

					//put sa najmanje presedanja
					M->bfs(sifra1, sifra2);

				}
				if (n2 > 4 || n2 < 0) cout << "Greska. Molimo vas ponovo unesite zahtev.";
				else cout << "Funkcija je uspesno izvrsena. Molimo vas unesite sledeci zahtev" << endl<< endl;
			}

		}
	}
	catch (LoseUnetaLinija* e) {
		cout << e->what();
		delete e;
	}
	catch (losaSifraStanice* e) {
		cout << e->what();
		delete e;
	}
	catch (loseUnetaStanica* e) {
		cout << e->what();
		delete e;
	}
	catch (losaLinija* e) {
		cout << e->what();
		delete e;
	}
	catch (loseUnetoVreme* e) {
		cout << e->what();
		delete e;
	}
}

Interfejs::~Interfejs()
{
	delete this->M;
}
