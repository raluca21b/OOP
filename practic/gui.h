#include <QWidget>
#include "QLayout"
#include "QPushButton"
#include "MyTableModel.h"
#include "QLabel"
#include "QLineEdit"
#include "QTableView"
#include "Service.h"
#include "qmessagebox.h"
class GUI : public QWidget {
private:
    Service& srv;       ///service

    QWidget* comps = new QWidget;

    //tabel in care vor fi afisate melodiile
    MyTableModel* model = new MyTableModel{ srv.getAllServ(),srv.artisti(),srv.genuri() };
    QTableView* table = new QTableView;

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* compsLayout = new QHBoxLayout;

    //buton de adaugare
    QPushButton* addBtn = new QPushButton, * deleteBtn = new QPushButton;

    //text fielduri pentru adaugare
    QLabel* lblTitlu = new QLabel, * lblArtist = new QLabel, * lblGen = new QLabel;
    QLineEdit* txtTitlu = new QLineEdit, * txtArtist = new QLineEdit, * txtGen = new QLineEdit;

    /*
    * Initializeaza toate componentele gui
    */
    void initGui();
    /*
    * Conecteaza elementele gui la interfata
    */
    void connectSlots();
    /*
    * Reactualizeaza lista de melodii
    */
    void reloadList();
    /*
    * Deseneaza cercurile 
    */
    void paintEvent(QPaintEvent* event) override;

public:
    explicit GUI(Service& srv) :srv{ srv } {
        initGui();
        connectSlots();
        reloadList();
    };
    void run() { this->show(); };
};
