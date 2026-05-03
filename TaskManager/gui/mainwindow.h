#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include<QPushButton>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include "barralateralewidget.h"
#include"vistaelenco.h"
#include"vistadettaglio.h"
#include"vistacalendario.h"
#include"vistalibretto.h"
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
    VistaLibretto* librettoCentrale;
    QPushButton* bottoneVistaLista;
    QPushButton* bottoneVistaCalendario;
    QPushButton* bottoneVistaLibretto;
    QPushButton* bottoneModifica;
    QPushButton* bottoneElimina;
    QPushButton* bottoneAggiungi;
    QMenu* menuFile;
    QMenu* menuAiuto;
    QAction* azioneSalva;
    QAction* azioneCarica;
    QAction* azioneAiuto;
    void preparaMenuAzioni();
    void salvataggio();
    void caricaAgenda();
    void refresh();
    void connectSegnali();
    //private slots:
private Q_SLOTS:
    void applicaFiltri();


};
}
#endif // MAINWINDOW_H
