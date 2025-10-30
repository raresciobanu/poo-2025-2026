#include<iostream>

#pragma warning(disable:4996)

using namespace std;

class Restaurant {
	//by default ce scrii intr o clasa e private daca ca nu specifici un modif. de acces
	const int CUI;
private:
	//has A
	string denumire;
protected:
	double nota;
	char* pTelefon;
public:
	static int TVA;

	//constr. default
	Restaurant() :CUI(0) {
		this->denumire = "denumireDefault";
		this->nota = 0.0;
		//pTelefon = nullptr;
		this->pTelefon = new char[strlen("telefonDefault") + 1];
		strcpy(this->pTelefon, "telefonDefault");
	}

	Restaurant(int CUI, string denumire, double nota, char *pTelefon) : CUI(CUI) {
		this->denumire = denumire;
		this->nota = nota;
		this->pTelefon = new char[strlen(pTelefon) + 1];
		strcpy(this->pTelefon, pTelefon);
	}

	//constr. copiere
	Restaurant(const Restaurant &r) : CUI(r.CUI) {
		this->denumire = r.denumire;
		this->nota = r.nota;
		this->pTelefon = new char[strlen(r.pTelefon) + 1];
		strcpy(this->pTelefon, r.pTelefon);
	}

	//r1=r2
	//op. egal
	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			this->denumire = r.denumire;
			this->nota = r.nota;

			//deep copy
			delete[] this->pTelefon; //evitare memory leaks

			this->pTelefon = new char[strlen(r.pTelefon) + 1];
			strcpy(this->pTelefon, r.pTelefon);
		}
		
		return *this;
	}

	~Restaurant() {
		cout << "Sunt in destructor";
		delete[] pTelefon;
	}

	int getCUI() {
		return CUI;
	}

	string getDenumire() {
		return denumire;
	}

	void setDenumire(string denumire) {
		this->denumire = denumire;
	}

	double getNota() {
		return nota;
	}

	void setNota(double nota) {
		this->nota = nota;
	}

	char* getPTelefon() {
		return pTelefon;
	}

	void setTelefon(char* pTelefon) {
		//this->telefon = telefon;//shallow copy

		//deep copy
		delete[] this->pTelefon; //evitare memory leaks

		this->pTelefon = new char[strlen(pTelefon) + 1];
		strcpy(this->pTelefon, pTelefon);
	}

	int getTVA() {
		return TVA;
	}

	void setTVA(int TVA) {
		this->TVA = TVA;
	}
};

int Restaurant::TVA = 19;

void main() {
	Restaurant r1;

}