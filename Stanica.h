#ifndef STANICA_H
#define STANICA_H
#include <iostream>
#include <string>
#include<vector>
#include<fstream>
using namespace std;
class Stanica {
public:
	Stanica(string brojStanice, string ime);
	string imeStanice();
	string sifraStanice();
	vector<string> vratiAutobuse();
	void ubaciStanicu(string a);
	void ispisiStanicu();
	void sortirajAutobuse();
	~Stanica();
private:
	string brojStanice;
	string ime;
	int vreme;
	vector<string> autobusi;

};
#endif
