#include <QPainter>
#include "GUI.h"
#include "qdebug.h"

void GUI::initGui()
{
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setModel(model);

    this->setLayout(mainLayout);
    mainLayout->addWidget(table);
    mainLayout->addWidget(comps);
    comps->setLayout(compsLayout);

    compsLayout->addWidget(lblTitlu);
    compsLayout->addWidget(txtTitlu);
    compsLayout->addWidget(lblArtist);
    compsLayout->addWidget(txtArtist);
    compsLayout->addWidget(lblGen);
    compsLayout->addWidget(txtGen);
    compsLayout->addWidget(deleteBtn);
    compsLayout->addWidget(addBtn);

    deleteBtn->setText("Delete");
    addBtn->setText("Add");
    lblTitlu->setText("Titlu");
    lblArtist->setText("Artist");
    lblGen->setText("Gen");

}

void GUI::connectSlots() {
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
        if (table->selectionModel()->selectedIndexes().isEmpty()) {
            txtTitlu->setText("");
            txtArtist->setText("");
            txtGen->setText("");
            return;
        }
        auto row = table->selectionModel()->selectedIndexes().at(0).row();
        auto titlu = table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString();
        auto autor = table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString();
        auto gen = table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toString();
        txtTitlu->setText(titlu);
        txtArtist->setText(autor);
        txtGen->setText(gen);
        });
    QObject::connect(addBtn, &QPushButton::clicked, [this] {
        auto titlu = txtTitlu->text().toStdString();
        auto artist = txtArtist->text().toStdString();
        auto gen = txtGen->text().toStdString();
        try {
            srv.add(titlu, artist, gen);
        }
        catch (RepoExceptii& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
        }
        reloadList();
        });
    QObject::connect(deleteBtn, &QPushButton::clicked, [this] {
        if (table->selectionModel()->selectedIndexes().isEmpty()) {
            return;
        }
        auto row = table->selectionModel()->selectedIndexes().at(0).row();
        auto id = table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toInt();
        srv.remove(id);
        reloadList();
        });

}

void GUI::reloadList() {
    model->setMelodii(srv.getAllServ(), srv.artisti(), srv.genuri());
    repaint();

}

void GUI::paintEvent(QPaintEvent* event) {
    QPainter p{ this };
    p.setPen(Qt::darkMagenta);
    int pop = 0, rock = 0, folk = 0, disco = 0;
    for (const auto& m : srv.getAllServ())
    {
        if (m.getGen() == "pop") {
            pop++;
            p.drawEllipse(QPoint(15,15), pop * 8, pop * 8);
        }
        if (m.getGen() == "folk") {
            folk++;
            p.drawEllipse(QPoint(p.device()->width()-15, 15), folk * 8, folk * 8);
        }
        if (m.getGen() == "disco") {
            disco++;
            p.drawEllipse(QPoint(15, p.device()->height()-15), disco * 8, disco * 8);
        }
        if (m.getGen() == "rock") {
            rock++;
            p.drawEllipse(QPoint(p.device()->width()-15, p.device()->height()-15), rock * 8, rock * 8);
        }
    }
}

