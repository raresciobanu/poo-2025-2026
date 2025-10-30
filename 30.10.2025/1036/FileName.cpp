#include<iostream>

using namespace std;

class Angajat {
	//by default totul e privat
	string nume;
	string CNP;
	int varsta;
public:

	//constr default
	Angajat() {
		this->nume = "numeDefault";
		this->CNP = "CNPDefault";
		this->varsta = 0;
	}

	//constr cu toti parametrii
	Angajat(string nume, string CNP, int varsta) {
		this->nume = nume;
		this->CNP = CNP;
		this->varsta = varsta;
	}

	//constr copiere
	Angajat(const Angajat& a) {
		this->nume = a.nume;
		this->CNP = a.CNP;
		this->varsta = a.varsta;
	}

	~Angajat() {
		cout << "Angajatul " << nume << " s a distrus.\n";
	}

	//op =
	//a1=a2;
	//a1=a2=a3=a4=a5
	Angajat& operator=(const Angajat& a) {
		if (this != &a) {//pt a evita a1=a1
			this->nume = a.nume;
			this->CNP = a.CNP;
			this->varsta = a.varsta;
		}

		return *this;//indirectare
	}

	string getNume() {
		return nume;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	string getCNP() {
		return CNP;
	}

	void setCNP(string CNP) {
		this->CNP = CNP;
	}

	int getVarsta() {
		return varsta;
	}

	void setVarsta(int varsta) {
		this->varsta = varsta;
	}
};

class Banca {
private:
	const int ID;
	//mostenire - has A
	string denumire;
	int anInfiintare;
protected:
	int nrAngajati;
	Angajat* pAngajati;
public:
	static int contor;

	Banca() :ID(contor++) {
		this->denumire = "DenumireDefault";
		this->anInfiintare = 0;
		this->nrAngajati = 0;
		this->pAngajati = nullptr;
	}

	Banca(int ID, string denumire, int anInfiintare, int nrAngajati, Angajat* angajati) :ID(ID) {
		this->denumire = denumire;
		this->anInfiintare = anInfiintare;
		this->nrAngajati = nrAngajati;

		this->pAngajati = new Angajat[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->pAngajati[i] = pAngajati[i];
		}
	}

	Banca(const Banca& b) : ID(b.ID) {
		this->denumire = b.denumire;
		this->anInfiintare = b.anInfiintare;
		this->nrAngajati = b.nrAngajati;

		this->pAngajati = new Angajat[b.nrAngajati];
		for (int i = 0; i < b.nrAngajati; i++) {
			this->pAngajati[i] = b.pAngajati[i];
		}
	}

	//b1=b2
	Banca& operator=(const Banca& b) {
		if (this != &b) {
			this->denumire = b.denumire;
			this->anInfiintare = b.anInfiintare;
			this->nrAngajati = b.nrAngajati;

			delete[] this->pAngajati;//pt a evita memory leaks

			this->pAngajati = new Angajat[b.nrAngajati];
			for (int i = 0; i < b.nrAngajati; i++) {
				this->pAngajati[i] = b.pAngajati[i];
			}
		}
		
		return *this;
	}

	~Banca() {
		cout << "Banca " << denumire << " s a distrus.\n";
		delete[] pAngajati;
	}

	int getID() {
		return ID;
	}

	int getNrAngajati() {
		return nrAngajati;
	}

	void setNrAngajati(int nrAngajati) {
		this->nrAngajati = nrAngajati;
	}

	Angajat* getPAngajati() {
		return pAngajati;
	}

	void setAngajati(int nrAngajati, Angajat* pAngajati) {
		this->nrAngajati = nrAngajati;

		//shallow copy
		//this->pAngajati = pAngajati;

		//deep copy
		delete[] this->pAngajati;//pt a evita memory leaks

		this->pAngajati = new Angajat[nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->pAngajati[i] = pAngajati[i];
		}
	}
};

int Banca::contor = 1000;

void main() {
	Angajat a1, a2("Popescu Vasile", "12122112", 22);
	
	Angajat angajati[2] = { a1,a2 };

	Banca b;
	b.setAngajati(2, angajati);
}