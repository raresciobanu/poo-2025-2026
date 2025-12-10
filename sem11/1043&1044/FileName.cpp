#include<iostream>
#include <string>

using namespace std;

class NrVietiException : public exception {
public:
	char const* what() const {
		return "Error: Ati introdus nrVieti gresit.";
	}
};

class MaxVietiException : public exception {
public:
	char const* what() const {
		return "Error: Ati introdus mai mult de 9 vieti.";
	}
};

// Polimorfism = override & overload 

// Interfete - o interfata este o clasa ce contine doar fct virtuale pure
class IAfisare {
public:
	virtual void afisare() = 0;
};


// Clasa de baza - clasa abstracta -> pt ca are cel putin o fct virtuala pura
// Clasele abstracte NU pot fi instantiate.
class Animal : public IAfisare {
	int nrVieti;
public:
	Animal(int nrVieti) {
		if (nrVieti < 1) {
			throw NrVietiException();
		}

		if (nrVieti > 9) {
			throw new MaxVietiException();
		}

		this->nrVieti = nrVieti;
	}

	virtual void makeSound() {         // funcție virtuală (pentru a suprascrie o fct)
		cout << "Un animal scoate un sunet.\n";
	}

	virtual void move() = 0; //fct virtuala pura - esti obligat sa o impl in clasele derivate
};

// Clasa derivată 1
class Dog : public Animal {
public:
	Dog() :Animal(1) {
	}

	Dog(int nrVieti) :Animal(nrVieti) {
	}

	void makeSound() override {
		cout << "Cainele latra: Ham Ham!\n\n";
	}

	void move() override {
		cout << "Cainele alearga.\n\n";
	}

	void afisare() override {
		cout << "Afisare din Caine.\n\n";
	}
};

// Clasa derivată 2
class Cat : public Animal {
public:

	Cat() :Animal(9) {

	}

	Cat(int nrVieti) :Animal(nrVieti) {

	}

	void makeSound() override {
		cout << "Pisica miauna: Miau Miau!\n\n";
	}

	void move() override {
		cout << "Pisica merge elegant.\n\n";
	}

	void afisare() override {
		cout << "Afisare din Pisica.\n\n";
	}
};

//overload ex:
int suma(int a, int b) {
	return a + b;
}

double suma(double a, double b) {
	return a + b;
}

int main() {
	//polimorfism
	//supraincarcare 
		// => doar numele functiei este la fel si parametrii pot fi in orice ordine si de orice tip
	//suprascriere - se aplica la mostenire
		// => antetul functiei trebuie sa fie acelasi mereu...diferenta este in ce o sa faca metoda (ai nevoie de functii virtuale)

	//early binding - are loc la compilare - reprezinta conceptul de overload - exemplu functia suma de ami sus

	//late binding - are loc la runtime - reprezinta conceptul de override - se aplica la mostenire
	Animal* pAnimal;        // pointer la clasa de bază
	Dog d;
	Cat c;

	pAnimal = &d;           // pointerul arată către un Dog
	pAnimal->makeSound();   // apelează Dog::makeSound()
	pAnimal->move();   // apelează Dog::move()
	pAnimal->afisare();   // apelează Dog::afisare()

	cout << "\n\n==========\n\n";

	pAnimal = &c;           // pointerul arată către un Cat
	pAnimal->makeSound();   // apelează Cat::makeSound()
	pAnimal->move();   // apelează Cat::move()
	pAnimal->afisare();   // apelează Cat::afisare()

	cout << "\n\n==========\n\n";

	//testare exceptie custom - fara a testa si conceptul de polimorfism
	try {
		Dog bb(-32);
	}
	catch (NrVietiException ex) {
		cout << ex.what() << endl;
	}

	//testare exceptie custom - prin pointeri pentru a testa si conceptul de polimorfism pe exceptii custom
	try {
		Cat cc(12);
	}
	catch (exception* ex) {
		cout << ex->what() << endl;
	}

	Dog dog1;
	Dog dog2;
	Dog dog3;
	Cat cat1;
	Cat cat2;


	cout << "\n\n===VECTOR DE POINTERI & POLYMORFISM===\n\n";
	Animal** pCatreVectorDePointeri = new Animal * [5];
	Animal* pA1 = &dog1;
	Animal* pA2 = &dog2;
	Animal* pA3 = &dog3;
	Animal* pA4 = &cat1;
	Animal* pA5 = &cat2;
	pCatreVectorDePointeri[0] = pA1;
	pCatreVectorDePointeri[1] = pA2;
	pCatreVectorDePointeri[2] = pA3;
	pCatreVectorDePointeri[3] = pA4;
	pCatreVectorDePointeri[4] = pA5;

	for (int i = 0; i < 5; i++) {
		pCatreVectorDePointeri[i]->afisare();
	}
	
	//dezalocare memorie
	delete[] pCatreVectorDePointeri;

	return 0;
}