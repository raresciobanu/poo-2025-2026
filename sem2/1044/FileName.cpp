#include<iostream>

using namespace std;

// class numeClasa {}; 
class Gadget {
	//by default tot este private daca nu pui un modif de access
	const int ID;
private:
	string marca;
protected:
	string model;
public:
	double pret;

	//constr. default
	Gadget() : ID(0) {
		this->marca = "marcaDefault";
		this->model = "modelDefault";
		this->pret = 0.0;
	}

	Gadget(int ID, string marca, string model, double pret) : ID(ID) {
		this->marca = marca;
		this->model = model;
		this->pret = pret;
	}

	Gadget(int ID, string marca, string model) : ID(ID) {
		this->marca = marca;
		this->model = model;
		this->pret = 0.0;
	}

	Gadget(string marca, double pret) : ID(0) {
		this->marca = marca;
		this->model = "modelDefault";
		this->pret = pret;
	}

	//constr. copiere
	Gadget(const Gadget& g) :ID(g.ID) {
		this->marca = g.marca;
		this->model = g.model;
		this->pret = g.pret;
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
		}

		return *this; //indirectare - va returna ob. de la adresa din this
	}

	int getID() {
		return ID;
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
		cout << "ID: " << ID << " marca: " << marca << " model: " << model << " pret: " << pret << endl;
	}
};


//has-a....Persoana has X gadgets
class Persoana {
	int nrGadgets;
	Gadget* pGadgets;

public:

	Persoana(int nrGadgets, Gadget* pGadgets) {
		this->nrGadgets = nrGadgets;

		//aici se aloca pe HEAP X gadgets ....si acele gadgets sunt niste obiecte create prin intermediul 
	    //constr. default din clasa Gadget...si asta o sa genereze pt fiecare obiect un ID = 0 
		this->pGadgets = new Gadget[this->nrGadgets];
		for (int i = 0; i < nrGadgets; i++) {
			this->pGadgets[i] = pGadgets[i];
		}
	}

	~Persoana() {
		cout << "Persoana cu " << nrGadgets << "  gadgets a fost distrusa.\n";

		delete[] this->pGadgets;
	}

	void afisarePersoana(){
		cout << "Persoana are " << nrGadgets << " gadgets:\n";
		for (int i = 0; i < nrGadgets; i++) {
			pGadgets[i].afisareGadget();
		}
	}
};

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
	Gadget g1(10, "Huawei", "X1", 333.55);

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

	//Persoana
	Gadget gadgets[5] = { g1,g3,g4,g5,g7 };
	Persoana p1(5, gadgets);
	p1.afisarePersoana();

	cout << "\n\n\n---program end---\n\n\n";
}