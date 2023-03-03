#include "Repo.h"
#include <fstream>
#include <iostream>
#include <sstream>

void RepoProdus::store(const Produs& produs)
{
	if (exists(produs)) { throw RepoExceptii("Produsul exista deja"); }
	this->listaProduse.push_back(produs);
}

const vector<Produs>& RepoProdus::getAll()
{
	return this->listaProduse;
}

const Produs& RepoProdus::find(int id)
{
	vector<Produs>::iterator p = std::find_if(this->listaProduse.begin(), this->listaProduse.end(), [=](const Produs& produs)
		{
			return produs.getId() == id;
		});
	if (p != this->listaProduse.end()) return (*p);
	else throw RepoExceptii("Produsul nu exista in lista\n");
}

bool RepoProdus::exists(const Produs& p)
{
	try{
		find(p.getId());
		return true;
	}
	catch (RepoExceptii)
	{
		return false;
	}
}

void RepoFile::load_from_file()
{
	ifstream file(this->nume_fisier);
	if (!file.is_open()) {
		throw RepoExceptii("Cannot open file");

	}
	string line;
	while (getline(file, line))
	{
		int id;
		double pret;
		string nume, tip;
		stringstream linestream(line);
		string current_item;
		int nr = 0;
		while (getline(linestream, current_item, ','))
		{
			if (nr == 0) id = stoi(current_item);
			if (nr == 1) nume = current_item;
			if (nr == 2) tip = current_item;
			if (nr == 3) pret = stod(current_item);
			nr++;
		}
		Produs p{ id, nume, tip, pret };
		RepoProdus::store(p);
	}
	file.close();
}

void RepoFile::save_to_file()
{
	ofstream outputFile(this->nume_fisier);
	if (!outputFile.is_open())
		throw RepoExceptii("Cannot write to file " + nume_fisier);
	for (auto& produs : getAll()) {
		outputFile << produs.getId() << "," << produs.getNume() << "," << produs.getTip() << "," << produs.getPret() << endl;
	}
	outputFile.close();
}

void RepoFile::store(const Produs& p)
{
	RepoProdus::store(p);
	save_to_file();
}
