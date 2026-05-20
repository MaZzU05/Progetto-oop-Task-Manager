#ifndef VISTAEDIT_H
#define VISTAEDIT_H

#include <QWidget>
#include<QLabel>
#include<QComboBox>
#include<QPushButton>
#include<QScrollArea>
#include<QVBoxLayout>
#include"Card/abstractcardedit.h"
#include"../modello/attivita.h"
namespace gui
{
class VistaEdit : public QWidget
{
    Q_OBJECT
public:
     VistaEdit(QWidget *parent = nullptr);
    void impostaPerCreazione(unsigned int id_daSalvare); //crea  una card vergine per crearne una nuova
     void impostaPerModifca(const modello::Attivita*);//imposta card per modifica
    modello::Attivita* getAttivita()  const;
private:
    void setup();
    void connectSegnali();
    unsigned int id;
    QDateTime dataCreazione;
    card::AbstractCardEdit* cardVisualizzata=nullptr;
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    QVBoxLayout* layoutCentrale;
    QLabel* labelTipo;
    QComboBox* comboTipo;
    QPushButton* bottoneAnnulla;
    QPushButton* bottoneSalva;


//signals:
Q_SIGNALS:
    void operazioneAnnulata();
    void operazioneConfermata(modello::Attivita*);
};
}
#endif // VISTAEDIT_H
