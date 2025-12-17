#include<iostream>

//PT STL:
#include<vector>
#include<list>
#include<map>

using namespace std;

/*
* Template = Sablon
*
* Folosit pentru reutilizarea codului.
* Fct sau clase template - este un mod utilizat de compilator pt a construi automat diverse functii.
*
* class sau typename
*
* La compilare are loc generarea de cod pentru entitatea template creata.
*
*/

template<typename T> T suma(T primulParam, T alDoileaParam) {
	return primulParam + alDoileaParam;
}

//un tip template poate fi definit prin typename / class - fac acelasi lucru...sunt mici diferente (pentru C++ mai avansat)
//recomandat e sa folositi typename (e mai sugestiv si e un good practice)
template<class T, class W> W suma(T primulParam, W alDoileaParam, W alTreilaParam) {
	return primulParam + alDoileaParam + alTreilaParam;
}

template<typename T, typename W, typename Z> Z suma(T primulParam, W alDoileaParam, W alTreilaParam, Z alPatruleaParam) {
	return primulParam + alDoileaParam + alTreilaParam + alPatruleaParam;
}

template<typename T> class VectorCustom {
	int nrElemente;
	T* pElemente;
public:
	VectorCustom(int nrElemente, T* pElemente) {
		this->nrElemente = nrElemente;
		this->pElemente = new T[this->nrElemente];
		for (int i = 0; i < this->nrElemente; i++) {
			this->pElemente[i] = pElemente[i];
		}
	}

	VectorCustom(const VectorCustom& v) {
		this->nrElemente = v.nrElemente;
		this->pElemente = new T[this->nrElemente];
		for (int i = 0; i < this->nrElemente; i++) {
			this->pElemente[i] = v.pElemente[i];
		}
	}

	VectorCustom& operator=(const VectorCustom& v) {
		if (this != &v) {
			this->nrElemente = v.nrElemente;

			delete[] this->pElemente;
			this->pElemente = new T[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++) {
				this->pElemente[i] = v.pElemente[i];
			}
		}

		return *this;
	}

	~VectorCustom() {
		delete[] this->pElemente;
	}

	int getNrElemente() {
		return this->nrElemente;
	}

	void setNrElemente(int nrElemente) {
		this->nrElemente = nrElemente;
	}

	T* getPElemente() {
		return this->pElemente;
	}

	void setPElemente(int nrElemente, T* pElemente) {
		this->nrElemente = nrElemente;

		delete[] pElemente;
		this->pElemente = new T[this->nrElemente];
		for (int i = 0; i < this->nrElemente; i++) {
			this->pElemente[i] = pElemente[i];
		}
	}

	void operator+=(T value) {
		T* pAux = new T[this->nrElemente + 1];
		for (int i = 0; i < this->nrElemente; i++) {
			pAux[i] = this->pElemente[i];
		}

		pAux[this->nrElemente] = value;

		this->nrElemente++;

		delete[] this->pElemente;

		this->pElemente = pAux;
	}

	void operator-=(T value) {
		int counter = 0;
		for (int i = 0; i < this->nrElemente; i++) {
			if (this->pElemente[i] == value) {
				counter++;
			}
		}

		if (counter > 0) {
			T* pAux = new T[this->nrElemente - counter];
			int k = 0;

			for (int i = 0; i < this->nrElemente; i++) {
				if (this->pElemente[i] != value) {
					pAux[k++] = this->pElemente[i];
				}
			}

			delete[] this->pElemente;

			this->nrElemente = this->nrElemente - counter;

			this->pElemente = pAux;
		}
	}


	T operator[](int index) {
		if (index >= 0 && index < nrElemente) {
			return this->pElemente[index];
		}
		else {
			throw exception("index is invalid");
		}
	}

	friend ostream& operator<<(ostream& afisareC, const VectorCustom& v) {
		afisareC << "NrElemente: " << v.nrElemente << endl;

		for (int i = 0; i < v.nrElemente; i++) {
			afisareC << "v[" << i << "] = " << v.pElemente[i] << " ";
		}

		afisareC << endl;

		return afisareC;
	}
};

//CLASE - STL
//-> reprezinta mai multe librarii de clase template standard(standard template library)
//-> acopera principalele structuri de date : vector, lista, stiva, coada, tabela de dispersie(hash - table);
//-> pot fi utilizate fara alte modificari pentru tipuri fundamentale sau definite de programator.

//STL = Containere + ITERATORI + ALGORITMI

//Containere: 
//-> un obiect ce stocheaza alte obiecte si are metode pentru a le accesa;

//TIP CONTAINERE
//-> secventiale : 
		//-> vector;
		//-> list;
		//-> deque; 
//-> asociative(valoare - cheie) :
		//-> set(multime de chei unice, sortate)
		//-> multiset(multime de chei, sortate)
		//-> map(multime valori - chei unice, sortate)
		//-> multimap(multime valori - chei sortate)
//-> adaptive :
		//-> stack 
		//-> queue
		//-> priority_queue


//ITERATORI
	//-> forma generalizata a pointerilor; 
	//-> utilizati pentru a itera prin elementele containerelor
	//-> se comporta ca interfata intre containere si algoritmi
	//-> iteratori predefiniti :
			//-> ostream_iterator; 
			//-> istream_iterator;
			//-> reverse_iterator; 
			//-> insert_iterator;

//ALGORITMI
	//-> functii generice independente de tipul containerului; 
	//-> utilizate pentru a prelucra elementele containerelor
	//-> folosesc iteratori pentru acces la elemente
	//-> functii importante : 
		//-> copy;
		//-> for_each;
		//-> sort;
		//-> find;
		//-> transform

////Mai multe exemple: https://www.sanfoundry.com/cpp-programming-examples-stl/


//pt containerul vector trebuie sa adaugi #include <vector> 
//pt containerul list trebuie sa adaugi #include <list> 
//pt containerul map trebuie sa adaugi #include <map> 
//la fel si pt alte containere...


class Persoana {
	string nume;

public:
	Persoana(string nume) {
		this->nume = nume;
	}

	friend ostream& operator<<(ostream& out, Persoana& p) {
		out << "Nume= " << p.nume << endl;

		return out;
	}
};

void main() {
	cout << suma(10, 20) << endl;
	cout << suma<double>(20.4, 43.45) << endl;
	cout << suma(434.54f, 4399.5423f) << endl;
	cout << suma(10, 43.4343, 5454.5454) << endl;
	cout << suma(10, 22.54, 555.55, 656.65f) << endl << endl << endl;


	VectorCustom<int> v1(6, new int[6] { 10, 20, 30, 10, 10, 44 });
	cout << v1 << endl;

	v1 += 20;

	cout << v1 << endl;

	v1 -= 10;

	cout << v1 << endl;

	cout << v1[2] << endl << endl;


	VectorCustom<char> v2(5, new char[5] { 'R', 'A', 'R', 'E', 'S'});
	cout << v2 << endl;

	v2 += '!';

	cout << v2 << endl;



	cout << "\n\nSTL\n\n";

	//STL
	Persoana p1("Ionica");
	Persoana p2("Iulian");
	Persoana p3("Vlad");

	vector<Persoana> vectorDePersoane;
	vectorDePersoane.push_back(p1);
	vectorDePersoane.push_back(p2);
	vectorDePersoane.push_back(p3);

	//varianta 1 de parcurgere vector
	for (int i = 0; i < vectorDePersoane.size(); i++) {
		cout << vectorDePersoane[i] << endl;
	}

	vectorDePersoane.pop_back();//sterge din vector ultima valoare

	//varianta 2 de parcurgere vector
	cout << "Parcurgere vector fara index [] \n";
	//Poti parcurge un vector si asa:
	for (Persoana j : vectorDePersoane) {
		cout << j << endl;
	}

	//varianta 3 de parcurgere vector
	vector<Persoana>::iterator it1;

	cout << "Iterator VECTOR" << endl;
	//iteratorul este un pointer ce va pointa catre fiecare obiect Persoana din vector
	for (it1 = vectorDePersoane.begin(); it1 != vectorDePersoane.end(); it1++) {
		cout << *it1 << endl;
	}

	//lista
	cout << "\nlista STL\n";
	list<Persoana> listaPersoane;
	list<Persoana>::iterator iteratorListaPersoane;

	listaPersoane.push_back(p1);
	listaPersoane.push_back(p2);
	listaPersoane.push_front(p3);

	for (iteratorListaPersoane = listaPersoane.begin(); iteratorListaPersoane != listaPersoane.end(); iteratorListaPersoane++) {
		cout << *iteratorListaPersoane;
	}

	//map
	cout << "\nmap STL\n";

	//pereche(cheie, valoare)
	map<int, Persoana> mapPersoane;
	map<int, Persoana>::iterator iteratorMapPersoane;

	mapPersoane.insert(pair<int, Persoana>(100, p1));
	mapPersoane.insert(pair<int, Persoana>(200, p2));
	mapPersoane.insert(pair<int, Persoana>(310, p3));

	for (iteratorMapPersoane = mapPersoane.begin(); iteratorMapPersoane != mapPersoane.end(); iteratorMapPersoane++) {
		cout << "La cheia: " << iteratorMapPersoane->first << " se afla valoarea: " << iteratorMapPersoane->second;
	}

	//dimensiunea lui mapPersoane
	cout << "dimensiunea lui mapPersoane: " << mapPersoane.size() << endl;
	cout << "La cheia 200 se afla valoarea " << mapPersoane.find(200)->second << endl;
}