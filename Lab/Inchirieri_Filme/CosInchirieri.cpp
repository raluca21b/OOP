#include "CosInchirieri.h"
using std::shuffle;
#include <fstream>

void CosInchirieri::adaugaCos(const Film& film)
{
    this->cos.push_back(film);
}

void CosInchirieri::golesteCos()
{
    this->cos.clear();
}

bool gasit(vector<Film> listaFilme, vector<Film> cosFilme) {
    for (auto film : cosFilme)
        if (film.getTitlu() == listaFilme.back().getTitlu())
            return false;
    return true;
}

void CosInchirieri::genereazaRandom(vector<Film> listaFilme, int numarDeGenerat)
{
    shuffle(listaFilme.begin(), listaFilme.end(), std::default_random_engine(std::random_device{}()));
    while (cos.size() < numarDeGenerat && listaFilme.size() > 0) {
        if (gasit(listaFilme, cos) == true) {
            cos.push_back(listaFilme.back());
        }
        listaFilme.pop_back();
    }
}

const vector<Film>& CosInchirieri::toateFilmeleDinCos()
{
    return this->cos;
}

void CosInchirieri::exportaCos(string numeFisier)
{
    std::ofstream fout(numeFisier);
    for (auto& film : cos)
        fout << film.getTitlu() << ":" << film.getGen() << ":" << film.getAnulAparitiei() << ":" << film.getActorPrincipal() << std::endl;
    fout.close();
}
