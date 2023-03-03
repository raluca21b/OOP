#include <QWodget/QApplication>
#include <QPushButton>
#include "Service.h"
#include "Repo.h"
#include "gui.h"

int main(int argc, char* argv[]) {
    testeDomain();
    testeRepo();
    testService();
    testeRepoFile();
    QApplication a(argc, argv);
    RepoFile repo{ "melodii.txt" };
    Service srv{ repo };
    GUI gui{ srv };
    gui.run();
    return QApplication::exec();

}
