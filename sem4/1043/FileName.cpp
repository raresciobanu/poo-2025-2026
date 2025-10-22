#include<iostream>

using namespace std;

void fct1(int a) {
	a = 100;
}

void fct2(int& a) {
	a = 200;
}

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

//class Nume {};
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
	Masina(const Masina& m) :ID(m.ID) {
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

	//cout<<m1;
	//cout<<m1<<"\n"<<m2<<endl;

	// friend - folosit pentru a putea avea acces la zona privata/protected din afara clasei curente
	// practic clasa Masina s a imprietenit cu functia de mai jos => nu mai ai nevoie de getteri cand apelezi informatii private din afara clasei
	friend ostream& operator<<(ostream& afisConsola, const Masina& m);
	friend istream& operator>>(istream& citireConsola, Masina& m);

	// Si poti sa imprietenesti si 2 clase
	// Practic daca ai o Masina in Companie ...o sa poti accesa informatia private din Masina
	//friend class Companie;
};

ostream& operator<<(ostream& afisConsola, const Masina& m) {
	afisConsola << "ID: " << m.ID << " culoare: " << m.culoare << " anFabricatie: " << m.anFabricatie << " nrKm: " << m.nrKm << endl;

	return afisConsola;
}

istream& operator>>(istream& citireConsola, Masina& m) {
	cout << "culoare: "; citireConsola >> m.culoare;
	cout << "anFabricatie: "; citireConsola >> m.anFabricatie;
	cout << "nrKm: "; citireConsola >> m.nrKm;

	return citireConsola;
}


//Tir is a Masina
class Tir : public Masina {
	float tonajMaxim;        // capacitatea maximã de încãrcare
	int nrRemorci;           // numãrul de remorci
public:

	//constr default
	Tir() :Masina() {

		this->tonajMaxim = 0;
		this->nrRemorci = 0;
	}

	//Constr Tir cu toti param fara cei din Masina
	Tir(float tonajMaxim, int nrRemorci) :Masina() {
		this->tonajMaxim = tonajMaxim;
		this->nrRemorci = nrRemorci;
	}

	//sau Constr Tir cu toti param si cu cei din Masina
	Tir(float tonajMaxim, int nrRemorci, int ID, string culoare, int anFabricatie, double nrKm) :Masina(ID, culoare, anFabricatie, nrKm) {
		this->tonajMaxim = tonajMaxim;
		this->nrRemorci = nrRemorci;
	}

	Tir(const Tir& t) :Masina(t) {
		this->tonajMaxim = t.tonajMaxim;
		this->nrRemorci = t.nrRemorci;
	}

	Tir& operator=(const Tir& t) {
		if (this != &t) {
			Masina::operator=(t);

			this->tonajMaxim = t.tonajMaxim;
			this->nrRemorci = t.nrRemorci;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& afisConsola, const Tir& t) {
		afisConsola << (Masina)t;
		afisConsola << "Tonaj maxim: " << t.tonajMaxim << " nrRemorci: " << t.nrRemorci << endl;

		return afisConsola;
	}

	friend istream& operator>>(istream& citireConsola, Tir& t) {
		citireConsola >> (Masina&)t;
		cout << "tonajMaxim: "; citireConsola >> t.tonajMaxim;
		cout << "nrRemorci: "; citireConsola >> t.nrRemorci;

		return citireConsola;
	}
};

//Motocicleta is a Masina
class Motocicleta : public Masina {
	bool areCasca;           // dacã motocicleta are cascã inclusã
	string tipCadru;     // ex: sport, cruiser, touring
public:
	//constr default
	Motocicleta() :Masina() {
		this->areCasca = false;
		this->tipCadru = "unknown";
	}

	//sau Constr Motocicleta cu toti param si cu cei din Masina
	Motocicleta(bool areCasca, string tipCadru, int ID, string culoare, int anFabricatie, double nrKm) :Masina(ID, culoare, anFabricatie, nrKm) {
		this->areCasca = areCasca;
		this->tipCadru = tipCadru;
	}

	Motocicleta(const Motocicleta& m) :Masina(m) {
		this->areCasca = m.areCasca;
		this->tipCadru = m.tipCadru;
	}

	Motocicleta& operator=(const Motocicleta& t) {
		if (this != &t) {
			Masina::operator=(t);

			this->areCasca = t.areCasca;
			this->tipCadru = t.tipCadru;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& afisConsola, const Motocicleta& m) {
		afisConsola << (Masina)m;
		afisConsola << "Are casca: " << m.areCasca << " tipCadru: " << m.tipCadru << endl;

		return afisConsola;
	}

	friend istream& operator>>(istream& citireConsola, Motocicleta& m) {
		citireConsola >> (Masina&)m;
		cout << "areCasca: "; citireConsola >> m.areCasca;
		cout << "tipCadru: "; citireConsola >> m.tipCadru;

		return citireConsola;
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
		for (int i = 0; i < this->nrMasini; i++) {
			this->pMasini[i] = pMasini[i];
		}
	}

	Companie(const Companie& c) {
		this->nrMasini = c.nrMasini;

		this->pMasini = new Masina[this->nrMasini];
		for (int i = 0; i < this->nrMasini; i++) {
			this->pMasini[i] = c.pMasini[i];
		}
	}

	Companie& operator=(const Companie& c) {
		if (this != &c) {
			this->nrMasini = c.nrMasini;

			delete[] this->pMasini;  //evitare memory leaks
			this->pMasini = new Masina[this->nrMasini];

			for (int i = 0; i < this->nrMasini; i++) {
				this->pMasini[i] = c.pMasini[i];
			}
		}

		return *this;
	}

	int getNrMasini() {
		return nrMasini;
	}

	void setNrMasini(int nrMasini) {
		this->nrMasini = nrMasini;
	}

	Masina* getPMasini() {
		return pMasini;
	}

	void setPMasini(Masina* pMasini, int nrMasini) {
		this->nrMasini = nrMasini;

		delete[] this->pMasini; //evitare memory leaks

		this->pMasini = new Masina[nrMasini];

		for (int i = 0; i < nrMasini; i++) {
			this->pMasini[i] = pMasini[i];
		}
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

	friend ostream& operator<<(ostream& out, const Companie& c);
};

ostream& operator<<(ostream& afisConsola, const Companie& c) {
	afisConsola << "Companie cu " << c.nrMasini << " masini: \n";

	for (int i = 0; i < c.nrMasini; i++) {
		afisConsola << c.pMasini[i];
	}

	return afisConsola;
}


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

	cout << "==== op << ====\n";
	cout << c1;
	cout << "\n\n\n";

	cout << "==== op masina >> ====\n";
	Masina m10;
	cin >> m10;
	cout << m10;
	cout << "\n\n\n";


	cout << "==== operatii pe Tir constr, >> si << ====\n";
	Tir t11;
	Tir t12(10.4, 1, 1399, "alb", 2019, 700000.559);

	cin >> t11;
	cout << t11;
	cout << t12;
	cout << "\n\n\n";


	cout << "==== operatii pe Motocicleta constr, >> si << ====\n";
	Motocicleta moto1;
	Motocicleta moto2(true, "cruiser", 1444, "rosu", 2025, 6700.44);

	cin >> moto1;
	cout << moto1;
	cout << moto2;
	cout << "\n\n\n";
}