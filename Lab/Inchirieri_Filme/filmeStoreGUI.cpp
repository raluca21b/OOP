#include "filmeStoreGUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void filmeStoreGUI::initializeGUIComponents()
{
	//main layout
	QHBoxLayout* layoutMain = new QHBoxLayout;
	this->setLayout(layoutMain);


	//left part of the window, pentru care setam layout vertical
	QWidget* left_side = new QWidget;
	QVBoxLayout* layoutLeft = new QVBoxLayout;
	left_side->setLayout(layoutLeft);

	QWidget* forma = new QWidget;
	QFormLayout* layoutForma = new QFormLayout;
	forma->setLayout(layoutForma);
	editTitlu = new QLineEdit;
	editGen = new QLineEdit;
	editAn = new QLineEdit;
	editActor = new QLineEdit;

	editTitluModificare = new QLineEdit;
	editGenModificare = new QLineEdit;
	editAnModificare = new QLineEdit;
	editActorModificare = new QLineEdit;

	layoutForma->addRow(labelTitlu, editTitlu);
	layoutForma->addRow(labelGen, editGen);
	layoutForma->addRow(labelAn, editAn);
	layoutForma->addRow(labelActor, editActor);
	layoutForma->addRow(labelTitluModif, editTitluModificare);
	layoutForma->addRow(labelGenModif, editGenModificare);
	layoutForma->addRow(labelAnModif, editAnModificare);
	layoutForma->addRow(labelActorModif, editActorModificare);
	buton_adauga = new QPushButton("Adauga film");
	layoutForma->addWidget(buton_adauga);
	buton_modifica = new QPushButton("Modifica film");
	layoutForma->addWidget(buton_modifica);
	buton_sterge = new QPushButton("Sterge film");
	layoutForma->addWidget(buton_sterge);

	//adaugam toate componentele legate de adaugare oferta in layout-ul care corespunde partii din stanga a ferestrei
	layoutLeft->addWidget(forma);



	//cream un GroupBox pentru radiobuttons care corespund criteriilor de sortare pe care le avem + butonul de sortare
	QVBoxLayout* layoutRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(layoutRadioBox);
	layoutRadioBox->addWidget(radioSortTitlu);
	layoutRadioBox->addWidget(radioSortActor);
	layoutRadioBox->addWidget(radioSortAnGen);

	buton_sorteaza = new QPushButton("Sorteaza Filme");
	layoutRadioBox->addWidget(buton_sorteaza);

	//adaugam acest grup in partea stanga, dupa componentele pentru adaugare in layout-ul vertical
	layoutLeft->addWidget(groupBox);

	//cream un form pentru filtrari
	QWidget* formaFiltrari = new QWidget;
	QFormLayout* layoutFormaFiltrari = new QFormLayout;
	formaFiltrari->setLayout(layoutFormaFiltrari);

	editFiltrareTitlu = new QLineEdit();
	layoutFormaFiltrari->addRow(labelCriteriuFiltrare, editFiltrareTitlu);
	buton_filtrare1 = new QPushButton("Filtreaza filme dupa titlu");
	layoutFormaFiltrari->addWidget(buton_filtrare1);

	editFiltrareAnAparitie = new QLineEdit();
	layoutFormaFiltrari->addRow(labelCriteriuFiltrare2, editFiltrareAnAparitie);
	buton_filtrare2 = new QPushButton("Filtreaza filme dupa anul aparitiei");
	layoutFormaFiltrari->addWidget(buton_filtrare2);

	layoutLeft->addWidget(formaFiltrari);

	//Buton folosit pentru a reincarca datele; afisam toate oferte in tabel, in ordinea initiala din fisier
	buton_reload_data = new QPushButton("Reload data");
	layoutLeft->addWidget(buton_reload_data);
	
	butonRomantic = new QPushButton("Romantic");
	butonActiune = new QPushButton("Actiune");
	butonDrama = new QPushButton("Drama");
	butonHorror = new QPushButton("Horror");
	butonAltGen = new QPushButton("Alt gen");
	layoutLeft->addWidget(butonRomantic);
	layoutLeft->addWidget(butonActiune);
	layoutLeft->addWidget(butonDrama);
	layoutLeft->addWidget(butonHorror);
	layoutLeft->addWidget(butonAltGen);
	
	int contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "romantic")
			contor++;
	if (contor == 0)
		butonRomantic->setVisible(false);
	else
		butonRomantic->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "actiune")
			contor++;
	if (contor == 0)
		butonActiune->setVisible(false);
	else
		butonActiune->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "drama")
			contor++;
	if (contor == 0)
		butonDrama->setVisible(false);
	else
		butonDrama->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "horror")
			contor++;
	if (contor == 0)
		butonHorror->setVisible(false);
	else
		butonHorror->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() != "romantic" &&
			service.preia_toate_filmele().at(i).getGen() != "actiune" &&
			service.preia_toate_filmele().at(i).getGen() != "drama" &&
			service.preia_toate_filmele().at(i).getGen() != "horror")
			contor++;
	if (contor == 0)
		butonAltGen->setVisible(false);
	else
		butonAltGen->setVisible(true);
	
	buton_undo= new QPushButton("Undo");
	layoutLeft->addWidget(buton_undo);

	buton_Cos = new QPushButton("Cos");
	adauga_in_cos = new QPushButton("Adauga film in cos");
	titluFilm = new QLineEdit;
	genereazaRandomInCos = new QPushButton("Adauga filme random in cos");
	editRandom = new QLineEdit;
	golesteCos = new QPushButton("Goleste cos");
	editExport = new QLineEdit;
	this->listaCos = new QListWidget();
	exportCos = new QPushButton("Export cos");

	//componenta right - contine doar tabelul cu oferte
	QWidget* right_side = new QWidget;
	QVBoxLayout* layoutRight = new QVBoxLayout;
	right_side->setLayout(layoutRight);

	int noLines = 10;
	int noColumns = 4;
	this->tabelFilme= new QTableWidget{ noLines, noColumns };

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Ttilu" << "Gen" << "An aparitie" << "Actor principal";
	this->tabelFilme->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tabelFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	layoutRight->addWidget(tabelFilme);

	this->listaFilme = new QListWidget();
	layoutRight->addWidget(listaFilme);

	layoutRight->addWidget(buton_Cos);

	layoutMain->addWidget(left_side);
	layoutMain->addWidget(right_side);
}

void filmeStoreGUI::connectSignalsSlots()
{
	QObject::connect(buton_adauga, &QPushButton::clicked, this, &filmeStoreGUI::guiAdaugaFilm);
	QObject::connect(buton_modifica, &QPushButton::clicked, this, &filmeStoreGUI::guiModificaFilm);
	QObject::connect(buton_sterge, &QPushButton::clicked, this, &filmeStoreGUI::guiStergeFilm);

	QObject::connect(buton_undo, &QPushButton::clicked, [&]() {
		try {
			this->service.undo();
			this->reloadLista(this->service.preia_toate_filmele());
			QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes."));
		}
		catch (FilmRepoExceptii& exceptie) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessage()));
		}
		});


	QObject::connect(buton_sorteaza, &QPushButton::clicked, [&]() {
		if (this->radioSortTitlu->isChecked())
			this->reloadLista(service.sorteazaDupaTitlu());
		else if (this->radioSortActor->isChecked())
			this->reloadLista(service.sorteazaDupaActor());
		else if (this->radioSortAnGen->isChecked())
			this->reloadLista(service.sorteazaDupaAnSiGen());
		});

	QObject::connect(buton_filtrare1, &QPushButton::clicked, [&]() {
		string titlu_filtrare = this->editFiltrareTitlu->text().toStdString();
		this->reloadLista(service.filtrareTitlu(titlu_filtrare));
		});

	QObject::connect(buton_filtrare2, &QPushButton::clicked, [&]() {
		string an_filtrare = this->editFiltrareAnAparitie->text().toStdString();
		this->reloadLista(service.filtrareAnAparitie(stoi(an_filtrare)));
		});

	QObject::connect(buton_reload_data, &QPushButton::clicked, [&]() {
		this->reloadLista(service.preia_toate_filmele());
		});
	
	QObject::connect(butonRomantic, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < service.preia_toate_filmele().size(); i++)
			if (service.preia_toate_filmele().at(i).getGen() == "romantic")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr filme romantic: %1").arg(cnt));
		});

	QObject::connect(butonActiune, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < service.preia_toate_filmele().size(); i++)
			if (service.preia_toate_filmele().at(i).getGen() == "actiune")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr filme actiune: %1").arg(cnt));
		});

	QObject::connect(butonDrama, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < service.preia_toate_filmele().size(); i++)
			if (service.preia_toate_filmele().at(i).getGen() == "drama")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr filme drama: %1").arg(cnt));
		});

	QObject::connect(butonHorror, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < service.preia_toate_filmele().size(); i++)
			if (service.preia_toate_filmele().at(i).getGen() == "horror")
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr filme horror: %1").arg(cnt));
		});

	QObject::connect(butonAltGen, &QPushButton::clicked, [&]() {
		int cnt = 0;
		for (int i = 0; i < service.preia_toate_filmele().size(); i++)
			if (service.preia_toate_filmele().at(i).getGen() != "romantic" &&
				service.preia_toate_filmele().at(i).getGen() != "actiune" &&
				service.preia_toate_filmele().at(i).getGen() != "drama" &&
				service.preia_toate_filmele().at(i).getGen() != "horror"
				)
				cnt++;
		QMessageBox::information(this, "Info", QString::fromStdString("Nr filme alt_gen: %1").arg(cnt));
		});
	

	QObject::connect(this->listaFilme, &QListWidget::itemSelectionChanged, [&]() {
		int index = this->getSelectedIndex();
		auto lista_filmelor = this->service.preia_toate_filmele();
		if (index >= lista_filmelor.size()) {
			this->editTitlu->clear();
			this->editGen->clear();
			this->editAn->clear();
			this->editActor->clear();
			this->titluFilm->clear();
			return;
		}
		auto film = lista_filmelor.at(index);
		this->editTitlu->setText(QString::fromStdString(film.getTitlu()));
		this->titluFilm->setText(QString::fromStdString(film.getTitlu()));
		this->editGen->setText(QString::fromStdString(film.getGen()));
		this->editAn->setText(QString::fromStdString(std::to_string(film.getAnulAparitiei())));
		this->editActor->setText(QString::fromStdString(film.getActorPrincipal()));
		
		});

	QObject::connect(this->tabelFilme, &QTableWidget::itemClicked, [&]() {
		auto currentIndex = this->tabelFilme->selectionModel()->currentIndex();
		int index = currentIndex.row();
		auto toate_filmele = this->service.preia_toate_filmele();
		if (index >= toate_filmele.size()) {
			this->editTitlu->clear();
			this->editGen->clear();
			this->editAn->clear();
			this->editActor->clear();
			this->titluFilm->clear();
			return;
		}
		auto film = toate_filmele.at(index);
		this->editTitlu->setText(QString::fromStdString(film.getTitlu()));
		this->titluFilm->setText(QString::fromStdString(film.getTitlu()));
		this->editGen->setText(QString::fromStdString(film.getGen()));		
		this->editAn->setText(QString::fromStdString(std::to_string(film.getAnulAparitiei())));
		this->editActor->setText(QString::fromStdString(film.getActorPrincipal()));
		});
	
	QObject::connect(buton_Cos, &QPushButton::clicked, [&]() {
		QWidget* fereastra_cos = new QWidget;
		QFormLayout* layoutcos = new QFormLayout;
		fereastra_cos->setLayout(layoutcos);
			//layoutcos->addWidget(listaFilme);
		titluFilm = new QLineEdit;
		layoutcos->addRow(labelTitluCos , titluFilm);
		layoutcos->addWidget(adauga_in_cos);
		editRandom = new QLineEdit;
		layoutcos->addRow(labelRandom, editRandom);
		layoutcos->addWidget(genereazaRandomInCos);
		layoutcos->addWidget(golesteCos);
		editExport = new QLineEdit;
		layoutcos->addRow(labelExport, editExport);
		layoutcos->addWidget(exportCos);
		layoutcos->addWidget(listaCos);
		fereastra_cos->show();
		});

	QObject::connect(adauga_in_cos, &QPushButton::clicked, [&]() {
		try {
			string titlu = titluFilm->text().toStdString();
			titluFilm->clear();
			this->service.adauga_in_cos(titlu);
			QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat cu succes in cos."));
			this->reloadCos(this->service.filmeDinCos());
		}
		catch (FilmRepoExceptii& eroare) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(eroare.getErrorMessage()));
		}
		});

	QObject::connect(genereazaRandomInCos, &QPushButton::clicked, [&]() {
		try {
			int numar_random = editRandom->text().toInt();
			editRandom->clear();
			int numar = this->service.preia_toate_filmele().size();
			this->service.genereazaCosRandom(numar_random);
			QMessageBox::information(this, "Info", QString::fromStdString("%1 filme adaugate").arg(numar_random));
			this->reloadCos(this->service.filmeDinCos());
		}
		catch (FilmRepoExceptii& eroare) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(eroare.getErrorMessage()));
		}
		});

	QObject::connect(golesteCos, &QPushButton::clicked, [&]() {
		try {
			this->service.goleste_cos();
			QMessageBox::information(this, "Info", QString::fromStdString("Cosul a fost golit"));
			this->reloadCos(this->service.filmeDinCos());
		}
		catch (FilmRepoExceptii& exceptie) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessage()));
		}
		});

	QObject::connect(exportCos, &QPushButton::clicked, [&]() {
		try {
			string fisier = editExport->text().toStdString();
			editExport->clear();
			this->service.export_fisier(fisier);
			QMessageBox::information(this, "Info", QString::fromStdString("Cosul a fost inregistrat in fisierul dat."));
			listaCos->clear();
			this->service.goleste_cos();
			this->reloadCos(this->service.filmeDinCos());
		}
		catch (FilmRepoExceptii& exceptie) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessage()));
		}
		});
}

void filmeStoreGUI::reloadLista(vector<Film> filme)
{
	this->tabelFilme->clearContents();
	this->tabelFilme->setRowCount(filme.size());

	int lineNumber = 0;
	for (auto& film : filme) {
		this->tabelFilme->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
		this->tabelFilme->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
		this->tabelFilme->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(film.getAnulAparitiei())));
		this->tabelFilme->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(film.getActorPrincipal())));
		lineNumber++;
	}
	
	int contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "romantic")
			contor++;
	if (contor == 0)
		butonRomantic->setVisible(false);
	else
		butonRomantic->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "actiune")
			contor++;
	if (contor == 0)
		butonActiune->setVisible(false);
	else
		butonActiune->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "drama")
			contor++;
	if (contor == 0)
		butonDrama->setVisible(false);
	else
		butonDrama->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() == "horror")
			contor++;
	if (contor == 0)
		butonHorror->setVisible(false);
	else
		butonHorror->setVisible(true);

	contor = 0;
	for (int i = 0; i < service.preia_toate_filmele().size(); i++)
		if (service.preia_toate_filmele().at(i).getGen() != "romantic" &&
			service.preia_toate_filmele().at(i).getGen() != "actiune" &&
			service.preia_toate_filmele().at(i).getGen() != "drama" &&
			service.preia_toate_filmele().at(i).getGen() != "horror")
			contor++;
	if (contor == 0)
		butonAltGen->setVisible(false);
	else
		butonAltGen->setVisible(true);

	
	this->listaFilme->clear();
	for (const auto& film : filme) {
		auto item = new QListWidgetItem(
			QString::fromStdString(
				film.getTitlu() + " "
				+ film.getGen() + " "
				+ std::to_string(film.getAnulAparitiei()) + " "
				+ film.getActorPrincipal()
				));
		this->listaFilme->addItem(item);
	}
}

void filmeStoreGUI::reloadCos(vector<Film> filme)
{
	this->listaCos->clear();
	for (const auto& film : filme) {
		auto item = new QListWidgetItem(
			QString::fromStdString(
				film.getTitlu() + " "
				+ film.getGen() + " "
				+ std::to_string(film.getAnulAparitiei()) + " "
				+ film.getActorPrincipal()
				));
		this->listaCos->addItem(item);
	}
}

void filmeStoreGUI::guiAdaugaFilm()
{
	try {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		string actor = editActor->text().toStdString();
		int an_aparitie = editAn->text().toInt();

		editTitlu->clear();
		editGen->clear();
		editActor->clear();
		editAn->clear();

		this->service.adaugaFilm(titlu, gen, an_aparitie,actor);
		this->reloadLista(this->service.preia_toate_filmele());

		QMessageBox::information(this, "Info", QString::fromStdString("Film adaugat cu succes."));

	}
	catch (FilmRepoExceptii& exceptieRepo) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptieRepo.getErrorMessage()));
	}
	catch (exceptieValidare& exceptie) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessages()));
	}
}

void filmeStoreGUI::guiModificaFilm()
{
	try {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		string actor = editActor->text().toStdString();
		int an = editAn->text().toInt();

		editTitlu->clear();
		editGen->clear();
		editActor->clear();
		editAn->clear();

		string titlu_nou = editTitluModificare->text().toStdString();
		string gen_nou = editGenModificare->text().toStdString();
		string actor_nou = editActorModificare->text().toStdString();
		int an_nou = editAnModificare->text().toInt();

		editTitluModificare->clear();
		editGenModificare->clear();
		editActorModificare->clear();
		editAnModificare->clear();


		this->service.modificaFilm(titlu, gen, an, actor,titlu_nou,gen_nou,an_nou,actor_nou);
		this->reloadLista(this->service.preia_toate_filmele());

		QMessageBox::information(this, "Info", QString::fromStdString("Film modificat cu succes."));

	}
	catch (FilmRepoExceptii& exceptieRepo) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptieRepo.getErrorMessage()));
	}
	catch (exceptieValidare& exceptie) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessages()));
	}
}

void filmeStoreGUI::guiStergeFilm()
{

	try {
		string titlu = editTitlu->text().toStdString();
		string gen = editGen->text().toStdString();
		string actor = editActor->text().toStdString();
		int an = editAn->text().toInt();

		editTitlu->clear();
		editGen->clear();
		editActor->clear();
		editAn->clear();

		this->service.StergeFilm(titlu,gen,an,actor);
		this->reloadLista(this->service.preia_toate_filmele());

		QMessageBox::information(this, "Info", QString::fromStdString("Film sters cu succes."));

	}
	catch (FilmRepoExceptii& exceptieRepo) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptieRepo.getErrorMessage()));
	}
	catch (exceptieValidare& exceptie) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(exceptie.getErrorMessages()));
	}
}
