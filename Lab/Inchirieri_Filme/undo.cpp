#include "undo.h"

UNDO::UNDO() {}

UNDO::~UNDO() {}

void UndoAdaugare::undo()
{
	filme.sterge_film_repo(film);
}

UndoAdaugare::~UndoAdaugare() {}

void UndoModificare::undo()
{
	filme.sterge_film_repo(film_modificat);
	filme.adauga_film_repo(film);
}
UndoModificare::~UndoModificare() {}

void UndoStergere::undo()
{
	filme.adauga_film_repo(film);
}

UndoStergere::~UndoStergere() {}