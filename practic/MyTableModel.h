#include <utility>

#include "QAbstractTableModel"
#include "QBrush"
#include "Qt"
#include "domain.h"
#include "vector"
#include "QFont"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
    vector<Melodie> melodii;
    map<string, int> artisti;
    map<string, int> genuri;

public:
    MyTableModel(vector<Melodie> melodii, map<string, int> artisti, map<string, int> genuri) :melodii(std::move(melodii)), artisti(std::move(artisti)), genuri(std::move(genuri)) {};

    /*
    * Returneaza numarul de linii ale tabelului
    */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }
    /*
    * Returneaza numarul de coloane ale tabelului
    */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 6;
    }
    /*
    * Afiseaza o melodie in tabel conform modelului creat
    */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Melodie m = melodii[index.row()];
            if (index.column() == 0)
                return QString::number(m.getId());
            if (index.column() == 1)
                return QString::fromStdString(m.getTitlu());
            if (index.column() == 2)
                return QString::fromStdString(m.getArtist());
            if (index.column() == 3)
                return QString::fromStdString(m.getGen());
            if (index.column() == 4)
                return QString::number(artisti.at(m.getArtist()));
            if (index.column() == 5)
                return QString::number(genuri.at(m.getGen()));
        }
        return QVariant{ };
    }
    void setMelodii(const vector<Melodie> melodi, map<string, int> artist, map<string, int> genuri) {
        this->melodii = melodi;
        this->artisti = artist;
        this->genuri = genuri;
        auto topLeft = createIndex(0, 0);
        auto bottomRight = createIndex(rowCount(), columnCount());
        emit layoutChanged();
        emit dataChanged(topLeft, bottomRight);
    }

};
