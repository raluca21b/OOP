#include "service.h"
#include "undo.h"
#include <functional>
#include <algorithm>
#include <assert.h>

vector<Film> FilmeService::Sorteaza(bool (*functieComparare)(const Film&, const Film&))
{
	vector<Film> lista{ repository_filme.lista_tuturor_filmelor() };//copie la lista
	for (size_t i = 0; i < lista.size(); i++)
		for (size_t j = i + 1; j < lista.size(); j++)
			if (!functieComparare(lista.at(i), lista.at(j)))
			{
				Film auxiliar_interschimbare = lista.at(i);
				lista.at(i) = lista.at(j);
				lista.at(j) = auxiliar_interschimbare;
			}
	return lista;
}

void FilmeService::adaugaFilm(const string& titlu, const string& gen, int an, const string& actor)
{
	Film film{ titlu,gen,an,actor };
	validator_filme.validate(film);
	repository_filme.adauga_film_repo(film);
	UNDO* operatie_undo = new UndoAdaugare{ repository_filme, film };
	lista_undo.push_back(operatie_undo);
}

void FilmeService::StergeFilm(const string& titlu, const string& gen, int an, const string& actor)
{
	Film film_de_sters{ titlu,gen,an,actor };
	validator_filme.validate(film_de_sters);
	repository_filme.sterge_film_repo(film_de_sters);
	UNDO* operatie_undo = new UndoStergere{ repository_filme, film_de_sters };
	lista_undo.push_back(operatie_undo);

}

void FilmeService::modificaFilm(const string& titlu, const string& gen, int an, const string& actor, const string& titlu_nou, const string& gen_nou, int an_nou, const string& actor_nou)
{
	Film film{ titlu,gen,an,actor };
	Film film_nou{ titlu_nou,gen_nou,an_nou,actor_nou };
	validator_filme.validate(film);
	validator_filme.validate(film_nou);
	repository_filme.modifica_film_repo(film, film_nou);
	UNDO* operatie_undo = new UndoModificare{ repository_filme, film,film_nou };
	lista_undo.push_back(operatie_undo);

}

vector<Film> FilmeService::sorteazaDupaTitlu()
{
	vector<Film> copie_lista = repository_filme.lista_tuturor_filmelor();
	std::sort(copie_lista.begin(), copie_lista.end(), comparaTitlu);
	return copie_lista;
}
vector<Film> FilmeService::sorteazaDupaActor()
{
	vector<Film> copie_lista = repository_filme.lista_tuturor_filmelor();
	std::sort(copie_lista.begin(), copie_lista.end(), comparaActorulPrincipal);
	return copie_lista;
}
vector<Film> FilmeService::sorteazaDupaAnSiGen()
{
	return Sorteaza([](const Film& film1, const Film& film2) {
		if (film1.getAnulAparitiei() == film2.getAnulAparitiei())
		{
			return film1.getGen() < film2.getGen();
		}
		return film1.getAnulAparitiei() < film2.getAnulAparitiei();
		});
}

vector<Film> FilmeService::filtreaza(function<bool(const Film&)> functie)
{
	vector<Film> lista_filtrata;
	for (const auto& film : repository_filme.lista_tuturor_filmelor())
	{
		if (functie(film))
			lista_filtrata.push_back(film);
	}
	return lista_filtrata;
}

vector<Film> FilmeService::filtrareTitlu(string titlu)
{
	return filtreaza([titlu](const Film& film) {return film.getTitlu() == titlu; });
}

vector<Film> FilmeService::filtrareAnAparitie(int an)
{
	return filtreaza([an](const Film& film) {return film.getAnulAparitiei() == an; });
}

void FilmeService::adauga_in_cos(string titlu)
{
	for (const auto& film : repository_filme.lista_tuturor_filmelor())
		if (film.getTitlu() == titlu)
			cos_inchirieri.adaugaCos(film);
}

void FilmeService::goleste_cos()
{
	cos_inchirieri.golesteCos();
}

void FilmeService::genereazaCosRandom(int numarDeGenerat)
{
	cos_inchirieri.genereazaRandom(repository_filme.lista_tuturor_filmelor(), numarDeGenerat);
}

const vector<Film>& FilmeService::filmeDinCos()
{
	return cos_inchirieri.toateFilmeleDinCos();
}

void FilmeService::export_fisier(string nume_fisier)
{
	cos_inchirieri.exportaCos(nume_fisier);
}

void FilmeService::undo()
{
	if (lista_undo.size() == 0)
		return;
	lista_undo[lista_undo.size() - 1]->undo();
	lista_undo.pop_back();
}

void testAdaugareService()
{
	FilmeRepo repository_filme;
	FilmValidator validator_film;
	FilmeService service{ repository_filme,validator_film };
	service.adaugaFilm("Aa", "BB", 1999, "CC");
	assert(service.preia_toate_filmele().size() == 1);

	try {
		service.adaugaFilm("", "", -12, "");
		assert(false);
	}
	catch (exceptieValidare&)
	{
		assert(true);
	}

	try
	{
		service.adaugaFilm("Aa", "BB", 1999, "CC");
		assert(false);
	}
	catch (FilmRepoExceptii&)
	{
		assert(true);
	}
}
void testStergereService()
{
	FilmeRepo repository_filme;
	FilmValidator validator_film;
	FilmeService service{ repository_filme,validator_film };
	service.adaugaFilm("Aa", "BB", 1999, "CC");
	service.adaugaFilm("qq", "ww", 1999, "rr");
	assert(service.preia_toate_filmele().size() == 2);
	service.StergeFilm("Aa", "BB", 1999, "CC");
	assert(service.preia_toate_filmele().size() == 1);
	try {
		service.StergeFilm("II", "AA", 1999, "ZZ");
		assert(false);
	}
	catch (FilmRepoExceptii&)
	{
		assert(true);
	}
}


void testModificare()
{

	FilmeRepo repository_filme;
	FilmValidator validator_film;
	FilmeService service{ repository_filme,validator_film };
	service.adaugaFilm("Aa", "BB", 1999, "CC");
	assert(service.preia_toate_filmele().at(0).getTitlu() == "Aa");
	service.modificaFilm("Aa", "BB", 1999, "CC", "BB", "as", 2000, "pp");
	assert(service.preia_toate_filmele().at(0).getTitlu() == "BB");
}

void testFiltrare()
{
	FilmeRepo repository_filme;
	FilmValidator validator_film;
	FilmeService service{ repository_filme,validator_film };
	service.adaugaFilm("Aa", "BB", 1999, "CC");
	service.adaugaFilm("Aa", "ww", 1998, "rr");
	service.adaugaFilm("sd", "BB", 2000, "CC");
	service.adaugaFilm("qqs", "ww", 1999, "rr");
	assert(service.filtrareAnAparitie(1999).size() == 2);
	assert(service.filtrareTitlu("Aa").size() == 2);
	assert(service.filtrareAnAparitie(2005).size() == 0);
	assert(service.filtrareTitlu("sd").size() == 1);


}
void testSortare()
{
	FilmeRepo repository_filme;
	FilmValidator validator_film;
	FilmeService service{ repository_filme,validator_film };
	service.adaugaFilm("Aa", "BB", 1998, "bb");
	service.adaugaFilm("Aa", "ww", 1998, "aa");
	service.adaugaFilm("sd", "BB", 2000, "cc");
	service.adaugaFilm("qqs", "ww", 1999, "rr");

	Film lista_sortata = service.sorteazaDupaActor().at(0);
	assert(lista_sortata.getTitlu() == "Aa");

	lista_sortata = service.sorteazaDupaTitlu().at(0);
	assert(lista_sortata.getTitlu() == "Aa");

	lista_sortata = service.sorteazaDupaAnSiGen().at(0);
	assert(lista_sortata.getGen() == "BB");
}

void testService()
{
	testAdaugareService();
	testStergereService();
	testFiltrare();
	testSortare();
	testModificare();
}
