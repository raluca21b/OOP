#pragma once
#include <map>
#include "algorithm"
#include "Repo.h"

using namespace std;

class Service {
private:
    Repo& repo;

public:
    explicit Service(Repo& repo) :repo{ repo } {}
    /*
    * Sorteaza o lista de melodii crescator dupa numele artistului
    * Param intrare: vectorul de melodii
    * Param iesire: vectorul sortat
    */
    vector<Melodie> sortLista(vector<Melodie> vect);
    /*
    * Returneaza o lista cu toate melodiile din repo sortate crescator
    * Param intrare: 
    * Param iesire: Vectorul de melodii sortate crescator dupa artist
    */
    vector<Melodie> getAllServ() {
        return sortLista(repo.getAll());
    };
    /*
    * Adauga o melodie in service
    * Param intrare: string titlu, string string artist, string gen
    */
    void add(string titlu, string artist, string gen);
    /*
    * Sterge o melodie in service
    * Param intrare: string titlu, string string artist, string gen
    */
    void remove(int id);
    /*
    * Returneaza un map cu fiecare artist si frecventa acestuia
    * Param intrare: 
    * Param de iesire: map
    */
    map<string, int> artisti();
    /*
   * Returneaza un map cu fiecare gen si frecventa acestuia
   * Param intrare:
   * Param de iesire: map
   */
    map<string, int> genuri();


};
void testService();
