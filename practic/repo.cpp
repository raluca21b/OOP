#include "repo.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
using std::getline;
using std::stod;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::ofstream;

void Repo::sterge(int id)
{
	int i = 0;
	while (i < this->allMelodii.size() && this->allMelodii.at(i).getId() != id) {
		i++;
	}
	if (i < this->allMelodii.size()) this->allMelodii.erase(this->allMelodii.begin() + i);
	else throw RepoExceptii("Melodia nu exista!\n");
}

void Repo::store(const Melodie& melodie)
{
	this->allMelodii.push_back(melodie);
}

const vector<Melodie>& Repo::getAll()
{
	return this->allMelodii;
}

const Melodie& Repo::find(int id)
{
	vector<Melodie>::iterator d = std::find_if(this->allMelodii.begin(), this->allMelodii.end(), [=](const Melodie& doctor)
		{
			return doctor.getId() == id;
		});
	if (d != this->allMelodii.end()) return (*d);
	else throw RepoExceptii("Melodia nu exista in lista\n");
}

bool Repo::exists(const Melodie& d)
{
	try {
		find(d.getId());
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
		throw RepoExceptii("Cannot read from file " + nume_fisier);
	}
	string line;
	while (getline(file, line))
	{
		int id;
		string titlu, artist, gen;
		stringstream linestream(line);
		string current_item;
		int nr = 0;
		while (getline(linestream, current_item, ','))
		{
			if (nr == 0) id = stoi(current_item);
			if (nr == 1) titlu = current_item;
			if (nr == 2) artist = current_item;
			if (nr == 3) gen = current_item;
			nr++;
		}
		Melodie p{ id, titlu, artist, gen };
		Repo::store(p);
	}
	file.close();
}

void RepoFile::save_to_file()
{
	ofstream outputFile(this->nume_fisier);
	if (!outputFile.is_open())
		throw RepoExceptii("Cannot write to file " + nume_fisier);
	for (auto& produs : getAll()) {
		outputFile << produs.getId() << "," << produs.getTitlu() << "," << produs.getArtist() << "," << produs.getGen() << endl;
	}
	outputFile.close();
}

void RepoFile::store(const Melodie& melodie)
{
	Repo::store(melodie);
	save_to_file();
}

void RepoFile::sterge(int id)
{
	Repo::sterge(id);
	save_to_file();
}

void testeRepo()
{
	//add
	Repo repo;
	Melodie o1{ 1, "d", "a", "pop" };
	Melodie o2{ 11, "daa", "aaa", "rock" };
	Melodie o3{ 12, "dbb", "abb", "pop" };
	repo.store(o1);
	repo.store(o2);
	repo.store(o3);

	assert(repo.getAll().size() == 3);
	vector<Melodie>v = repo.getAll();
	assert(v[0].getId() == 1);
	assert(v[0].getTitlu() == "d");
	assert(v[0].getArtist() == "a");
	assert(v[0].getGen() == "pop");

	//delete
	repo.sterge(11);
	vector<Melodie>v1 = repo.getAll();
	assert(v1[1].getId() == 12);
	assert(v1[1].getTitlu() == "dbb");
	assert(v1[1].getArtist() == "abb");
	assert(v1[1].getGen() == "pop");
	repo.sterge(12);
	repo.sterge(1);

	try {
		repo.sterge(1);
		assert(false);
	}
	catch (RepoExceptii) {
		assert(true);
	}

	auto list = repo.getAll();
	assert(list.size() == 0);

	//find
	repo.store(o1);
	assert(repo.exists(o1));
	assert(!repo.exists(o2));
	repo.store(o2);
	repo.store(o3);
	assert(repo.find(1).getTitlu() == o1.getTitlu());
	try {
		repo.find(16);
		assert(false);
	}
	catch (RepoExceptii) {
		assert(true);
	}

}

void testeRepoFile()
{
	std::ofstream ofs;
	ofs.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	ofs << "1,LetItGo,a,pop\n";
	ofs << "2,CampRock,c,rock\n";
	ofs.close();
	RepoFile testRepoF{ "test.txt" };
	assert(testRepoF.getAll().size() == 2);


	auto foundof = testRepoF.find(1);
	assert(foundof.getTitlu() == "LetItGo");
	assert(foundof.getArtist() == "a");
	assert(foundof.getGen() == "pop");

	Melodie of1{6, "E", "Edinburgh", "pop"};

	testRepoF.store(of1);
	assert(testRepoF.getAll().size() == 3);
	Melodie found = testRepoF.find(6);
	assert(found.getGen() == "pop");
}