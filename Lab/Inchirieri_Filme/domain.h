#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Film {
	std::string titlu;
	std::string gen;
	int anul_aparitiei;
	std::string actor_principal;
public:
	Film() = default;
	Film(const string titlu, const string gen, int an, const string actor) : titlu{ titlu }, gen{ gen }, anul_aparitiei{ an }, actor_principal{ actor }{}
	Film(const Film& film) : titlu{ film.titlu }, gen{ film.gen }, anul_aparitiei{ film.anul_aparitiei }, actor_principal{ film.actor_principal }{cout << "*"; }
	//~Film();
	string getTitlu() const {
		return titlu;
	}
	string getGen() const {
		return gen;
	}
	int getAnulAparitiei() const {
		return anul_aparitiei;
	}
	string getActorPrincipal() const {
		return actor_principal;
	}
	Film& operator=(const Film& film)
	{
		this->titlu = film.titlu;
		this->gen = film.gen;
		this->anul_aparitiei = film.anul_aparitiei;
		this->actor_principal = film.actor_principal;
		return (*this);
	}
};
bool comparaTitlu(const Film& film1, const Film& film2);
bool comparaActorulPrincipal(const Film& film1, const Film& film2);