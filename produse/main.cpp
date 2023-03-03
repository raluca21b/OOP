#include "produse_bun.h"
#include <QtWidgets/QApplication>
#include "Repo.h"
#include "Service.h"
#include "gui.h"
#include "teste.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepoFile repo{ "produse.txt" };
    Service srv{ repo };
    GUI gui(srv);
    test_all();
    gui.run();
    return QApplication::exec();
}
