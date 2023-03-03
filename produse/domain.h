#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Produs {
private:
	int id;
	string nume, tip;
	double pret;
public:
	Produs(int id1, string nume1, string tip1, double pret1) :id{ id1 }, nume{ nume1 }, tip{ tip1 }, pret{ pret1 }{};
	Produs(const Produs& p) :id{ p.getId() }, nume{ p.getNume() }, tip{ p.getTip()}, pret{p.getPret()}{};
	 int getId()const {
		return this->id;
	}
	 string getNume() const {
		return this->nume;
	}
	 string getTip() const{
		return this->tip;
	}
	 double getPret() const {
		return this->pret;
	}
	
	 void setNume(string numeNou) {
		this->nume = numeNou;
	}
	void setTip(string tipNou) {
		this->tip=tipNou;
	}
	void setPret(double pretNou) {
		this->pret = pretNou;
	}
	int getNumarVocale()const {
		int cnt = 0;
		for (int i = 0; i < this->nume.size(); i++)
		{
			if (this->nume[i] == 'a' || this->nume[i] == 'e' || this->nume[i] == 'i' || this->nume[i] == 'o' || this->nume[i] == 'u' || this->nume[i] == 'A' || this->nume[i] == 'E' || this->nume[i] == 'I' || this->nume[i] == 'O' || this->nume[i] == 'U')
				cnt++;
		}
		return cnt;
	}
	Produs& operator=(const Produs& p)
	{
		this->id = p.id;
		this->nume = p.nume;
		this->tip = p.tip;
		this->pret = p.pret;
		return (*this);
	}
	~Produs() = default;
};