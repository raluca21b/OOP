#include "repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>

using std::ostream;
using std::stringstream;

const int FilmeRepo::cauta_film(string titlu, string gen, int an, string actor) const {
	int pozitie = 0;
	for (const auto& film : toate_filmele)
	{
		if (film.getTitlu() == titlu && film.getGen() == gen && film.getAnulAparitiei() == an && film.getActorPrincipal() == actor)
			return pozitie;
		pozitie++;
	}
	throw FilmRepoExceptii("Nu exista filmul " + titlu);
}

bool FilmeRepo::existaFilm(const Film& film) const {
	try {
		cauta_film(film.getTitlu(), film.getGen(), film.getAnulAparitiei(), film.getActorPrincipal());
		return true;
	}
	catch (FilmRepoExceptii&)
	{
		return false;
	}
}

void FilmeRepo::adauga_film_repo(const Film& film)
{
	if (existaFilm(film))
	{
		throw FilmRepoExceptii("Exista deja filmul");
	}
	toate_filmele.push_back(film);
}

void FilmeRepo::modifica_film_repo(const Film& film, const Film& film_modificat)
{
	int const pozitie = cauta_film(film.getTitlu(), film.getGen(), film.getAnulAparitiei(), film.getActorPrincipal());
	sterge_film_repo(film);
	toate_filmele.insert(toate_filmele.begin() + pozitie, film_modificat);
}

void FilmeRepo::sterge_film_repo(const Film& film_de_sters)
{
	if (!existaFilm(film_de_sters))
	{
		throw FilmRepoExceptii("Filmul nu exista!");
	}
	int const pozitie = cauta_film(film_de_sters.getTitlu(), film_de_sters.getGen(), film_de_sters.getAnulAparitiei(), film_de_sters.getActorPrincipal());
	toate_filmele.erase(toate_filmele.begin() + pozitie);
}

const vector<Film>& FilmeRepo::lista_tuturor_filmelor()
{
	return toate_filmele;
}

ostream& operator<<(ostream& out, const FilmRepoExceptii& exceptie) {
	out << exceptie.eroare;
	return out;
}

void FileRepository::loadFromFile()
{
	std::ifstream inputFile(this->nume_fisier);
	if (!inputFile.is_open()) {
		throw FilmRepoExceptii("Cannot read from file " + nume_fisier);
	}
	string line;
	while (getline(inputFile, line))
	{
		string titlu, gen, actorPrincipal;
		int anulAparitiei;

		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) titlu = current_item;
			if (item_no == 1) gen = current_item;
			if (item_no == 2) anulAparitiei = stoi(current_item);
			if (item_no == 3) actorPrincipal = current_item;
			item_no++;
		}
		Film film{ titlu, gen,anulAparitiei,actorPrincipal };
		FilmeRepo::adauga_film_repo(film);
	}
	inputFile.close();
}

void FileRepository::writeToFile() {
	std::ofstream fisier_iesire(nume_fisier);
	if (!fisier_iesire.is_open()) {
		std::string mesaj("Unable to open file:");
		throw FilmRepoExceptii(mesaj);
	}
	for (auto& film : lista_tuturor_filmelor()) {
		fisier_iesire << film.getTitlu() << "," << film.getGen() << "," <<  film.getAnulAparitiei() << "," << film.getActorPrincipal();
		fisier_iesire << std::endl;
	}
	fisier_iesire.close();
}


void testAdauga() {
	FilmeRepo repo;
	repo.adauga_film_repo(Film{ "AAA","vvv", 2000,"ala" });
	assert(repo.lista_tuturor_filmelor().size() == 1);
	assert(repo.cauta_film("AAA", "vvv", 2000, "ala") == 0);

	repo.adauga_film_repo(Film{ "BBB","aaa",1999,"zzz" });
	assert(repo.lista_tuturor_filmelor().size() == 2);

	//nu pot adauga 2 cu acelasi tip si specie
	try {
		repo.adauga_film_repo(Film{ "AAA","vvv", 2000,"ala" });
		assert(false);
	}
	catch (const FilmRepoExceptii&) {
		assert(true);
	}
	//cauta inexistent
	try {
		repo.cauta_film("ppp", "qqqq", 22, "xmen");
		assert(false);
	}
	catch (const FilmRepoExceptii& exceptie) {
		stringstream out;
		out << exceptie;
		assert(out.str().find("exista") >= 0);
	}
}

void testCauta() {
	FilmeRepo repo;
	repo.adauga_film_repo(Film{ "AAA","vvv", 2000,"ala" });
	repo.adauga_film_repo(Film{ "BBB","aaa",1999,"zzz" });

	int const pozitie_in_lista = repo.cauta_film("AAA", "vvv", 2000, "ala");
	assert(pozitie_in_lista == 0);

	//arunca exceptie daca nu gaseste
	try {
		repo.cauta_film("AAA", "qqqq", 22, "xmen");
		assert(false);
	}
	catch (FilmRepoExceptii&) {
		assert(true);
	}
}

void testSterge() {
	FilmeRepo repo;
	repo.adauga_film_repo(Film{ "AAA","vvv", 2000,"ala" });
	repo.adauga_film_repo(Film{ "BBB","aaa",1999,"zzz" });

	assert(repo.lista_tuturor_filmelor().size() == 2);
	repo.sterge_film_repo(Film{ "BBB","aaa",1999,"zzz" });
	assert(repo.lista_tuturor_filmelor().size() == 1);

	//arunca exceptie daca nu gaseste
	try {
		repo.sterge_film_repo(Film{ "z","c",12,"z" });
		assert(false);
	}
	catch (FilmRepoExceptii&) {
		assert(true);
	}
}

void testModifica()
{
	FilmeRepo repo;
	repo.adauga_film_repo(Film{ "AAA","vvv", 2000,"ala" });
	assert(repo.lista_tuturor_filmelor().at(0).getTitlu() == "AAA");
	repo.modifica_film_repo(Film{ "AAA","vvv", 2000,"ala" }, Film{ "BBB","vvv", 2000,"ala" });
	assert(repo.lista_tuturor_filmelor().at(0).getTitlu() == "BBB");
}

void testeRepo() {
	testAdauga();
	testCauta();
	testSterge();
	testModifica();
}