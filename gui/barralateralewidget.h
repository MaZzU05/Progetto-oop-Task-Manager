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
#include<QListWidget>
#include "../modello/gestoreobserverinterface.h"
#include "../modello/gestore.h"
#include<set>
#include<vector>
namespace gui{
class BarraLateraleWidget : public QWidget, public modello::GestoreObserverInterface
{
    Q_OBJECT
public:
     BarraLateraleWidget(QWidget *parent = nullptr);
     QString getTestoRicerca() const;
     QString getTipoSelezionato() const;
     QString getStatoSelezionato() const;
     QString getUrgenzaSelezionata() const;
     QDate getDataSelezionata() const;
     bool isFiltroDataOn() const;
     bool isFiltroAnnoOn() const;
     unsigned int getAnnoSelezionato() const;
     QString getPrioritaSelezionata() const;
     std::vector<QString> getTagSelezionati() const;
     bool isFiltroMeseAnnoOn() const; // true solo se mese E anno sono entrambi selezionati
     unsigned int getMeseSelezionato() const;  // ritorna 1-12 (corrispondente a MeseTarget)
     void notify(modello::Gestore& gestore) override;
private:
     QVBoxLayout* layout;
     QLineEdit* barraRicerca; //per scrivere il testo
     QLabel* labelTipo;
     QComboBox* comboTipo;
     QLabel* labelAnno;
     QLabel* labelMese;
     QComboBox* comboAnno;
     QComboBox* comboMese;
     QCheckBox* checkFiltroData;
     QDateEdit* modificaData;
     QLabel* labelStato;
     QComboBox* comboStato;
     QLabel* labelUrgenza;
     QComboBox* comboUrgenza;
     QLabel* labelPriorita;
     QComboBox* comboPriorita;
     QLabel* labelTag;
     QLineEdit* cercaTag;
     QListWidget* listaTag; //se avessi usato la QComboBox come in precedenza non avrei potuto usare la selezione multipla
     QPushButton* reset;
     void popolaMesi();
     void popolaAnni(const std::set<int>& s);
     void popolaTag(const std::set<QString>& t);
     void setup(); //uso una funzione dove compongo i vari layout ecc. per non avere un costruttore troppo complesso
     void connectSegnali(); //usato per connettere i segnali agli slot
//signals: conflitto con compilatore Appleclang in macos che da errore
 Q_SIGNALS:
     void filtriCambiati();
 //private slots:
 private Q_SLOTS:
     void azzeraFiltri();
     void filtraRigheTag(const QString& testoCercato); //per nascondere i tag nella ricerca testuale


};
}
#endif // BARRALATERALEWIDGET_H
