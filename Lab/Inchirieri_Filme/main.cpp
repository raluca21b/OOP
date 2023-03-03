#include "lab10.h"
#include <QtWidgets/QApplication>
#include "filmeStoreGUI.h"
#include "service.h"
int main(int argc, char *argv[])
{
   // QApplication a(argc, argv);
   // lab10 w;
   // w.show();
   // return a.exec();
    QApplication aplicatie(argc, argv);
    FileRepository repoFile{ "filme.txt" };
    FilmValidator valid;
    FilmeService service{ repoFile, valid };
    filmeStoreGUI gui{ service };

    gui.show();
    return aplicatie.exec();
}
