#ifndef CARDAPPUNTAMENTO_H
#define CARDAPPUNTAMENTO_H

#include "abstractcardedit.h"
#include"../modello/appuntamento.h"
#include<QRadioButton>
#include<QGroupBox>
namespace gui
{namespace card
{
class CardAppuntamento : public AbstractCardEdit
{
    Q_OBJECT
public:
    CardAppuntamento(QWidget* parent=nullptr);
    modello::Appuntamento* generaAttivita(unsigned int id, QDateTime dataCreazione) override;
    void popola(const modello::Appuntamento* );
    QString validaSelezioni() override;
private:
    void setup();
    void connectSegnali();
    QWidget* contenitore;
    QVBoxLayout* layoutPrincipale;
    QLabel* labelLuogo;
    QLineEdit* inserisciLuogo;
    QLabel* labelInPresenza;
    //per la scelta tra presenza e online uso per cambiare i QRadioButton inseriti in un QGroupBox
    QGroupBox* groupModalita;
    QRadioButton* radPresenza;
    QRadioButton* radOnline;
    QLabel* labelPartecipanti;
    QPushButton* bottoneAggiungiPartecipante;
    QPushButton* bottoneTogliPartecipante;
    QLineEdit* inserisciPartecipante;
    QListWidget* listaPartecipanti;


};
}}
#endif // CARDAPPUNTAMENTO_H
