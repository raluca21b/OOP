#pragma once

#include <QtWidgets/QWidget>
#include "ui_produse_bun.h"

class produse_bun : public QWidget
{
    Q_OBJECT

public:
    produse_bun(QWidget *parent = nullptr);
    ~produse_bun();

private:
    Ui::produse_bunClass ui;
};
