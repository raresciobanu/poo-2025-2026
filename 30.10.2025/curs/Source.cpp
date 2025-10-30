#include<iostream>

using namespace std;

void fct1(int x) {
	x = 100;
}

void fct2(int &x) {
	x = 200;
}

class Vehicul {
	//by default totul este privat
	const int ID;
	//has A
	string culoare;
private:
	double nrKm;
protected:
	double capacitateCilindrica;
public:
	string marca;
	static int contor;

	//constructor default
	Vehicul() : ID(contor++) {
		this->culoare = "defaultCuloare";
		this->nrKm = 0.0;
		this->capacitateCilindrica = 0.0;
		this->marca = "defaultMarca";
	}

	Vehicul(string culoare, double nrKm, string marca) :ID(contor++) {
		this->culoare = culoare;
		this->nrKm = nrKm;
		this->capacitateCilindrica = 2.0;
		this->marca = marca;
	}

	Vehicul(int ID, string culoare, double nrKm, string marca,
		double capacitateCilindrica) :ID(ID) {

		this->culoare = culoare;
		this->nrKm = nrKm;
		this->capacitateCilindrica = capacitateCilindrica;
		this->marca = marca;
	}


	Vehicul(const Vehicul& v) :ID(v.ID) {
		this->culoare = v.culoare;
		this->nrKm = v.nrKm;
		this->capacitateCilindrica = v.capacitateCilindrica;
		this->marca = v.marca;
	}

	//(v1=(v2=v3))
	Vehicul& operator=(const Vehicul& v) {
		if (this != &v) { //verifici sa nu fii pe cazul v1=v1
			this->culoare = v.culoare;
			this->nrKm = v.nrKm;
			this->capacitateCilindrica = v.capacitateCilindrica;
			this->marca = v.marca;
		}
	
		return *this;//indirectare
	}

	//destructor
	~Vehicul() {
		cout << "Obiectul s a distrus";
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

	double getNrKm() {
		return nrKm;
	}

	void setNrKm(double nrKm) {
		this->nrKm = nrKm;
	}

	double getCapacitateCilindrica() {
		return capacitateCilindrica;
	}

	void setCapacitateCilindrica(double capacitateCilindrica) {
		this->capacitateCilindrica = capacitateCilindrica;
	}

	string getMarca() {
		return marca;
	}

	void setMarca(string marca) {
		this->marca = marca;
	}

	int getContor() {
		return contor;
	}

	void setContor(int contor) {
		this->contor = contor;
	}

	//friend class Tir;
	friend ostream& operator<<(ostream& afisareConsola, const Vehicul& v);
};

//cout<<v1<<"\n"<<v2;
//cout<<v1;
ostream& operator<<(ostream& afisareConsola, const Vehicul& v) {
	afisareConsola << "ID: " << v.ID << " marca: " << v.marca << " contor: "
		<< v.contor << " capacitateCilindrica: " << v.capacitateCilindrica
		<< " culoare: " << v.culoare << " nrKm: " << v.nrKm << endl;

	return afisareConsola;
}

int Vehicul::contor = 1000;

//is A
class Motor : public Vehicul {
};

class Tir : public Vehicul {
};

//const char* p; //<- un pointer ce pointeaza catre un sir de caractere CONSTANT din memorie;
//char const* p; //<- un pointer CONSTANT ce pointeaza catre un sir de caractere din memorie;
//const char const* p; //<- un pointer CONSTANT ce pointeaza catre un sir de caractere CONSTANT din memorie;


void main() {
	Vehicul v1;
	v1.getCuloare();

	int* p1 = new int(10);
	int* p2 = new int[10];
}