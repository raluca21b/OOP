#pragma once

#include <QtWidgets/QWidget>
#include "ui_practic.h"

class practic : public QWidget
{
    Q_OBJECT

public:
    practic(QWidget *parent = nullptr);
    ~practic();

private:
    Ui::practicClass ui;
};
