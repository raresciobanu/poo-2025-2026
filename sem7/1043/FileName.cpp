#include <iostream>
using namespace std;

class CameraHotel {
	string* pFacilitatiCamera;
	string numarCamera;
	int numarFacilitati;
	float pretPerNoapte;

public:

	// constructor fara parametri
	CameraHotel() {
		this->numarCamera = "";
		this->numarFacilitati = 0;
		this->pretPerNoapte = 0;
		this->pFacilitatiCamera = nullptr;
	}

	// Constructor cu 3 parametri + 3 tipuri de validari
	CameraHotel(string* pFacilitatiCamera, int numarFacilitati, string numarCamera) {
		if (pFacilitatiCamera == nullptr) {
			throw exception("pFacilitaiCamera nu poate fi nullptr");
		}

		if (numarFacilitati <= 0) {
			throw exception("numarFacilitati nu poate fi < 0");//prefer asta
		}


		if (numarCamera.empty()) {
			throw exception("numarCamera nu poate fi gol");
		}

		this->numarCamera = numarCamera;
		this->numarFacilitati = numarFacilitati;
		this->pretPerNoapte = 190.99;
		this->pFacilitatiCamera = new string[numarFacilitati];
		for (int i = 0; i < numarFacilitati; i++) {
			this->pFacilitatiCamera[i] = pFacilitatiCamera[i];
		}
	}

	//constructor de copiere
	CameraHotel(const CameraHotel& c) {
		this->numarCamera = c.numarCamera;
		this->numarFacilitati = c.numarFacilitati;
		this->pretPerNoapte = c.pretPerNoapte;

		this->pFacilitatiCamera = new string[c.numarFacilitati];
		for (int i = 0; i < numarFacilitati; i++) {
			this->pFacilitatiCamera[i] = pFacilitatiCamera[i];
		}
	}

	// supraincarcare operator =
	CameraHotel& operator=(const CameraHotel& c) {
		if (this != &c) {
			this->numarCamera = c.numarCamera;
			this->numarFacilitati = c.numarFacilitati;
			this->pretPerNoapte = c.pretPerNoapte;

			delete[] this->pFacilitatiCamera;//evitare memory leaks

			this->pFacilitatiCamera = new string[c.numarFacilitati];
			for (int i = 0; i < numarFacilitati; i++) {
				this->pFacilitatiCamera[i] = pFacilitatiCamera[i];
			}
		}

		return *this;
	}

	~CameraHotel() {
		delete[] this->pFacilitatiCamera;// eliberare memorie, evitare memory leak
	}

	// supraincarcare operator <<
	friend ostream& operator<<(ostream& afisareConsola, const CameraHotel& c) {
		afisareConsola << "Numar camera: " << c.numarCamera << "pretPerNoapte:" << c.pretPerNoapte;
		for (int i = 0; i < c.numarFacilitati; i++) {
			afisareConsola << c.pFacilitatiCamera[i] << " ";
		}
		return afisareConsola;
	}

	float getPretPerNoapte() {
		return pretPerNoapte;
	}
	// setter cu validare
	void setPretPerNoapte(float pretPerNoapte) {
		if (pretPerNoapte <= 40) {
			throw exception("pretPerNoapte trebuie sa fie minim 40 lei");
		}
		this->pretPerNoapte = pretPerNoapte;
	}

	string operator[](int index) {
		if (index >= 0 && index < numarFacilitati) {
			return pFacilitatiCamera[index];
		}
		else {
			throw exception("index not in bound");
		}
	}

	// c1+="dus"
	void operator+=(string facilitate) {
		string* aux = new string[numarFacilitati + 1];
		for (int i = 0; i < numarFacilitati; i++) {
			aux[i] = pFacilitatiCamera[i];
		}

		delete[] pFacilitatiCamera;

		aux[numarFacilitati] = facilitate;
		numarFacilitati++;
		this->pFacilitatiCamera = aux;
	}
};

void main() {
	CameraHotel c1;
	string facilitati1[3] = { "aer conditionat","frigider","pat" };


	CameraHotel c2(facilitati1, 3, "201");
	cout << c1 << endl;
	cout << c2 << endl;
	CameraHotel c3(c2);
	c1 = c3;
	c1.setPretPerNoapte(250.50);
	cout << c1.getPretPerNoapte() << endl;
	cout << c3 << endl;
	cout << c1 << endl;
	cout << c1[1] << endl;
	c1 += "carte";
	cout << c1 << endl;
}