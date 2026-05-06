#ifndef CARDSPORT_H
#define CARDSPORT_H

#include "abstractcardedit.h"
#include"../modello/sport.h"
namespace gui{
namespace card{

class CardSport : public AbstractCardEdit
{
    Q_OBJECT
public:
    CardSport(QWidget* parent=nullptr);
    modello::Sport* generaAttivita(unsigned int id, QDateTime dataCreazione) override;
    void popola(const modello::Sport* );
    QString validaSelezioni() override;
private:
    void setup();
    //void connectSegnali();
    QWidget* contenitore;
    QVBoxLayout* layoutPrincipale;
    QLabel* labelLuogo;
    QLineEdit* inserisciLuogo;
    QLabel* labelDataInizio;
    QDateEdit* selezionaDataInizio;
    QLabel* labelGiorniSport;
    QListWidget* listaGiorniSport;
};
}}
#endif // CARDSPORT_H
