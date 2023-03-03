#include <QWidget>
#include <QTableView>
#include <utility>
#include "QLayout"
#include "QPushButton"
#include "QSlider"
#include "QLineEdit"
#include "QFormLayout"
#include "QLabel"
#include "QMessageBox"
#include "Service.h"
#include "MytableModel.h"
#include "Observer.h"

class AfisTipWindows :public Observer {
private:
    Service& service;
    int nr;
    string tip;
    QLabel* lbl = new QLabel;
    QWidget* window = new QWidget;
    QHBoxLayout* layout = new QHBoxLayout;
public:
    AfisTipWindows(Service& srv, string tip, int nr) :service{ srv }, tip(tip), nr{ nr }{
        this->service.addObserver(this);
        auto txt = to_string(nr);
        lbl->setText(QString::fromStdString(txt));
        window->setWindowTitle(QString::fromStdString(tip));
        window->setLayout(layout);
        layout->addWidget(lbl);
       
    }
    ~AfisTipWindows() {
        this->service.removeObserver(this);
    }
    void update() override {
        nr = service.nrTipuri(tip);
        auto txt = to_string(nr);
        lbl->setText(QString::fromStdString(txt));
    }
    void run() {
        window->setFixedWidth(200);
        window->show(); }
};

class GUI : public QWidget {
private:
    Service& service;

    QHBoxLayout* mainLayout = new QHBoxLayout;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel{ service.getAllProduse(),{} };

    QSlider* sldPret = new QSlider(Qt::Horizontal);
    QLabel* lblPretSld = new QLabel{ "Pret" }, * lblId = new QLabel{ "Id" }, * lblTitlu = new QLabel{
            "Nume" }, * lblTip = new QLabel{ "tip" }, * lblPret = new QLabel{ "Pret" };
    QLineEdit* txtTitlu = new QLineEdit, * txtId = new QLineEdit, * txtTip = new QLineEdit, * txtPret = new QLineEdit;

    QPushButton* btnAdd = new QPushButton{ "Add" };

    void initGui();

    void connectSlots();

    void reloadData();

    void openDyn();

public:
    GUI(Service& service) : service{ service } {
        initGui();
        connectSlots();
        reloadData();
    };

    void run() {
        this->show();
        openDyn();
    }

};
