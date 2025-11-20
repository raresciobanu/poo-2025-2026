#include<iostream>

using namespace std;

class Restaurant {
	string denumire;
	string* pProduse;
	int nrProduse;
	double incasari;

public:
	Restaurant() {
		this->denumire = "";
		this->nrProduse = 0;
		this->pProduse = nullptr;
		this->incasari = 0.0;
	}

	Restaurant(string denumire, int nrProduse, string* pProduse, double incasari) {
		this->denumire = denumire;

		this->nrProduse = nrProduse;

		this->pProduse = new string[nrProduse];
		for (int i = 0; i < nrProduse; i++) {
			this->pProduse[i] = pProduse[i];
		}

		this->incasari = incasari;
	}

	Restaurant(const Restaurant& r) {
		this->denumire = r.denumire;

		this->nrProduse = r.nrProduse;

		this->pProduse = new string[r.nrProduse];
		for (int i = 0; i < r.nrProduse; i++) {
			this->pProduse[i] = r.pProduse[i];
		}

		this->incasari = r.incasari;
	}


	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			this->denumire = r.denumire;

			this->nrProduse = r.nrProduse;

			delete[] this->pProduse;//evitare memory leaks
			this->pProduse = new string[r.nrProduse];
			for (int i = 0; i < r.nrProduse; i++) {
				this->pProduse[i] = r.pProduse[i];
			}

			this->incasari = r.incasari;
		}

		return *this;
	}

	~Restaurant() {
		delete[] this->pProduse;
	}

	//operatori

	//op <<
	friend ostream& operator<<(ostream& afisareConsola, const Restaurant& r) {
		afisareConsola << "Denumire: " << r.denumire << " incasari: " << r.incasari
			<< " nrProduse: " << r.nrProduse << " produse: ";

		for (int i = 0; i < r.nrProduse; i++) {
			afisareConsola << "produsul[" << i << "] = " << r.pProduse[i] << " ";
		}

		afisareConsola << endl;
		return afisareConsola;
	}

	//op >>
	friend istream& operator>>(istream& citireConsola, Restaurant& r) {
		char aux[100];

		cout << "Denumire: "; citireConsola.getline(aux, 100);
		r.denumire = aux;

		cout << "Incasari: "; citireConsola >> r.incasari;
		cout << "NrProduse: "; citireConsola >> r.nrProduse;
		cout << "Produse:\n";

		citireConsola.ignore(); //golire buffer 

		delete[] r.pProduse;//evitare memory leaks
		r.pProduse = new string[r.nrProduse];
		for (int i = 0; i < r.nrProduse; i++) {
			cout << "produsul[" << i + 1 << "] = "; citireConsola.getline(aux, 100);
			r.pProduse[i] = aux;
		}

		return citireConsola;
	}

	//op ++ pre-incrementare.
	Restaurant& operator++() {
		this->incasari += 100;
		return *this;
	}

	//op ++ post-incrementare
	Restaurant operator++(int) {
		Restaurant aux(*this);

		this->incasari += 100;

		return aux;
	}

	//op + (Restaurant + double)
	Restaurant operator+(double value) {
		Restaurant aux(*this);

		aux.incasari += value;

		return aux;
	}

	//op + (double + Restaurant)
	friend Restaurant operator+(double value, Restaurant r1) {
		Restaurant aux(r1);

		aux.incasari += value;

		return aux;
	}

	//op + (Restaurant + Restaurant)
	double operator+(const Restaurant& r1) {
		return this->incasari + r1.incasari;
	}


	//op [] 
	string operator[](int index) {
		if (index >= 0 && index < nrProduse) {
			return this->pProduse[index];
		}
		else {
			throw exception("index out of bounds: " + index);
		}
	}

	//op !
	bool operator!() {
		return this->nrProduse > 0;
	}

	//op conversie / cast
	operator string() {
		return this->denumire;
	}
};

void main() {
	Restaurant r1;
	//op <<
	cout << r1 << endl;

	//op ++ post incrementare
	cout << "post incrementare: " << r1++ << endl;

	//op ++ pre incrementare
	cout << "pre incrementare: " << ++r1 << endl;

	//op + (Restaurant + double)
	cout << "+ (Restaurant + double): " << (r1 + 200.5) << endl;

	//op + (double + Restaurant)
	cout << "+ (double + Restaurant): " << (300.5 + r1) << endl;

	//op + (Restaurant + Restaurant)
	string produse[3] = { "prod1", "prod2", "prod3" };
	Restaurant r2("La Placinte", 3, produse, 3999.99);
	cout << "+ (Restaurant + Restaurant): " << r1 + r2 << endl << endl;

	//op []
	cout << "op []: " << r2[1] << endl << endl;

	//op !

	if (!r2) {
		cout << "r2 are produse" << endl << endl;
	}


	//op conversie
	cout << "cast explicit:" << (string)r2 << endl;//cast explicit

	string x = r2;//cast implicit
	cout << "cast implict:" << x << endl;

	//op >>
	cin >> r1;
	cout << r1 << endl;
}
