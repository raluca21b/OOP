#pragma once
#include <string>
#include <iostream>

using namespace std;
using std::string;

class Melodie
{
private:
	int id; ///id-ul melodiei
	string titlu;	///titlul melodiei
	string artist;	///artistul melodiei
	string gen;		///genul melodiei

public:
	Melodie(int id, string nume, string tip, string gen) :id{ id }, titlu{ nume }, artist{ tip }, gen{ gen }{};
	Melodie(const Melodie& melodie) :id{ melodie.getId() }, titlu{ melodie.getTitlu() }, artist{ melodie.getArtist() }, gen{ melodie.getGen() } {};
	
	/*
	* Returneaza id-ul unei melodii
	* Param intrare:
	* Param iesire: id-ul melodiei(inntreg)
	*/
	int getId()const;
	/*
	* Returneaza titlul unei melodii
	* Param intrare:
	* Param iesire: titlul melodiei(string)
	*/
	string getTitlu()const;
	/*
	* Returneaza artistul unei melodii
	* Param intrare:
	* Param iesire: artistul melodiei(string)
	*/
	string getArtist()const;
	/*
	* Returneaza genul unei melodii
	* Param intrare:
	* Param iesire: genul melodiei(string)
	*/
	string getGen()const;

	/*
	* Seteaza titlul unei melodii
	* Param intrare: string
	*/
	void setTitlu(string titlu);
	/*
	* Seteaza artistul unei melodii
	* Param intrare: string
	*/
	void setArtist(string artist);
	/*
	* Seteaza genul unei melodii
	* Param intrare: string
	*/
	void setGen(string gen);

	/*
	* Suprascrie operatorul =
	*/
	Melodie& operator=(const Melodie& melodie)
	{
		this->id = melodie.id;
		this->titlu = melodie.titlu;
		this->artist = melodie.artist;
		this->gen = melodie.gen;
		return (*this);
	}
};
void testeDomain();