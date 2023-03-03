#include "GUI.h"

void GUI::initGui() {
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setModel(model);

    this->setLayout(mainLayout);
    table->setFixedHeight(500);
    table->setFixedWidth(500);
    mainLayout->addWidget(table);
   
    QWidget* form = new QWidget;
    QFormLayout* layoutForm = new QFormLayout;
    form->setLayout(layoutForm);
    layoutForm->addRow(lblId, txtId);
    layoutForm->addRow(lblTitlu, txtTitlu);
    layoutForm->addRow(lblTip, txtTip);
    layoutForm->addRow(lblPret, txtPret);
    layoutForm->addWidget(lblPretSld);
    layoutForm->addWidget(sldPret);
    layoutForm->addWidget(btnAdd);

    mainLayout->addWidget(form);

    
    sldPret->setMinimum(1);
    sldPret->setMaximum(100);
    this->setFixedHeight(700);
    this->setFixedWidth(700);
}

void GUI::connectSlots() {
    QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
        if (table->selectionModel()->selectedIndexes().isEmpty())
        {
            txtTitlu->setText("");
            txtPret->setText("");
            txtId->setText("");
            txtTip->setText("");
            return;
        }
        auto row = table->selectionModel()->selectedIndexes().at(0).row();
        txtTitlu->setText(table->model()->data(table->model()->index(row, 1), Qt::DisplayRole).toString());
        txtId->setText(table->model()->data(table->model()->index(row, 0), Qt::DisplayRole).toString());
        txtTip->setText(table->model()->data(table->model()->index(row, 2), Qt::DisplayRole).toString());
        txtPret->setText(table->model()->data(table->model()->index(row, 3), Qt::DisplayRole).toString());
        });
    QObject::connect(btnAdd, &QPushButton::clicked, [this] {
        auto id = txtId->text().toInt();
        auto nume = txtTitlu->text().toStdString();
        auto tip = txtTip->text().toStdString();
        auto pret = txtPret->text().toDouble();
        try {
            service.adauga(id, nume, tip, pret);
        }
        catch (ServiceException& re) {
            QMessageBox::information(this, "Error", QString::fromStdString(re.getMessage()));
        }
        reloadData();
        });
    QObject::connect(sldPret, &QSlider::valueChanged, [this] {

        reloadData();
        });
}

void GUI::reloadData() {
    model->setProduse(service.getAllProduse(), service.filtrare(sldPret->value(), service.getAllProduse()));
}

void GUI::openDyn() {
    auto lst = service.getTipuri();
    for (const auto& el : lst) {
        auto wnd = new AfisTipWindows{ service,el.first,el.second };
        wnd->run();
    }

}

