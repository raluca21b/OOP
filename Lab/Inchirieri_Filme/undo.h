#pragma once
#include "repo.h"
class UNDO {
public:
	UNDO();
	virtual void undo() = 0;
	virtual ~UNDO();
};

class UndoAdaugare :public UNDO {
private:
	FilmeRepo& filme;
	Film film;
public:
	UndoAdaugare(FilmeRepo& filme, Film film) : filme{ filme }, film{ film }, UNDO() {};
	void undo()override;
	virtual ~UndoAdaugare();

};

class UndoModificare :public UNDO {
private:
	FilmeRepo& filme;
	Film film, film_modificat;
public:
	UndoModificare(FilmeRepo& filme, Film film, Film film_modificat) : filme{ filme }, film{ film }, film_modificat{ film_modificat }, UNDO() {};
	void undo()override;
	virtual ~UndoModificare();
};

class UndoStergere :public UNDO {
private:
	FilmeRepo& filme;
	Film film;
public:
	UndoStergere(FilmeRepo& filme, Film film) : filme{ filme }, film{ film }, UNDO() {};
	void undo()override;
	virtual ~UndoStergere();
};