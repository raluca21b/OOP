#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;


class CosInchirieri
{
private:
	vector<Film> cos;
public:
	CosInchirieri() = default;

	void adaugaCos(const Film& Film);

	void golesteCos();
	void genereazaRandom(vector<Film> listaFilme, int numarDeGenerat);

	
	const vector<Film>& toateFilmeleDinCos();

	void exportaCos(string numeFisier);
};

