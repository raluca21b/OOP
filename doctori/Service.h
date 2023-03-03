#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;
public:
	Service() = default;
	Service( Repository& repo) :repo{ repo } {};
	Service(const Service& service) = delete;

	const vector<Doctor> filreazaSectie(string sectie);
	const vector<Doctor> filtreazaNume(string nume);
	const vector<Doctor> filtreazaSectie_Nume(string sectie, string nume);
	vector<Doctor> getAllDoctori();
};
