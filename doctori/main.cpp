#include "doctori.h"
#include <QtWidgets/QApplication>
#include "DoctoriGUI.h"
#include "Teste.h"
int main(int argc, char *argv[])
{
    test_all();
    QApplication a(argc, argv);
    RepoFile repoFile{ "doctori.txt" };
    Service service{ repoFile };
    DoctoriGUI gui{ service };
    gui.show();
    //doctori w;
   // w.show();
    return a.exec();
}
