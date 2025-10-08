#include<iostream>

using namespace std;

//un tip returnat.....denumire functie.....si parametrii
int suma(int a, int b) {
	return a + b;
}

//supraincarcare
int suma(int a, double b) {
	return a + b;
}

//supraincarcare
double suma(int a, double b, int c) {
	return a + b + c;
}

class Masina {
	// zona privata by default
	const int ID;
private:
	string culoare;
protected:
	int anFabricatie;
public:
	double nrKm;

	Masina() :ID(0) {
		this->culoare = "neagra";
		this->anFabricatie = 0;
		this->nrKm = 0.0;
	}

	Masina(int ID, string culoare, int anFabricatie, double nrKm) : ID(ID) {
		this->culoare = culoare;
		this->anFabricatie = anFabricatie;
		this->nrKm = nrKm;
	}

	Masina(int ID, string culoare, int anFabricatie) :ID(ID) {
		this->culoare = culoare;
		this->anFabricatie = anFabricatie;
		this->nrKm = 0.0;
	}

	Masina(int anFabricatie, double nrKm) :ID(0) {
		this->culoare = "neagra";
		this->anFabricatie = anFabricatie;
		this->nrKm = nrKm;
	}


	// Masina m2=m1;// apelare in main pt constr. copiere
	// constr. copiere
	Masina(const Masina& m) :ID(111) {
		this->culoare = m.culoare;
		this->anFabricatie = m.anFabricatie;
		this->nrKm = m.nrKm;
	}

	// m1=m2
	// 
	// 
	// 
	// m1=m2=m3=m4...inlantuire de operatori
	Masina& operator=(const Masina& m) {
		if (this != &m) { //verifica daca nu faci m1=m1
			this->culoare = m.culoare;
			this->anFabricatie = m.anFabricatie;
			this->nrKm = m.nrKm;
		}

		return *this; //aici avem indirectare adica...returneaza obiectul de la adresa din this
	}

	int getID() {
		return ID;
	}

	string getCuloare() {
		return culoare;
	}

	void setCuloare(string culoare) {
		this->culoare = culoare;
	}

	int getAnFabricatie() {
		return anFabricatie;
	}

	void setAnFabricatie(int anFabricatie) {
		this->anFabricatie = anFabricatie;
	}

	int getNrKm() {
		return nrKm;
	}

	void setNrKm(int nrKm) {
		this->nrKm = nrKm;
	}

	~Masina() {
		cout << "Masina " << culoare << " s-a distrus\n";
	}

	void afisareMasina() {
		cout << "ID: " << ID << " culoare: " << culoare << " anFabricatie: " << anFabricatie << " nrKm: " << nrKm << endl;
	}
};

//mostenire de tip has a
class Companie {
	int nrMasini;
	Masina* pMasini;

public:
	Companie(int nrMasini, Masina* pMasini) {
		this->nrMasini = nrMasini;


		//aici se aloca pe HEAP X nrMasini ....si acele masini sunt niste obiecte create prin intermediul 
		//constr. default din clasa Masina...si asta o sa genereze pt fiecare obiect un ID = 0 
		this->pMasini = new Masina[this->nrMasini];

		for (int i = 0; i < nrMasini; i++) {
			this->pMasini[i] = pMasini[i];
		}
	}

	int getNrMasini() {
		return nrMasini;
	}

	Masina* getPMasini() {
		return pMasini;
	}

	//destructor
	~Companie() {
		cout << "Compania cu " << nrMasini << " masini s-a distrus\n";

		delete[]pMasini;
	}

	void afisareCompanie() {
		cout << "Companie cu " << nrMasini << " masini: \n";

		for (int i = 0; i < nrMasini; i++) {
			pMasini[i].afisareMasina();
		}
	}
};

void main() {
	//Apelare constr. default
	Masina m1;
	m1.afisareMasina();

	//Apelare constr. toti param
	Masina m2(20, "verde", 2010, 46600.6);
	m2.afisareMasina();

	//Apelare constr. cu cativa param
	Masina x1(2010, 99999.6);
	Masina x2(11, "rosu", 2010);

	//Apelare constr copiere
	Masina m3(m2);
	Masina m4 = m2;

	//Op egal
	Masina m5;
	m5 = m1;

	cout << "\n\n\n===COMPANIE=====\n\n\n";

	Masina masini[5] = { m1,m2,m3,x1,x2 };
	Companie c1(5, masini);
	c1.afisareCompanie();

	cout << "\n\n\n";
}