#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include "service.h"

using std::vector;
using std::string;
class filmeStoreGUI : public QWidget
{
	FilmeService& service;

	QLabel* labelTitlu = new QLabel{ "Titlu film:" };
	QLabel* labelGen = new QLabel{ "Gen film:" };
	QLabel* labelAn = new QLabel{ "An aparitie:" };
	QLabel* labelActor = new QLabel{ "Actor principal:" };

	QLineEdit* editTitlu;
	QLineEdit* editGen;
	QLineEdit* editAn;
	QLineEdit* editActor;

	QLabel* labelTitluModif = new QLabel{ "Titlu nou:" };
	QLabel* labelGenModif = new QLabel{ "Gen nou:" };
	QLabel* labelAnModif = new QLabel{ "An aparitie nou:" };
	QLabel* labelActorModif = new QLabel{ "Actor principal nou:" };

	QLineEdit* editTitluModificare;
	QLineEdit* editGenModificare;
	QLineEdit* editAnModificare;
	QLineEdit* editActorModificare;

	QPushButton* buton_adauga;
	QPushButton* buton_modifica;
	QPushButton* buton_sterge;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortTitlu = new QRadioButton(QString::fromStdString("Titlu"));
	QRadioButton* radioSortActor = new QRadioButton(QString::fromStdString("Actor"));
	QRadioButton* radioSortAnGen = new QRadioButton(QString::fromStdString("An si Gen"));
	QPushButton* buton_sorteaza;

	QLabel* labelCriteriuFiltrare = new QLabel{ "Titlul dupa care se filtreaza:" };
	QLineEdit* editFiltrareTitlu;
	QPushButton* buton_filtrare1;

	QLabel* labelCriteriuFiltrare2 = new QLabel{ "Anul dupa care se filtreaza:" };
	QLineEdit* editFiltrareAnAparitie;
	QPushButton* buton_filtrare2;

	QPushButton* buton_reload_data;

	QPushButton* butonRomantic;
	QPushButton* butonActiune;
	QPushButton* butonDrama;
	QPushButton* butonHorror;
	QPushButton* butonAltGen;

	QPushButton* buton_undo;

	QTableWidget* tabelFilme;
	QListWidget* listaFilme;
	QPushButton* buton_Cos;
	QWidget* fereastra_cos;
	QPushButton* adauga_in_cos;
	QLineEdit* titluFilm;
	QPushButton* genereazaRandomInCos;
	QLineEdit* editRandom;
	QPushButton* golesteCos;
	QListWidget* listaCos;
	QLineEdit* editExport;
	QPushButton* exportCos;
	QLabel* labelRandom = new QLabel{ "Nr filme random: " };
	QLabel* labelTitluCos = new QLabel{ "Titlu : " };
	QLabel* labelExport = new QLabel{ "Nume fisier: " };

	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadLista(vector<Film> filme);
	void reloadCos(vector<Film> filme);
public:
	filmeStoreGUI(FilmeService& service) : service{ service } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadLista(service.preia_toate_filmele());
	}
	int getSelectedIndex() {
		auto currentIndex = this->listaFilme->selectionModel()->currentIndex();
		return currentIndex.row();
	}
	void guiAdaugaFilm();
	void guiModificaFilm();
	void guiStergeFilm();
};

