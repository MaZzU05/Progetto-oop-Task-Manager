#ifndef BARRALATERALEWIDGET_H
#define BARRALATERALEWIDGET_H

#include<QWidget>
#include <QString>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QCheckBox>
#include<QDateEdit>
#include<QPushButton>
#include<set>
namespace gui{
class BarraLateraleWidget : public QWidget
{
    Q_OBJECT
public:
     BarraLateraleWidget(QWidget *parent = nullptr);
     QString getTestoRicerca() const;
     QString getTipoSelezionato() const;
     QString getStatoSelezionato() const;
     bool isFiltroDataOn() const;
     unsigned int getAnnoSelezionato() const;
     void popolaAnni(const std::set<int>& s);
private:
     QVBoxLayout* layout;
     QLineEdit* barraRicerca; //per scrivere il testo
     QLabel* labelTipo;
     QComboBox* comboTipo;
     QLabel* labelAnno;
     QComboBox* comboAnno;
     QCheckBox* checkFiltroData;
     QDateEdit* modificaData;
     QLabel* labelStato;
     QComboBox* comboStato;
     QPushButton* reset;
     void setup(); //uso una funzione dove compongo i vari layout ecc. per non avere un costruttore troppo complesso
     void connectSegnali(); //usato per connettere i segnali agli slot
//signals: conflitto con compilatore Appleclang in macos che da errore
 Q_SIGNALS:
     void filtriCambiati();
 //private slots:
 private Q_SLOTS:
     void azzeraFiltri();


};
}
#endif // BARRALATERALEWIDGET_H
