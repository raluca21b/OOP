#include "Teste.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "Repository.h"
#include "Service.h"

void test_domain() {
	Doctor doctor("1233", "Pop", "Ion", "chirurgie", 1);
	assert(doctor.getCNP() == "1233");
	assert(doctor.getNume() == "Pop");
	assert(doctor.getPrenume() == "Ion");
	assert(doctor.getSectie() == "chirurgie");
	assert(doctor.getConcediu() == 1);

	doctor.setCNP("2222");
	doctor.setNume("Rus");
	doctor.setPrenume("Maria");
	doctor.setSectie("oncologie");
	doctor.setConcediu(0);

	assert(doctor.getCNP() == "2222");
	assert(doctor.getNume() == "Rus");
	assert(doctor.getPrenume() == "Maria");
	assert(doctor.getSectie() == "oncologie");
	assert(doctor.getConcediu() == 0);
}

void test_repo() {
	Repository repo;
	Doctor doctor{ "12234", "Pop", "Mihai", "pediatrie",0 };
	repo.store(doctor);
	assert(repo.getAll().size() == 1);
	try {
		repo.store(doctor);
		assert(false);
	}
	catch (RepoExceptii) {
		assert(true);
	}
	assert(repo.exists(doctor) == true);
	Doctor doctorfictiv{ "2", "X", "Y", "Unknown",1 };
	assert(repo.exists(doctorfictiv) == false);
	assert(repo.find("12234").getNume() == "Pop");
	try {
		repo.find("22");
		assert(false);
	}
	catch(RepoExceptii)
	{
		assert(true);
	}

}
void test_repo_file() {
	std::ofstream out;
	out.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	out << "2234,Pop,Ana,pediatrie,0\n";
	out << "1222,Ignat,Andrei,ortopedie,1\n";
	out << "1256,Serban,Ilie,chirurgie,0\n";
	out.close();
	
	RepoFile testRepoF{ "test.txt" };
	assert(testRepoF.getAll().size() == 3);
	
	Doctor doctor{ "1901", "Ionescu", "Catalin", "oncologie",0 };

	testRepoF.store(doctor);
	assert(testRepoF.getAll().size() == 4);

}
void test_service() {
	Repository repo;
	Service service { repo };
	Doctor doctor1{ "1901", "Ionescu", "Catalin", "oncologie",0 };
	Doctor doctor2{ "12234", "Pop", "Mihai", "pediatrie",0 };
	Doctor doctor3("1233", "Pop", "Ion", "chirurgie", 1);
	Doctor doctor4("2343", "Pop", "Anca", "chirurgie", 0);
	repo.store(doctor1);
	repo.store(doctor2);
	repo.store(doctor3);
	repo.store(doctor4);

	assert(service.getAllDoctori().size() == 4);
	vector<Doctor> filtrareNume = service.filtreazaNume("Pop");
	assert(filtrareNume.size() == 3);
	assert(filtrareNume.at(0).getNume() == "Pop");
	vector<Doctor> filtrareSectie = service.filreazaSectie("oncologie");
	assert(filtrareSectie.size() == 1);
	assert(filtrareSectie.at(0).getSectie() == "oncologie");
	vector<Doctor> filtrareNumeSectie = service.filtreazaSectie_Nume("chirurgie","Pop");
	assert(filtrareNumeSectie.size() == 2);
	assert(filtrareNumeSectie.at(0).getSectie() == "chirurgie");
	assert(filtrareNumeSectie.at(0).getNume() == "Pop");

}

void test_all()
{
	test_domain();
	test_repo();
	test_repo_file();
	test_service();
}