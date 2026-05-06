#include "finestrainizializzazionelibretto.h"
#include<QLabel>
#include<QHBoxLayout>
namespace gui
{
FinestraInizializzazioneLibretto::FinestraInizializzazioneLibretto(QWidget* parent): QDialog(parent)
{
    setup();
    connectSegnali();
}

/*
 *  QVBoxLayout* layout;
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
 */
void FinestraInizializzazioneLibretto::setup()
{
    this->setWindowTitle("Inserisci Informazioni Laurea");
    layout=new QVBoxLayout(this);
    QLabel* labelSelezione=new QLabel(this);
    labelSelezione->setText("Seleziona tipologia laurea:");
    layout->addWidget(labelSelezione);
    comboTipologia=new QComboBox(this);
    comboTipologia->addItem("Triennale-180CFU");
    comboTipologia->addItem("Magistrale-120CFU");
    comboTipologia->addItem("Ciclo Unico-300CFU");
    layout->addWidget(comboTipologia);
    QLabel* labelInserimento=new QLabel(this);
    labelInserimento->setText("Inserisci il titolo del corso:");
    layout->addWidget(labelInserimento);
    inserimento=new QLineEdit(this);
    inserimento->setPlaceholderText("Nome Laurea");
    layout->addWidget(inserimento);
    QHBoxLayout* layoutBottoni=new QHBoxLayout();
    layoutBottoni->setAlignment(Qt::AlignRight);
    bottoneRifiuta=new QPushButton("Annulla");
    //bottoneRifiuta->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    layoutBottoni->addWidget(bottoneRifiuta);
    bottoneAccetta=new QPushButton("Conferma");
    //bottoneAccetta->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    layoutBottoni->addWidget(bottoneAccetta);
    layout->addLayout(layoutBottoni);
}
void FinestraInizializzazioneLibretto::connectSegnali()
{
    connect(bottoneAccetta, &QPushButton::clicked, this, &FinestraInizializzazioneLibretto::accept);
    connect(bottoneRifiuta, &QPushButton::clicked, this, &FinestraInizializzazioneLibretto::reject);
}
unsigned int FinestraInizializzazioneLibretto::getCFU() const
{
    QString selezione=comboTipologia->currentText();
    if(selezione=="Triennale-180CFU") return 180;
    else if(selezione=="Magistrale-120CFU") return 120;
    return 300;

}
QString FinestraInizializzazioneLibretto::getNomeCorso() const
{
    return inserimento->text();
}
}
