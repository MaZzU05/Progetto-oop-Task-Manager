#ifndef ABSTRACTCARDEDIT_H
#define ABSTRACTCARDEDIT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QSpinBox>
#include<QDateEdit>
#include<QGroupBox>
#include<QCheckBox>
#include<QComboBox>
#include<QListWidget>
#include<QTimeEdit>
#include<QDateTime>
#include"../modello/attivita.h"
#include<vector>
namespace gui
{
namespace card
{
class AbstractCardEdit : public QWidget
{
    Q_OBJECT
private:
    QWidget* dettagliWidget;
    QVBoxLayout* layoutPrincipale;
    QVBoxLayout* parteAlta;
    QVBoxLayout* parteBassa;
    QLabel* labelTitolo;
    QLineEdit* inserisciTitolo;
    QLabel* labelData;
    QDateEdit* selezionaData;
    QLabel* labelOra;
    QTimeEdit* selezionaOra;
    QLabel* labelDurata;
    QSpinBox* inserisciDurata;
    QLabel* labelStato; //da valutare se spostarla
    QCheckBox* boxStato;
    QLabel* labelPriorita;
    QComboBox* comboPriorita;
    QLabel* labelTag;
    QPushButton* bottoneAggiungiTag;
    QPushButton* bottoneTogliTag;
    QLineEdit* inserisciTag;
    QListWidget* listaTag;
    QLabel* labelNote;
    QLineEdit* inserisciNote;
    void setup();
    void connectSegnali();

public:
     AbstractCardEdit(QWidget *parent = nullptr);
     virtual modello::Attivita* generaAttivita(unsigned int id)=0;
 protected:
     void addWidget(QWidget*); //per aggiungere elementi grafici nelle derivate
     //tutti i getter degli elementi della base selezionati, da utilizzare per la costruzione nella derivata
     const QString getTitle() const;
     QTime getTime() const;
     QDate getDate() const;
     unsigned int getDurata() const;
     modello::Priority getPriorita() const;
     std::vector<QString> getTag() const;
     const QString getNote() const;
     void nascondiDurata(); //per scadenza che non ha durata
     bool isComplete() const;
     void preparaBase(const modello::Attivita*); //popola gli elementi con quelli dell'attivita eventualmente d a modificare, da usare nelle derivate


//signals:
 Q_SIGNALS:
};
}
}
#endif // ABSTRACTCARDEDIT_H
