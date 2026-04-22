#include "barralateralewidget.h"
#include <QHBoxLayout>
namespace gui {
BarraLateraleWidget::BarraLateraleWidget(QWidget *parent)
    : QWidget(parent)
{setup();
connectSegnali();}


void BarraLateraleWidget::setup()
{
    layout=new QVBoxLayout(this);
    QHBoxLayout* layoutBarraRicerca=new QHBoxLayout();
    barraRicerca=new QLineEdit(this);
    barraRicerca->setPlaceholderText("Cerca"); //mette il testo suggerito in grigetto
    layoutBarraRicerca->addWidget(barraRicerca);
    QPixmap iconaRicerca("://gui/assets/icona_ricerca.png");
    QLabel *artwork=new QLabel(this);
    artwork->setPixmap(iconaRicerca.scaledToHeight(64));
    layoutBarraRicerca->addWidget(artwork);
    layout->addLayout(layoutBarraRicerca);
    labelTipo=new QLabel(this);
    labelTipo->setText("Tipologia:");
    layout->addWidget(labelTipo);
    comboTipo=new QComboBox(this);
    comboTipo->addItem("Tutte");
    comboTipo->addItem("Appuntamento");
    comboTipo->addItem("Esame");
    comboTipo->addItem("Scadenza");
    comboTipo->addItem("Sport");
    layout->addWidget(comboTipo);
    labelStato=new QLabel("Stato:",this);
    layout->addWidget(labelStato);
    comboStato=new QComboBox(this);
    comboStato->addItem("Tutte");
    comboStato->addItem("Completate");
    comboStato->addItem("Non completate");
    layout->addWidget(comboStato);
    labelAnno=new QLabel("Anno:", this);
    layout->addWidget(labelAnno);
    comboAnno=new QComboBox(this);
    layout->addWidget(comboAnno);
    checkFiltroData=new QCheckBox(this);
    layout->addWidget(checkFiltroData);
    modificaData=new QDateEdit(QDate::currentDate());
    modificaData->setDisplayFormat("dd.MM.yyyy"); //cosi visualizzo il selettore in giorno-mese-anno
    modificaData->setEnabled(false);//disabilito la visione automatica del calendartio, lo rendero' visibile col click del mouse
    layout->addWidget(modificaData);
    reset=new QPushButton("Reset");
    layout->addWidget(reset);
    layout->addStretch();
}

void BarraLateraleWidget::popolaAnni(const std::set<int>& s)
{
    comboAnno->clear();
    comboAnno->addItem("Tutte");
    for(auto anno:s) comboAnno->addItem(QString::number(anno));
}

bool BarraLateraleWidget::isFiltroDataOn() const
{
    return checkFiltroData->isChecked();
}

QString BarraLateraleWidget::getTestoRicerca() const
{
    return barraRicerca->text();
}

QString BarraLateraleWidget::getTipoSelezionato() const
{
    return comboTipo->currentText(); //restituisce il testo della casella selezionata
}

QString BarraLateraleWidget::getStatoSelezionato() const //da aggiungere il campo stato e il relativo widget
{
    return comboStato->currentText();
}

unsigned int BarraLateraleWidget::getAnnoSelezionato() const
{
    return comboAnno->currentText().toInt();
}

void BarraLateraleWidget::azzeraFiltri()
{
    barraRicerca->clear();
    comboTipo->setCurrentIndex(0);//lo riporto al primo elemento
    comboStato->setCurrentIndex(0);
    comboAnno->setCurrentIndex(0);
    checkFiltroData->setChecked(false);
    modificaData->setEnabled(false);
}

void BarraLateraleWidget::connectSegnali()
{
    //ablitazione calendario
    connect(checkFiltroData, &QCheckBox::clicked, modificaData, &QDateEdit::setEnabled);
    //reset, mi appoggio alla funzione interna azzera
    connect(reset, &QPushButton::pressed, this, &BarraLateraleWidget::azzeraFiltri);
    //segnali modifiche verso la main window
    connect(barraRicerca, &QLineEdit::textChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboTipo, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboStato, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboAnno, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(checkFiltroData, &QCheckBox::toggled, this, &BarraLateraleWidget::filtriCambiati);

}
}
