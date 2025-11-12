#include<iostream>

using namespace std;

class Carte {
	char* titlu;
	string autor;
	int anulPublicarii;
	float pret;
	int nrPagini;

public:
	Carte() {
		this->titlu = nullptr;
		this->autor = "";
		this->anulPublicarii = 0;
		this->pret = 0.0;
		this->nrPagini = 0;
	}

	Carte(const char* titlu, string autor, int anulPublicarii, float pret) {
		if (titlu == nullptr) {
			throw exception("titlu nu poate fi nullptr");
		}
		if (autor.empty()) {
			throw exception("autor este empty");
		}
		if (pret < 0) {
			throw exception("pretul nu poate fi negativ");
		}

		this->titlu = new char[strlen(titlu) + 1];
		strcpy(this->titlu, titlu);

		this->autor = autor;
		this->anulPublicarii = anulPublicarii;
		this->pret = pret;
		this->nrPagini = 100;
	}

	Carte(const Carte& c) {
		this->titlu = new char[strlen(c.titlu) + 1];
		strcpy(this->titlu, c.titlu);

		this->autor = c.autor;
		this->anulPublicarii = c.anulPublicarii;
		this->pret = c.pret;
		this->nrPagini = c.nrPagini;
	}

	Carte& operator=(const Carte& c) {
		if (this != &c) {
			delete[] this->titlu;//evitare memory leaks

			this->titlu = new char[strlen(c.titlu) + 1];
			strcpy(this->titlu, c.titlu);

			this->autor = c.autor;
			this->anulPublicarii = c.anulPublicarii;
			this->pret = c.pret;
			this->nrPagini = c.nrPagini;
		}

		return *this;
	}

	~Carte() {
		delete[] this->titlu;//evitare memory leaks;
	}

	friend ostream& operator<<(ostream& afisareConsola, const Carte& c) {
		if (c.titlu != nullptr) {
			afisareConsola << "Titlu: " << c.titlu << " ";
		}

		afisareConsola << "Autor: " << c.autor << " Anul publicarii: "
			<< c.anulPublicarii << " Pret: " << c.pret << " NrPagini: " << c.nrPagini << endl;
		return afisareConsola;
	}

	//cout<<c1>c2; sau if(c1>c2)...do something
	bool operator>(Carte c) {
		return this->anulPublicarii > c.anulPublicarii;
	}

	int getNrPagini() {
		return nrPagini;
	}

	void setNrPagini(int nrPagini) {
		if (nrPagini <= 0) {
			throw exception("nrPagini nu poate fi <=0");
		}

		this->nrPagini = nrPagini;
	}

	void seteazaTitlu(const char* text) {
		if (text == nullptr) {
			throw exception("text nu poate fi nullptr");
		}

		delete[] this->titlu;//evitare memory leaks
		this->titlu = new char[strlen(text) + 1];
		strcpy(this->titlu, text);
	}

};

void main() {
	Carte c1;
	Carte c2("Povestea nr 1", "Popescu Ion", 2020, 224.44);

	cout << c1 << endl;
	cout << c2 << endl;
	c1.seteazaTitlu("Somnoroase Pasarele");
	c1.setNrPagini(222);
	cout << c1 << endl;


	Carte c3(c2);
	cout << c3 << endl;

	Carte c4;
	c4 = c1;
	cout << c4 << endl;

	Carte c5("Povestea nr 133", "Elena Maria", 2024, 1121.44);

	cout << c5 << endl;
	cout << ((c5 > c4) ? "true" : "false") << endl;

}