#include<iostream>

using namespace std;

#pragma warning(disable:4996)

void fct1(int a) {
	a = 100;
}

void fct2(int& a) {
	a = 200;
}

enum TipGadget {
	Telefon,
	Tableta,
	Laptop,
	CeasInteligent,
	FRIGIDER = 10, //am scris cu litere mari ca sa poata diferentia compilatorul enumerarea frigider de clasa frigider 
	TELEVIZOR,
	Necunoscut
};

string getTipGadgetAfisatFrumos(TipGadget tipGadget) {
	switch (tipGadget) {
	case Telefon:
		return "Telefon";
	case Tableta:
		return "Tableta";
	case Laptop:
		return "Laptop";
	case CeasInteligent:
		return "CeasInteligent";
	case FRIGIDER:
		return "Frigider";
	case TELEVIZOR:
		return "Televizor";
	case Necunoscut:
		return "Necunoscut";
	default:
		return "Necunoscut";
	}
}

TipGadget getTipGadgetNumarCaEnum(int numar) {
	switch (numar) {
	case Telefon:
		return Telefon;
	case Tableta:
		return Tableta;
	case Laptop:
		return Laptop;
	case CeasInteligent:
		return CeasInteligent;
	case FRIGIDER:
		return FRIGIDER;
	case TELEVIZOR:
		return TELEVIZOR;
	case Necunoscut:
		return Necunoscut;
	default:
		return Necunoscut;
	}
}

// class numeClasa {}; 
class Gadget {
	//by default tot este private daca nu pui un modif de access
	const int ID;
private:
	string marca;
	TipGadget tipGadget;
protected:
	string model;
public:
	double pret;
	static int contor;

	//constr. default
	Gadget() : ID(contor++) {
		this->marca = "marcaDefault";
		this->model = "modelDefault";
		this->pret = 0.0;
		this->tipGadget = Necunoscut;
	}

	Gadget(int ID, string marca, string model, double pret, TipGadget tipGadget) : ID(ID) {
		this->marca = marca;
		this->model = model;
		this->pret = pret;
		this->tipGadget = tipGadget;
	}

	Gadget(int ID, string marca, string model) : ID(ID) {
		this->marca = marca;
		this->model = model;
		this->pret = 0.0;
		this->tipGadget = Necunoscut;
	}

	Gadget(string marca, double pret) : ID(0) {
		this->marca = marca;
		this->model = "modelDefault";
		this->pret = pret;
		this->tipGadget = Necunoscut;
	}

	//constr. copiere
	Gadget(const Gadget& g) :ID(g.ID) {
		this->marca = g.marca;
		this->model = g.model;
		this->pret = g.pret;
		this->tipGadget = g.tipGadget;
	}

	~Gadget() {
		cout << "Gadgetul cu ID: " << ID << " a fost distrus.\n";
	}

	//op =
	// g1=g2
	// g1=(g2=(g3=(g4=(g5=g6))))
	Gadget& operator=(const Gadget& g) {
		if (this != &g) {//verifica daca adresa din this != de adresa var. g...pt a evita g1=g1
			this->marca = g.marca;
			this->model = g.model;
			this->pret = g.pret;
			this->tipGadget = g.tipGadget;
		}

		return *this; //indirectare - va returna ob. de la adresa din this
	}

	int getID() {
		return ID;
	}

	TipGadget getTipGadget() {
		return tipGadget;
	}

	void setTipGadget(TipGadget tipGadget) {
		this->tipGadget = tipGadget;
	}

	string getMarca() {
		return marca;
	}

	void setMarca(string marca) {
		this->marca = marca;
	}

	string getModel() {
		return model;
	}

	void setModel(string model) {
		this->model = model;
	}

	double getPret() {
		return pret;
	}

	void setPret(double pret) {
		this->pret = pret;
	}

	void afisareGadget() {
		cout << "ID: " << ID << " marca: " << marca << " model: " << model << " pret: " << pret <<
			" tipGadget: " << getTipGadgetAfisatFrumos(tipGadget) << endl;
	}

	//cout<<g1;
	//cout<<g1<<"\n"<<g2<<endl;

	// friend - folosit pentru a putea avea acces la zona private/protected din afara clasei curente
	// practic clasa Gadget s a imprietenit cu functia de mai jos => nu mai ai nevoie de getteri cand apelezi informatii private din afara clasei
	friend ostream& operator<<(ostream& afisareConsola, const Gadget& g);
	friend istream& operator>>(istream& citireConsola, Gadget& g);

	// Si poti sa imprietenesti si 2 clase
	// Practic daca ai o Gadget in Persoana ...o sa poti accesa informatia private din Gadget
	//friend class Persoana;

};

int Gadget::contor = 1000;


ostream& operator<<(ostream& afisareConsola, const Gadget& g) {
	afisareConsola << "ID: " << g.ID << " marca: " << g.marca << " model: " << g.model << " pret: " << g.pret <<
		" tipGadget: " << getTipGadgetAfisatFrumos(g.tipGadget) << endl;

	return afisareConsola;
}

istream& operator>>(istream& citireConsola, Gadget& g) {
	cout << "marca: "; citireConsola >> g.marca;
	cout << "model: "; citireConsola >> g.model;
	cout << "pret: "; citireConsola >> g.pret;

	int aux;
	cout << "tipGadget: "; citireConsola >> aux;
	g.tipGadget = getTipGadgetNumarCaEnum(aux);

	return citireConsola;
}

// Frigider is a Gadget
class Frigider : public Gadget {
	int capacitate;     // capacitate în litri
	bool areCongelator; // dacã are compartiment de congelare
public:
	//Constr. default
	Frigider() :Gadget() {
		this->capacitate = 0;
		this->areCongelator = false;
	}

	//Constr Frigider cu toti param fara cei din Gadget
	Frigider(int capacitate, bool areCongelator) :Gadget() {
		this->capacitate = capacitate;
		this->areCongelator = areCongelator;
	}

	//sau Constr Frigider cu toti param si cu cei din Gadget
	Frigider(int capacitate, bool areCongelator, int ID, string marca, string model, double pret, TipGadget tipGadget)
		:Gadget(ID, marca, model, pret, tipGadget) {
		this->capacitate = capacitate;
		this->areCongelator = areCongelator;
	}

	Frigider(const Frigider& f) :Gadget(f) {
		this->capacitate = f.capacitate;
		this->areCongelator = f.areCongelator;
	}

	Frigider& operator=(const Frigider& f) {
		if (this != &f) {
			Gadget::operator=(f);

			this->capacitate = f.capacitate;
			this->areCongelator = f.areCongelator;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& afisareConsola, const Frigider& f) {
		afisareConsola << (Gadget)f;
		afisareConsola << "capacitate: " << f.capacitate << " areCongelator: " << f.areCongelator << endl;
		return afisareConsola;
	}

	friend istream& operator>>(istream& citireConsola, Frigider& f) {
		citireConsola >> (Gadget&)f;
		cout << "capacitate: "; citireConsola >> f.capacitate;
		cout << "areCongelator: "; citireConsola >> f.areCongelator;

		return citireConsola;
	}
};


// Frigider is a Gadget
class Televizor : public Gadget {
	double diagonala;  // diagonala ecranului
	bool smart;        // dacã este Smart TV

public:
	//Constr. default
	Televizor() :Gadget() {
		this->diagonala = 0.0;
		this->smart = false;
	}

	//Constr Televizor cu toti param fara cei din Gadget
	Televizor(double diagonala, bool smart) :Gadget() {
		this->diagonala = diagonala;
		this->smart = smart;
	}

	//sau Constr Televizor cu toti param si cu cei din Gadget
	Televizor(double diagonala, bool smart, int ID, string marca, string model, double pret, TipGadget tipGadget)
		:Gadget(ID, marca, model, pret, tipGadget) {
		this->diagonala = diagonala;
		this->smart = smart;
	}

	Televizor(const Televizor& t) :Gadget(t) {
		this->diagonala = t.diagonala;
		this->smart = t.smart;
	}

	Televizor& operator=(const Televizor& t) {
		if (this != &t) {
			Gadget::operator=(t);

			this->diagonala = t.diagonala;
			this->smart = t.smart;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& afisareConsola, const Televizor& t) {
		afisareConsola << (Gadget)t;
		afisareConsola << "diagonala: " << t.diagonala << " smart: " << t.smart << endl;

		return afisareConsola;
	}

	friend istream& operator>>(istream& citireConsola, Televizor& t) {
		citireConsola >> (Gadget&)t;
		cout << "diagonala: "; citireConsola >> t.diagonala;
		cout << "smart: "; citireConsola >> t.smart;

		return citireConsola;
	}
};

//has-a....Persoana has X gadgets
class Persoana {
	int nrGadgets;
	Gadget* pGadgets;
	char* pNume;
public:
	static string codPostal;//adica toate persoanele traiesc in aceeasi zona

	Persoana() {
		this->nrGadgets = 0;

		this->pGadgets = nullptr;

		this->pNume = new char[strlen("defaultNume") + 1];//+1 pt null terminator \0
		strcpy(this->pNume, "defaultNume");
	}

	Persoana(int nrGadgets, Gadget* pGadgets, const char* pNume) {
		if (nrGadgets < 0) {
			throw "nrGadgets nu poate fi < 0";
		}

		if (pGadgets == nullptr) {
			exception e("pGadgets este nullptr");

			throw e;
		}

		if (pNume == nullptr) {
			throw exception("pNume este nullptr");
		}

		this->nrGadgets = nrGadgets;

		//aici se aloca pe HEAP X gadgets ....si acele gadgets sunt niste obiecte create prin intermediul 
		//constr. default din clasa Gadget...si asta o sa genereze pt fiecare obiect un ID = 0 

		this->pGadgets = new Gadget[this->nrGadgets];
		for (int i = 0; i < this->nrGadgets; i++) {
			this->pGadgets[i] = pGadgets[i];
		}

		this->pNume = new char[strlen(pNume) + 1];
		strcpy(this->pNume, pNume);
	}

	Persoana(const Persoana& p) {
		this->nrGadgets = p.nrGadgets;

		this->pGadgets = new Gadget[this->nrGadgets];
		for (int i = 0; i < this->nrGadgets; i++) {
			this->pGadgets[i] = pGadgets[i];
		}

		this->pNume = new char[strlen(p.pNume) + 1];
		strcpy(this->pNume, p.pNume);
	}

	Persoana& operator=(const Persoana& p) {
		if (this != &p) {
			this->nrGadgets = p.nrGadgets;

			delete[] p.pGadgets;//evitare memory leaks
			this->pGadgets = new Gadget[this->nrGadgets];
			for (int i = 0; i < this->nrGadgets; i++) {
				this->pGadgets[i] = p.pGadgets[i];
			}

			delete[] p.pNume;//evitare memory leaks

			this->pNume = new char[strlen(p.pNume) + 1];
			strcpy(this->pNume, p.pNume);
		}

		return *this;
	}

	~Persoana() {
		cout << "Persoana cu " << nrGadgets << "  gadgets a fost distrusa.\n";

		delete[] this->pGadgets;
		delete[] this->pNume;
	}

	void afisarePersoana() {
		cout << "Persoana " << pNume << " are " << nrGadgets << " gadgets, cod postal: " << codPostal << ":\n";
		for (int i = 0; i < nrGadgets; i++) {
			pGadgets[i].afisareGadget();
		}
	}

	friend ostream& operator<<(ostream& afisareConsola, const Persoana& p);
	friend istream& operator>>(istream& citireConsola, Persoana& p);

	int getNrGadgets() {
		return nrGadgets;
	}

	void setNrGadgets(int nrGadgets) {
		if (nrGadgets < 0) {
			throw "nrGadgets nu poate fi < 0";
		}

		this->nrGadgets = nrGadgets;
	}

	Gadget* getPGadgets() {
		return pGadgets;
	}

	void setPGadgets(int nrGadgets, Gadget* pGadgets) {
		if (nrGadgets < 0) {
			throw "nrGadgets nu poate fi < 0";
		}

		if (pGadgets == nullptr) {
			exception e("pGadgets este nullptr");

			throw e;
		}

		this->nrGadgets = nrGadgets;

		delete[] this->pGadgets;//evitare memory leaks

		this->pGadgets = new Gadget[this->nrGadgets];
		for (int i = 0; i < this->nrGadgets; i++) {
			this->pGadgets[i] = pGadgets[i];
		}
	}

	char* getPNume() {
		return pNume;
	}

	void setPNume(char* pNume) {
		if (pNume == nullptr) {
			throw exception("pNume este nullptr");
		}

		delete[] this->pNume;//evitare memory leaks

		this->pNume = new char[strlen(pNume) + 1];
		strcpy(this->pNume, pNume);
	}
};

//initializare default pt o var statica
string Persoana::codPostal = "123456";

ostream& operator<<(ostream& afisareConsola, const Persoana& p) {
	afisareConsola << "Persoana " << p.pNume << " are " << p.nrGadgets << " gadgets, cod postal " << p.codPostal << ":\n";
	for (int i = 0; i < p.nrGadgets; i++) {
		afisareConsola << p.pGadgets[i];
	}

	return afisareConsola;
}

istream& operator>>(istream& citireConsola, Persoana& p) {
	cout << "Citire persoana:\n";
	cout << "Nume:";

	char aux[100];
	citireConsola.getline(aux, 100);
	delete[] p.pNume;//evitare memory leaks

	p.pNume = new char[strlen(aux) + 1];
	strcpy(p.pNume, aux);

	cout << "Nr Gadgets: "; citireConsola >> p.nrGadgets;

	cout << "Introdu gadgets-urile:\n";
	delete[] p.pGadgets;//evitare memory leaks

	p.pGadgets = new Gadget[p.nrGadgets];

	for (int i = 0; i < p.nrGadgets; i++) {
		cout << "Gadget " << i + 1 << ":\n";
		citireConsola >> p.pGadgets[i];
	}

	return citireConsola;
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

void main() {

	//Constr. cu toti parametrii
	Gadget g1(10, "Huawei", "X1", 333.55, Telefon);

	cout << g1.pret << " " << g1.getID() << " " << g1.getMarca() << endl;

	//Constr. default;
	Gadget g2;
	g2.afisareGadget();

	//Constr. cu 2 param;
	Gadget g3("Samsung", 2999.99);
	g3.afisareGadget();

	//Constr. cu 3 param;
	Gadget g4(99, "Apple", "X9");
	g4.afisareGadget();

	cout << "\n\n\n Constr copiere si op =\n";

	//Contr. copiere
	Gadget g5 = g4;
	g5.afisareGadget();

	Gadget g6(g4);
	g6.afisareGadget();

	//Op egal
	Gadget g7;
	g7 = g3;
	g7.afisareGadget();

	cout << "\n\n\n-----Persoana-----\n\n\n";

	//const char* p; //<- un pointer ce pointeaza catre un sir de caractere CONSTANT din memorie;
	//char const* p; //<- un pointer CONSTANT ce pointeaza catre un sir de caractere din memorie;
	//const char const* p; //<- un pointer CONSTANT ce pointeaza catre un sir de caractere CONSTANT din memorie;

	try {
		Persoana pEroare(0, nullptr, nullptr);
	}
	catch (const char* err) {
		cout << "Eroare: " << err << endl << endl;
	}
	catch (exception &err) {
		cout << "Eroare: " << err.what() << endl << endl;
	}

	//Persoana
	Gadget gadgets[5] = { g1,g3,g4,g5,g7 };
	Persoana p1(5, gadgets, "Popescu Vasile");
	p1.afisarePersoana();

	Persoana p2;
	cout << p2.getPNume() << endl;
	p2.codPostal = "2222222";
	cin >> p2;
	cout << endl << p2 << endl;

	cout << "\n\n\n---op <<---\n\n\n";
	cout << p1;

	cout << "==== op Gadget >> ====\n";
	Gadget g10;
	cin >> g10;
	cout << g10;
	cout << "\n\n\n";

	cout << "==== operatii pe Frigider constr, >> si << ====\n";
	Frigider f11;
	Frigider f12(40, true, 2001, "LG", "M1", 2999.99, FRIGIDER);

	cin >> f11;
	cout << f11;
	cout << f12;
	cout << "\n\n\n";


	cout << "==== operatii pe Televizor constr, >> si << ====\n";
	Televizor tv1;
	Televizor tv2(15.55, true, 2001, "Samsung", "X22", 1622.29, TELEVIZOR);

	cin >> tv1;
	cout << tv1;
	cout << tv2;
	cout << "\n\n\n";

	cout << "\n\n\n---program end---\n\n\n";
}