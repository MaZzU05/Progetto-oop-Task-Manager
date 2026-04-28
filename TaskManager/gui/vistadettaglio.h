#ifndef VISTADETTAGLIO_H
#define VISTADETTAGLIO_H

#include <QWidget>
#include <QLabel>
#include<QVBoxLayout>
#include<QScrollArea>
#include"../modello/attivita.h"
namespace gui
{
class VistaDettaglio : public QWidget
{
    Q_OBJECT
public:
    VistaDettaglio(QWidget *parent = nullptr);
    void mostraAttivita(modello::Attivita*);
private:
    modello::Attivita* attivitaCorrente=nullptr;
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    QVBoxLayout* layoutCentrale;
    void setWidget(QWidget* nuovaCard);
    void setup();
//signals:
Q_SIGNALS:
    void tornaIndietro();

};
}
#endif // VISTADETTAGLIO_H
