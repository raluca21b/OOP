#include <iostream>
#include "Service.h"
#include "cassert"
#include <assert.h>

void Service::add(string titlu, string artist, string gen) {
    if (titlu != "" && artist != "" && (gen == "pop" || gen == "rock" || gen == "disco" || gen == "folk"))
        repo.store(Melodie(repo.getAll().size() + 1, titlu, artist, gen));
    else throw RepoExceptii("Genul nu este vid\n");
}

void Service::remove(int id) {
    repo.sterge(id);
}

map<string, int> Service::artisti() {
    map<string, int> rez;
    for (const auto& m : getAllServ()) {
        rez[m.getArtist()]++;
    }
    return rez;
}

map<string, int> Service::genuri() {
    map<string, int> rez;
    for (const auto& m : getAllServ()) {
        rez[m.getGen()]++;
    }
    return rez;

}

vector<Melodie> Service::sortLista(vector<Melodie> vect) {
    sort(vect.begin(), vect.end(), [](const Melodie m1, const Melodie m2) {
        return m1.getArtist() < m2.getArtist();
        });
    return vect;
}

void testService() {

    //add
    Repo repo;
    Service service{ repo };

    service.add("a", "b", "pop");
    service.add("f", "b", "pop");
    service.add("andra", "db", "pop");
    service.add("bianca", "sdbsdfg", "pop");
    assert(service.getAllServ().size() == 4);

    //delete
    service.remove(1);
    assert(service.getAllServ().size() == 3);

    //sortare
    vector<Melodie>sorted = service.sortLista(service.getAllServ());
    assert(sorted.size() == 3);

    //artisti
    map<string, int> mapa = service.artisti();
    assert(mapa["b"] == 1);

    //genuri
    map<string, int> mapa2 = service.genuri();
    assert(mapa2["pop"] == 3);
}