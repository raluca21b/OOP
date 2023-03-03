#pragma once
#include "domain.h"
#include <string>
#include<vector>

using std::vector;

class RepoExceptii {
private:
	string eroare; ///eraore
public:
	RepoExceptii(string eroare) : eroare{ eroare } {};
	/*
	* Returneaza eroarea gasita
	*/
	string getErrorMessage() {
		return this->eroare;
	}
};

class Repo
{
private:
	vector<Melodie> allMelodii;
public:
	Repo() = default;
	Repo(const Repo& repo) = delete;
	/*
	* Adauga o melodie in repo
	* Param intrare: Melodie&
	* Param iesire:
	* Throws: Se arunca exceptie daca melodie existaa deja in lista(se verifica dupa id)
	*/
	virtual void store(const Melodie& melodie);
	/*
	* Returneazaz un vector cu toate melodiile din repo
	* param de iesire: vector de melodii
	*/
	const vector<Melodie>& getAll();
	/*
	* Cauta o melodie dupa id-ul melodiei
	* Param intrare: id-ul melodiei
	* Param iesire: Melodia cu id-ul= id, daca exista melodie
	* altfel se arunca exceptie ca nu exista acea melodie
	*/
	const Melodie& find(int id);
	/*
	* Cauta o melodie dupa id-ul melodiei
	* Param intrare: o melodie
	* Param iesire: 1, daca melodia exista
	*				0, altfel
	*/
	bool exists(const Melodie& melodie);
	/*
	* Sterge o melodie din repo
	* Param intrare: Melodie&
	* Param iesire:
	* Throws: Se arunca exceptie daca melodie existaa deja in lista(se verifica dupa id)
	*/
	virtual void sterge(int id);
};

class RepoFile : public Repo {
private:
	string nume_fisier;		///numele fisierului
	void load_from_file();	///incarca din fisier
	void save_to_file();	///incarca in fisier
public:
	RepoFile(string nume_fisier) :Repo(), nume_fisier{ nume_fisier }{load_from_file();};
	/*
	* Adauga o melodie in fisier
	* Param intrare: Melodie&
	* Param iesire:
	* Throws: Se arunca exceptie daca melodie existaa deja in lista(se verifica dupa id)
	*/
	void store(const Melodie& doctor)override;
	/*
	* Sterge o melodie in fisier
	* Param intrare: Melodie&
	* Param iesire:
	* Throws: Se arunca exceptie daca melodie existaa deja in lista(se verifica dupa id)
	*/
	void sterge(int id) override;
};
void testeRepo();
void testeRepoFile();
