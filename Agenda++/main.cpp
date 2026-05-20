#include "gui/mainwindow.h"
#include<QFile>
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/gui/assets/icona_app.png"));
    //carico il file di stile
    QFile fileStile(":/gui/assets/stile.qss");
    if(fileStile.open(QFile::ReadOnly))
      app.setStyleSheet(fileStile.readAll());
    gui::MainWindow w;
    w.resize(1024, 576);
    w.setWindowTitle("Agenda++");
    w.show();
    return app.exec();
}
