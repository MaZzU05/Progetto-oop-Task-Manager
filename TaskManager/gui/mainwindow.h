#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include<QPushButton>
#include "barralateralewidget.h"
#include"vistaelenco.h"
#include"vistadettaglio.h"
#include"vistacalendario.h"
#include"../modello/gestore.h"
namespace gui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);

private:
    modello::Gestore gestorePrincipale;
    QStackedWidget* finestraPrincipale;
    BarraLateraleWidget* barraLaterale;
    VistaElenco* centrale;
    VistaDettaglio* dettaglioCentrale;
    VistaCalendario* calendarioCentrale;
    QPushButton* bottoneVistaLista;
    QPushButton* bottoneVistaCalendario;
    void connectSegnali();
};
}
#endif // MAINWINDOW_H
