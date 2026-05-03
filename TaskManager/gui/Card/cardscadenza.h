#ifndef CARDSCADENZA_H
#define CARDSCADENZA_H

#include "abstractcardedit.h"
#include"../modello/scadenza.h"
namespace gui{
namespace card{
class CardScadenza : public AbstractCardEdit
{
    Q_OBJECT
public:
    CardScadenza(QWidget* parent=nullptr);
    modello::Scadenza* generaAttivita(unsigned int id) override;
    void popola(const modello::Scadenza* );
private:
    void setup();
    void connectSegnali();
    QWidget* contenitore;
    QVBoxLayout* layoutPrincipale;
    QLabel* labelPreavviso;
    QSpinBox* selezionaPreavviso;
    QLabel* labelToDoList;
    QPushButton* bottoneAggiungiTask;
    QPushButton* bottoneTogliTask;
    QLineEdit* inserisciTask;
    QListWidget* listaTask;
    std::vector<std::pair<QString, bool>> taskGiaPresenti; //serve per il caricamento

};
}}
#endif // CARDSCADENZA_H
