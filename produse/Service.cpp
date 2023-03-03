#include "Service.h"
#include <map>
#include "Service.h"
#include "algorithm"

vector<Produs> Service::sortLista(vector<Produs> vect)
{
    sort(vect.begin(), vect.end(), [](const Produs& p1, const Produs& p2) {
        return p1.getPret() < p2.getPret();
        });
    return vect;
}

void Service::valideaza(int id, const string& nume, const string& tip, double pret)
{
    for (const auto& p : getAllProduse()) {
        if (p.getId() == id)
            throw ServiceException("Id ul exista deja\n");
    }
    if (nume.empty() && tip.empty() && (pret < 1.0 || pret>100.0))
        throw ServiceException("Numele nu poate fi vid\nTipul nu poate fi vid\nPretul e incorect\n");
    if (nume.empty() && tip.empty())
        throw ServiceException("Numele nu poate fi vid\nTipul nu poate fi vid\n");
    if (tip.empty() && (pret < 1.0 || pret>100.0))
        throw ServiceException("Tipul nu poate fi vid\nPretul e incorect\n");
    if(nume.empty() && (pret < 1.0 || pret>100.0))
        throw ServiceException("Numele nu poate fi vid\nPretul e incorect\n");
    if (nume.empty())
        throw ServiceException("Numele nu poate fi vid\n");
    if (tip.empty())
        throw ServiceException("Tipul nu poate fi vid\n");
    if (pret < 1.0 || pret>100.0)
        throw ServiceException("Pretul e incorect\n");
   
}

void Service::adauga(int id, string nume, string tip, double pret)
{
    valideaza(id, nume, tip, pret);
    repoProduse.store(Produs(id, nume, tip, pret));
    notify();

}

vector<Produs> Service::filtrare(double pret, vector<Produs> vect) {
    vector<Produs> rez;
    copy_if(vect.begin(), vect.end(), back_inserter(rez), [pret](const Produs& p1) {
        return p1.getPret() < pret;
        });
    return rez;
}

int Service::nrTipuri(string tip) {
    int k = 0;
    for (const auto& p : getAllProduse()) {
        if (tip == p.getTip())
            k++;
    }
    return k;
}

map<string, int> Service::getTipuri() {
    map<string, int> rez;
    for (const auto& p : getAllProduse()) {
        rez[p.getTip()]++;
    }
    return rez;
}

