#ifndef CARDESAME_H
#define CARDESAME_H
#include"../modello/esame.h"
#include "abstractcardedit.h"
namespace gui
{namespace card
{
class CardEsame : public AbstractCardEdit
{
    Q_OBJECT
public:
    CardEsame(QWidget* parent=nullptr);
    modello::Esame* generaAttivita(unsigned int id) override;
    void popola(const modello::Esame* );
    QString validaSelezioni() override;
private:
    void setup();
    void connectSegnali();
    QWidget* contenitore;
    QVBoxLayout* layoutPrincipale;
    QLabel* labelCFU;
    QSpinBox* selezionaCFU;
    QLabel* labelVoto;
    QSpinBox* selezionaVoto;
    QLabel* labelSede;
    QLineEdit* inserisciSede;
    QLabel* labelProfessori;
    QPushButton* bottoneAggiungiProfessore;
    QPushButton* bottoneTogliProfessore;
    QLineEdit* inserisciProfessore;
    QListWidget* listaProfessori;



};
}}
#endif // CARDESAME_H
