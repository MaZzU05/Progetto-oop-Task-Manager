#ifndef FINESTRAINIZIALIZZAZIONELIBRETTO_H
#define FINESTRAINIZIALIZZAZIONELIBRETTO_H

#include <QDialog>
#include<QVBoxLayout>
#include<QComboBox>
#include<QLineEdit>
#include<QPushButton>
namespace gui
{
class FinestraInizializzazioneLibretto:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QComboBox* comboTipologia;
    QLineEdit* inserimento;
    QPushButton* bottoneAccetta;
    QPushButton* bottoneRifiuta;
    void setup();
    void connectSegnali();

public:
    FinestraInizializzazioneLibretto(QWidget* parent=nullptr);
    unsigned int getCFU() const;
    QString getNomeCorso() const;
};

}
#endif // FINESTRAINIZIALIZZAZIONELIBRETTO_H
