#pragma once
#include "domain.h"
#include "repo.h"
#include <string>
#include <vector>
#include "undo.h"
#include <functional>
#include "validare.h"
#include "CosInchirieri.h"
using std::vector;
using std::function;

class FilmeService {
	FilmeRepo& repository_filme;
	FilmValidator& validator_filme;
	vector<UNDO*> lista_undo;

	CosInchirieri cos_inchirieri;

	vector<Film> Sorteaza(bool (*functieComparare)(const Film&, const Film&));
	vector<Film> filtreaza(function<bool(const Film&)> functie);
public:
	FilmeService(FilmeRepo& repo, FilmValidator& valid) noexcept :repository_filme{ repo }, validator_filme{ valid } {
	}
	//nu permitem copierea de obiecte 
	FilmeService(const FilmeService& obiect) = delete;
	/*
	 returneaza toate filmele in ordinea in care au fost adaugate
	*/
	const vector<Film>& preia_toate_filmele() noexcept {
		return repository_filme.lista_tuturor_filmelor();
	}
	/*
	Adauga un nou film
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void adaugaFilm(const string& titlu, const string& gen, int an, const string& actor);

	/*
	Sterge un film
	arunca exceptie daca: nu se poate sterge, nu este valid
	*/
	void StergeFilm(const string& titlu, const string& gen, int an, const string& actor);

	/*
	* Modifica un film
	* arunca exceptie daca nu se poate modifica
	*/
	void modificaFilm(const string& titlu, const string& gen, int an, const string& actor, const string& titlu_nou, const string& gen_nou, int an_nou, const string& actor_nou);
	/*
	Sorteaza dupa titlu
	*/
	vector<Film> sorteazaDupaTitlu();

	/*
	Sorteaza dupa actorPrincipal
	*/
	vector<Film> sorteazaDupaActor();


	/*
	Sorteaza dupa anul aparitiei + gen
	*/
	vector<Film> sorteazaDupaAnSiGen();

	/*
	returneaza doar filmele cu un anumit titlu
	*/
	vector<Film> filtrareTitlu(string titlu);

	/*
	returneaza doar filmele cu un anumit an al aparitiei
	*/
	vector<Film> filtrareAnAparitie(int an);

	void adauga_in_cos(string titlu);
	void goleste_cos();
	void genereazaCosRandom(int numarDeGenerat);
	const vector<Film>& filmeDinCos();
	void export_fisier(string nume_fisier);

	void undo();
};

void testService();