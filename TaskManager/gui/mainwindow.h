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
#include"vistalibretto.h"
#include"../modello/gestore.h"
#include"../modello/libretto.h"
namespace gui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);

private:
    modello::Gestore gestorePrincipale;
    modello::Libretto libretto;
    QStackedWidget* finestraPrincipale;
    BarraLateraleWidget* barraLaterale;
    VistaElenco* centrale;
    VistaDettaglio* dettaglioCentrale;
    VistaCalendario* calendarioCentrale;
    VistaLibretto* librettoCentrale;
    QPushButton* bottoneVistaLista;
    QPushButton* bottoneVistaCalendario;
    QPushButton* bottoneVistaLibretto;
    void connectSegnali();
};
}
#endif // MAINWINDOW_H
