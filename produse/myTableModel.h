#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "domain.h"
#include <vector>
#include <qdebug.h>
#include <QFont>

using std::vector;

class MyTableModel :public QAbstractTableModel {
    std::vector<Produs> produse;
    vector<Produs> filtre;

public:
    MyTableModel(const vector<Produs>& produse, vector<Produs> filtre) :produse{ produse }, filtre(filtre){
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return produse.size();
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override {
        return 0;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {

      
        if (role == Qt::BackgroundRole) {
            auto carte = this->produse[index.row()];
            for (const auto& p : filtre) {
                if (carte.getId() == p.getId()) {
                    QBrush bg(Qt::red);
                    return bg;
                }
            }
        }


        if (role == Qt::DisplayRole) {

            Produs c = produse[index.row()];
            if (index.column() == 0) {
                return QString::number(c.getId());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(c.getNume());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(c.getTip());
            }
            else if (index.column() == 3) {
                return QString::number(c.getPret());
            }
            else if (index.column() == 4) {
                return QString::number(c.getNumarVocale());
            }
        }

        return QVariant{};
    }

    void setProduse(const vector<Produs> produse, const vector<Produs> filtru) {
        this->produse = produse;
        this->filtre = filtru;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit layoutChanged();
        emit dataChanged(topLeft, bottomR);
    }

    Qt::ItemFlags flags(const QModelIndex&) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case 0:
                    return tr("Id");
                case 1:
                    return tr("Nume");
                case 2:
                    return tr("Tip");
                case 3:
                    return tr("Pret");
                case 4:
                    return tr("Vocale");
                default:
                    return QString("");
                }
            }
        }
        return QVariant();
    }
};
