#ifndef IZUZECI_H
#define IZUZECI_H

#include<exception>
using namespace std;

class LoseUnetaLinija : public exception {

public:
	LoseUnetaLinija() : exception("Linije nisu unete u adekvatnom formatu.") {};
};

class losaSifraStanice : public exception {

public:
	losaSifraStanice() : exception("Sifra stanice nije uneta u adekvatnom formatu.") {};
};

class loseUnetaStanica : public exception {

public:
	loseUnetaStanica() : exception("Uneta stanice se ne nalazi ni na jednoj liniji.") {};
};
class losaLinija : public exception {

public:
	losaLinija() : exception("Uneta linija se ne nalazi u fajlu sa spiskom linija.") {};
};
class loseUnetoVreme : public exception {

public:
	loseUnetoVreme() : exception("Vreme nije uneto u adekvatnom formatu.") {};
};
#endif