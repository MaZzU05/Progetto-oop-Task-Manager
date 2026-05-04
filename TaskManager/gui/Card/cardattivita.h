#ifndef CARDATTIVITA_H
#define CARDATTIVITA_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QListWidget>
#include"../modello/attivita.h"
namespace gui
{
namespace card
{
class CardAttivita : public QWidget
{
    Q_OBJECT
private:
    QWidget* dettagliWidget;
    QVBoxLayout* layoutPrincipale;
    QLabel* titolo;
    QLabel* data_ora;
    QLabel* durata;
    QLabel* Completata;
    QLabel* dataCreazione;
    QLabel* tag;
    QLabel* note;
    QLabel* priorita;
    QHBoxLayout* layoutAlto;
    QVBoxLayout* layoutDettagli;
    bool espansa;
    void setup();
    const modello::Attivita* attivitaRappresentata;
public:
    CardAttivita(QWidget *parent = nullptr);
    void setSelezionata(bool stato);
    void popolaAttivita(const modello::Attivita*);
    void addWidget(QWidget*);
protected:
    //per fare in modo che vi sia l'evento del tocco del mouse sul mio widget, dato che qwidget non ce l'ha, ho dovuto farne l'override
    void mousePressEvent(QMouseEvent *event) override;

//signals:
Q_SIGNALS:
    //per selezionare l'attivita, espanderla e farvi operazioni, il bool lo sfrutto nella mainWindow, dato che voglio una sola attivita' espansa per volta
    void selezionata(CardAttivita*, bool);
};
}
}
#endif // CARDATTIVITA_H
