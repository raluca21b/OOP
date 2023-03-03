#include "domain.h"

bool comparaTitlu(const Film& film1, const Film& film2)
{
	return film1.getTitlu() < film2.getTitlu();
}
bool comparaActorulPrincipal(const Film& film1, const Film& film2)
{
	return film1.getActorPrincipal() < film2.getActorPrincipal();
}