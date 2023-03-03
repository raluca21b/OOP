#include "domain.h"
#include <assert.h>

int Melodie::getId()const {
	return this->id;
}
string Melodie::getTitlu()const {
	return this->titlu;
}
string Melodie::getArtist()const {
	return this->artist;
}
string Melodie::getGen()const {
	return this->gen;
}

void Melodie::setTitlu(string titlu) {
	this->titlu = titlu;
}
void Melodie::setArtist(string artist) {
	this->artist = artist;
}
void Melodie::setGen(string gen) {
	this->gen = gen;
}

void testeDomain() {
	Melodie melodie{ 1, "B", "C", "pop" };
	assert(melodie.getId() == 1);
	assert(melodie.getTitlu() == "B");
	assert(melodie.getArtist() == "C");
	assert(melodie.getGen() == "pop");

	melodie.setTitlu("X");
	melodie.setArtist("Y");
	melodie.setGen("rock");

	assert(melodie.getTitlu() == "X");
	assert(melodie.getArtist() == "Y");
	assert(melodie.getGen() == "rock");
}