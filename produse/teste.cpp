#include "Teste.h"
#include "domain.h"
#include "Repo.h"
#include "Service.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include <sstream>

void test_domain()
{
	Produs o{ 1, "B", "Altele", 100.1 };
	assert(o.getId() == 1);
	assert(o.getNume() == "B");
	assert(o.getTip() == "Altele");
	assert(o.getPret() == 100.1);

	o.setNume("X");
	o.setTip("Y");
	o.setPret(5);

	assert(o.getNume() == "X");
	assert(o.getTip() == "Y");
	assert(o.getPret() == 5);
}

void test_add_repo() {
	RepoProdus repo;
	Produs o1{ 1, "d", "Altele", 10 };
	repo.store(o1);
	assert(repo.getAll().size() == 1);
	try {
		repo.store(o1);
		assert(false);
	}
	catch (RepoExceptii) {
		assert(true);
	}
}

void test_find_repo() {
	Produs o1{ 1, "d", "Altele", 10 };
	Produs o2{ 2, "dAS", "Altele", 410 };
	Produs o3{ 3, "SVS", "Altele", 63 };
	RepoProdus repo;
	repo.store(o1);
	repo.store(o2);
	repo.store(o3);

}

void test_all() {
	test_domain();
	test_add_repo();
	
}
