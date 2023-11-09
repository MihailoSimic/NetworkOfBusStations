#include "Station.h"

Stanica::Stanica(string brojStanice, string ime)
{
	this->brojStanice = brojStanice;
	this->ime = ime;
}

string Stanica::imeStanice()
{
	return this->ime;
}

string Stanica::sifraStanice()
{
	return this->brojStanice;
}

vector<string> Stanica::vratiAutobuse()
{
	return autobusi;
}

void Stanica::ispisiStanicu()
{
	string nazivFajla;
	nazivFajla = "stajaliste_" + this->brojStanice + ".txt";
	ofstream izlaz;
	//ispisuje se stanica u fajl sa nazivom ime_brojStanice.txt u odgovarajucem formatu
	izlaz.open(nazivFajla);
		izlaz << brojStanice << " " << ime << "[";
		for (int i = 0; i < autobusi.size(); i++) {
			izlaz << autobusi[i];
			if (i != autobusi.size() - 1) izlaz << " ";
		}
		izlaz << "]" << endl;

		izlaz.close();
}

void Stanica::sortirajAutobuse()
{
	string prob;
	for (int i = 0; i < this->autobusi.size(); i++) {
		for (int j = i + 1; j < this->autobusi.size();j++) {
			if (autobusi[i] > autobusi[j]) {
				prob = autobusi[i];
				autobusi[i] = autobusi[j];
				autobusi[j] = prob;
			}
		}
	}
}

Stanica::~Stanica()
{
}

void Stanica::ubaciStanicu(string a)
{
		this->autobusi.push_back(a);
	
}
