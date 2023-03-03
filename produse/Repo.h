#pragma once
#include "domain.h"
class RepoExceptii {
private:
	string mesaj;
public:
	RepoExceptii(string eroare) :mesaj{ eroare } {};
	string getMesajEroare() {
		return this->mesaj;
	}
};
class RepoProdus
{
private:
	vector<Produs> listaProduse;
public:
	RepoProdus() = default;
	RepoProdus(const RepoProdus& repo) = delete;
	virtual void store(const Produs&);
	const vector<Produs>& getAll();
	const Produs& find(int id);
	bool exists(const Produs& p);

};

class RepoFile :public RepoProdus {
private:
	string nume_fisier;
	void load_from_file();
	void save_to_file();
public:
	RepoFile(string nume_fisier) : RepoProdus(), nume_fisier{ nume_fisier } { load_from_file(); };
	void store(const Produs& p)override;
};
