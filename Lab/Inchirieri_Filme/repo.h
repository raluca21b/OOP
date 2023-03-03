#pragma once
#include "domain.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class FilmeRepo {
protected:
	vector <Film> toate_filmele;
	bool existaFilm(const Film& film) const;
public:
	FilmeRepo() = default;
	FilmeRepo(const FilmeRepo& repo) = delete;

	virtual void adauga_film_repo(const Film& film);
	virtual void modifica_film_repo(const Film& film, const Film& film_modificat);
	virtual void sterge_film_repo(const Film& film);
	virtual const int cauta_film(string titlu, string gen, int an, string actor) const;
	virtual const vector<Film>& lista_tuturor_filmelor();


	virtual void loadRepository() {};
	virtual void saveRepository() {};
	virtual void setPath(std::string cale_fisier) {};
};

class FileRepository :
	public FilmeRepo
{
private:
private:
	std::string nume_fisier;
	void loadFromFile();
	void writeToFile();
public:
	FileRepository(std::string nume_fisier) :FilmeRepo(), nume_fisier{ nume_fisier } {
		loadFromFile();//incarcam datele din fisier
	}
	void adauga_film_repo(const Film& film) override {
		//loadFromFile();
		FilmeRepo::adauga_film_repo(film);//apelam metoda din clasa de baza
		writeToFile();
	}
	void sterge_film_repo(const Film& film) override {
		//loadFromFile();
		FilmeRepo::sterge_film_repo(film);//apelam metoda din clasa de baza
		writeToFile();
	}

};



class FilmRepoExceptii {
protected:
	string eroare;
public:
	FilmRepoExceptii(string eroare) :eroare{ eroare } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const FilmRepoExceptii& exceptie);
	string getErrorMessage() {
		return this->eroare;
	}
};

ostream& operator<<(ostream& out, const FilmRepoExceptii& exceptie);

void testeRepo();