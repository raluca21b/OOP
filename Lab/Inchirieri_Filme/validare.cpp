#include "validare.h"
#include <assert.h>
#include <sstream>

void FilmValidator::validate(const Film& film) {
	vector<string> mesaj;
	if (film.getAnulAparitiei() < 0) mesaj.push_back("Anul nu poate fi negativ!!!");
	if (film.getTitlu().size() == 0) mesaj.push_back("Titlu nu poate fi vid!!!");
	if (film.getGen().size() == 0) mesaj.push_back("Genul nu poate fi vid!!!");
	if (film.getActorPrincipal().size() == 0) mesaj.push_back("Numele actorului nu poate fi vid!!!");
	if (mesaj.size() > 0) {
		throw exceptieValidare(mesaj);
	}
}

ostream& operator<<(ostream& out, const exceptieValidare& exceptie) {
	for (const auto& mesaj : exceptie.mesaj) {
		out << mesaj << " ";
	}
	return out;
}

void testValidator() {
	FilmValidator validator;
	Film film{ "","",-1,"" };
	try {
		validator.validate(film);
	}
	catch (const exceptieValidare& exceptie) {
		std::stringstream sout;
		sout << exceptie;
		auto const mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}