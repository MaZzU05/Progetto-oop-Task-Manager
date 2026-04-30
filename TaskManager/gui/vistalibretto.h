#ifndef VISTALIBRETTO_H
#define VISTALIBRETTO_H

#include <QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QScrollArea>
#include<QProgressBar>
#include<QPushButton>
#include"../modello/libretto.h"
namespace gui
{
class VistaLibretto : public QWidget
{
    Q_OBJECT
public:
    VistaLibretto(modello::Libretto* libretto, QWidget *parent=nullptr);
    void aggiornaVista();
private:
    void setup();
    void connectSegnali();
    void setWidget(std::vector<const modello::Esame*> esami);
    modello::Libretto* libretto=nullptr;
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    QHBoxLayout* layoutAlto;
    QVBoxLayout* layoutCentrale;
    QGridLayout* layoutBasso;
    QPushButton* modificaInfo;
    QLabel* labeltipoCorso;
    QLabel* labelnomeCorso;
    QLabel* labelCFU;
    QProgressBar* barraCFU;
    QLabel* labelMediaPesata;
    QProgressBar* barraMedia;
    QLabel* labelVotoAtteso;
    QProgressBar* barraVotoAtteso;
};
}
#endif // VISTALIBRETTO_H
