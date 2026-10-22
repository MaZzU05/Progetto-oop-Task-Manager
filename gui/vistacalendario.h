#ifndef VISTACALENDARIO_H
#define VISTACALENDARIO_H

#include <QWidget>
#include<QCalendarWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QScrollArea>
#include "abstractvistaattivita.h"
#include "../modello/gestoreobserverinterface.h"
#include "../modello/gestore.h"
#include"../modello/attivita.h"
namespace gui
{
class VistaCalendario : public AbstractVistaAttivita, public modello::GestoreObserverInterface
{
    Q_OBJECT
public:
    VistaCalendario(QWidget *parent = nullptr);
    void popolaAttivita(const std::vector<modello::Attivita*>& vec) override;
    void notify(modello::Gestore& gestore) override;
private:
    void setup();
    void connectSegnali();
    void coloraGiorni(int mese, int anno);
    void decoloraGiorni(int mese, int anno);
    void costruisciSettimana(QDate giornoSelezionato);
    QVBoxLayout* layoutPrincipale;
    QCalendarWidget* calendario;
    QScrollArea* AreaScorrimento;
    QWidget* contenitoreCentrale;
    //creo un layout composito di 7 layout verticali per le attività settimanali
    QHBoxLayout* layoutSettimana;
    std::vector<QVBoxLayout*> vecLayoutSettimana;
    std::vector<modello::Attivita*> vecAttivita;
};
}
#endif // VISTACALENDARIO_H
