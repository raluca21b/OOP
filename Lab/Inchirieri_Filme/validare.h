#pragma once
#include <string>
#include "domain.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class Exception {
	string mesaj;
public:
	Exception(string mesaj) : mesaj{ mesaj } {
	}

	string getMessage() {
		return mesaj;
	}
};

class exceptieValidare {
	vector<string> mesaj;
public:
	exceptieValidare(const vector<string>& erori) :mesaj{ erori } {}

	friend ostream& operator<<(ostream& out, const exceptieValidare& exceptie);
	string getErrorMessages() {
		string mesaje = "";
		for (const string e : mesaj) {
			mesaje += e + "\n";
		}
		return mesaje;
	}
};

ostream& operator<<(ostream& out, const exceptieValidare& exceptie);

class FilmValidator {
public:
	void validate(const Film& film);
};

void testValidator();