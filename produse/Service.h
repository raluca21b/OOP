#pragma once
#include <set>
#include "repo.h"
#include "observer.h"
#include<map>
using namespace std;

class ServiceException :public exception {
    string msj;
public:
    ServiceException(string err) :msj{ err } {};
    string getMessage()
    {
        return msj;
    }
};
class Service :public Observable {
private:
    RepoProdus& repoProduse;

public:
    explicit Service(RepoProdus& repo) :repoProduse{ repo } {}
    vector<Produs> sortLista(vector<Produs> vect);
    vector<Produs> getAllProduse() {
        return sortLista(repoProduse.getAll());
    }
    void valideaza(int id, const string& nume, const string& tip, double pret);
    void adauga(int id, string nume, string tip, double pret);
    vector<Produs> filtrare(double pret, vector<Produs> vect);
    int nrTipuri(string tip);
    map<string, int> getTipuri();
};
