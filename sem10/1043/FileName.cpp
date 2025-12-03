#include<iostream>

using namespace std;

class Elev {
	int nrNote;
	float* pNote;
	string nume;
	int nrAbsente;
public:

	Elev() {
		this->nrNote = 0;
		this->pNote = nullptr;
		this->nume = "";
		this->nrAbsente = 0;
	}

	Elev(int nrNote, float* pNote, string nume, int nrAbsente) {
		this->nrNote = nrNote;

		this->pNote = new float[nrNote];

		for (int i = 0; i < nrNote; i++) {
			this->pNote[i] = pNote[i];
		}

		this->nume = nume;

		this->nrAbsente = nrAbsente;
	}

	Elev(const Elev& v) {
		this->nrNote = v.nrNote;

		this->pNote = new float[v.nrNote];

		for (int i = 0; i < v.nrNote; i++) {
			this->pNote[i] = v.pNote[i];
		}

		this->nume = v.nume;

		this->nrAbsente = v.nrAbsente;
	}

	Elev& operator=(const Elev& v) {
		if (this != &v) {
			this->nrNote = v.nrNote;

			delete[] this->pNote; //evitare memory leaks

			this->pNote = new float[v.nrNote];

			for (int i = 0; i < v.nrNote; i++) {
				this->pNote[i] = v.pNote[i];
			}

			this->nume = v.nume;

			this->nrAbsente = v.nrAbsente;
		}

		return *this;
	}

	~Elev() {
		delete[] pNote;
	}

	//operatori
	// op unari ++ / -- 


	// op ++ pre incrementare
	Elev& operator++() {
		this->nrAbsente++;
		return *this;
	}

	// op ++ post incrementare
	Elev operator++(int) {
		Elev temp(*this);

		this->nrAbsente++;

		return temp;
	}

	// op -- post decrementare - elimina ultima nota din vector
	Elev operator--(int) {
		Elev temp(*this);

		float* pAux = new float[nrNote - 1];
		for (int i = 0; i < nrNote - 1; i++) {
			pAux[i] = this->pNote[i];
		}

		delete[] this->pNote;

		this->nrNote--;

		this->pNote = pAux;//shallow copy...e ok aici...aux o sa fie distrus cand se termina metoda

		return temp;
	}

	// operator +
	Elev operator+(int nrAbsente) {
		Elev temp(*this);

		temp.nrAbsente += nrAbsente;

		return temp;
	}

	// operator +
	int operator+(Elev ev1) {
		return this->nrAbsente + ev1.nrAbsente;
	}

	// operator +
	friend Elev operator+(int nrAbsente, const Elev& e1) {
		Elev temp(e1);

		temp.nrAbsente += nrAbsente;

		return temp;
	}

	// operator <<
	friend ostream& operator<<(ostream& afisareConsola, const Elev& e1) {
		afisareConsola << "Nume: " << e1.nume << " nrAbsente: " << e1.nrAbsente
			<< " nrNote: " << e1.nrNote << " note: ";

		for (int i = 0; i < e1.nrNote; i++) {
			afisareConsola << e1.pNote[i] << " ";
		}

		afisareConsola << endl;

		return afisareConsola;
	}

	// operator >>
	friend istream& operator>>(istream& citireConsola, Elev& e1) {
		char aux[100];
		cout << "Nume: ";  citireConsola.getline(aux, 100);
		e1.nume = aux;

		cout << "NrAbsente: "; citireConsola >> e1.nrAbsente;
		cout << "NrNote: "; citireConsola >> e1.nrNote;
		cout << "Note: \n";

		delete[] e1.pNote; //evitare memory leaks
		e1.pNote = new float[e1.nrNote];
		for (int i = 0; i < e1.nrNote; i++) {
			cout << "Nota[" << i << "] = "; citireConsola >> e1.pNote[i];
		}

		return citireConsola;
	}

	//operator [] (sau index)
	float operator[](int index) {
		if (index >= 0 && index < nrNote) {
			return this->pNote[index];
		}
		else {
			throw exception("index out of bounds: " + index);
		}
	}

	//op !
	bool operator!() {
		return this->nrNote > 0;
	}

	//op cast la int (op de conversie)

	//	explicit operator int() { <-- cand vrei doar explicit
	operator int() { //<-- cand vrei implicit & explicit
		return this->nrAbsente;
	}

	bool operator==(const Elev& v) {
		if (nume != v.nume) {
			return false;
		}
		if (nrAbsente != v.nrAbsente) {
			return false;
		}
		if (nrNote != v.nrNote) {
			return false;
		}

		for (int i = 0; i < nrAbsente; i++) {
			if (this->pNote[i] != v.pNote[i]) {
				return false;
			}
		}

		return true;
	}

	void operator+=(int nrAbsente) {
		this->nrAbsente += nrAbsente;
	}

	void operator+=(float nota) {
		float* pAux = new float[nrNote + 1];
		for (int i = 0; i < nrNote; i++) {
			pAux[i] = this->pNote[i];
		}

		pAux[nrNote] = nota;

		nrNote++;

		delete[] this->pNote;

		this->pNote = pAux;//shallow copy...e ok aici...aux o sa fie distrus cand se termina metoda
	}

	//sterge toate aparitiile notei primite ca input
	void operator-=(float nota) {
		int counter = 0;
		for (int i = 0; i < nrNote; i++) {
			if (this->pNote[i] == nota) {
				counter++;
			}
		}

		if (counter > 0) {
			int k = 0;
			float* pAux = new float[nrNote - counter];

			for (int i = 0; i < nrNote; i++) {
				if (this->pNote[i] != nota) {
					pAux[k++] = this->pNote[i];
				}
			}

			this->nrNote = k;

			delete[] this->pNote;

			this->pNote = pAux;//shallow copy...e ok aici...aux o sa fie distrus cand se termina metoda
		}
	}

	//op functie ()
	int operator()(int nrAbsente) {
		return this->nrAbsente + nrAbsente;
	}

	//creati o functie ce sterge un element de la un index dat.
	void stergeDeLaIndex(int index) {
		if (index < 0 && index >= nrNote) {
			throw exception("index invalid");
		}

		float* pAux = new float[nrNote - 1];

		int k = 0;
		for (int i = 0; i < nrNote; i++) {
			if (i != index) {
				pAux[k++] = this->pNote[i];
			}
		}

		this->nrNote = k;

		delete[] this->pNote;

		this->pNote = pAux;//shallow copy...e ok aici...aux o sa fie distrus cand se termina metoda
	}
};

void main() {
	Elev e1;

	cout << "Operator ++\n";

	cout << e1++ << endl; //post incrementare

	cout << ++e1 << endl; //pre incrementare

	cout << "Operator +\n";

	cout << e1 + 2 << endl; //op + ( Elev + int )

	cout << 3 + e1 << endl; //op + ( int + Elev )

	float note[2] = { 6, 7.6 };
	Elev e2(2, note, "Popescu Ion", 50);

	cout << e1 + e2 << endl;//op + ( Elev + Elev )

	//op index
	cout << "operator index: " << e2[1] << endl;

	//op !
	if (!e2) {
		cout << "e2 are note in pNote" << endl;
	}

	//op conversie
	cout << "cast explicit:" << (int)e2 << endl;//cast explicit

	int x = e2;//cast implicit
	cout << "cast implict:" << x << endl;

	//op >>
	Elev e3;
	//cin >> e3;
	cout << e3 << endl;

	//operator ()
	cout << "op (): " << e3(3) << endl;

	//op +=
	e3 += 2;
	cout << "op +=(int): " << e3 << endl;

	//op +=
	e3 += 10.0f;
	e3 += 10.0f;
	e3 += 10.0f;
	e3 += 10.0f;
	e3 += 10.0f;
	cout << "op +=(float): " << e3 << endl;

	//op --
	cout << "op --: " << e3-- << endl;
	cout << "dupa decrementare e3: " << e3 << endl;

	//op -= - scoate toate aparitiile
	e3 -= 10.0f;
	cout << "op -=(float): " << e3 << endl;

	//op ==
	Elev e4, e5;
	cout << "e4==e5: " << ((e4 == e5) ? "true" : "false") << endl;

	//sterge de la un anumit index
	e3 += 7.7f;
	e3 += 8.8f;
	e3 += 10.0f;
	e3 += 5.5f;
	e3 += 9.3f;
	e3 += 4.5f;

	cout << "inainte de stergere: " << e3 << endl;
	e3.stergeDeLaIndex(3);
	cout << "sterge de la un anumit index: " << e3 << endl;
}