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

	Gadget(int ID, string marca, string model, double pret) :ID(ID) {
		this->marca = marca;
		this->model = model;
		this->pret = pret;
	}

	int getID() {
		return this->ID;
	}

	string getMarca() {
		return this->marca;
	}

	void setMarca(string marca) {
		this->marca = marca;
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

	Gadget g1(10, "Huawei", "X1", 333.55);

	cout << g1.pret << "\n" << g1.getID() << " " << g1.getMarca() << endl;
}

