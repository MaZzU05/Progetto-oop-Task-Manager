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
    QPixmap iconaRicerca(":/gui/assets/icona_ricerca.png");
    QLabel *artwork=new QLabel(this);
    artwork->setPixmap(iconaRicerca.scaledToHeight(32));
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
    labelUrgenza=new QLabel("Urgenza:", this);
    layout->addWidget(labelUrgenza);
    comboUrgenza=new QComboBox(this);
    comboUrgenza->addItem("Tutte");
    comboUrgenza->addItem("Urgente");
    comboUrgenza->addItem("Non Urgente");
    layout->addWidget(comboUrgenza);
    labelPriorita=new QLabel("Priorita:", this);
    layout->addWidget(labelPriorita);
    comboPriorita=new QComboBox(this);
    comboPriorita->addItem("Tutte");
    comboPriorita->addItem("Alta");
    comboPriorita->addItem("Media");
    comboPriorita->addItem("Bassa");
    layout->addWidget(comboPriorita);
    labelAnno=new QLabel("Anno:", this);
    layout->addWidget(labelAnno);
    comboAnno=new QComboBox(this);
    comboAnno->addItem("Tutte");
    layout->addWidget(comboAnno);
    labelMese=new QLabel("Mese:", this);
    layout->addWidget(labelMese);
    comboMese=new QComboBox(this);
    comboMese->setEnabled(false); //di default la disabilito, se seleziono l'anno la riabilito
    popolaMesi();
    layout->addWidget(comboMese);
    checkFiltroData=new QCheckBox("Filtra per data:", this);
    layout->addWidget(checkFiltroData);
    modificaData=new QDateEdit(QDate::currentDate());
    modificaData->setDisplayFormat("dd.MM.yyyy"); //cosi visualizzo il selettore in giorno-mese-anno
    modificaData->setEnabled(false);//disabilito la visione automatica del selettore, lo rendero' visibile col click del mouse
    //modificaData->setCalendarPopup(true);//permette di selezionare la data con un mini calendario, abbastanza invasivo, per ora lo disabilito
    layout->addWidget(modificaData);
    labelTag=new QLabel("Filtra per tag:", this);
    layout->addWidget(labelTag);
    cercaTag=new QLineEdit(this);
    cercaTag->setPlaceholderText("Cerca tag");
    layout->addWidget(cercaTag);
    listaTag=new QListWidget(this);
    listaTag->setSelectionMode(QAbstractItemView::MultiSelection);//necessario per abilitare la selezione mmultipla
    layout->addWidget(listaTag);
    reset=new QPushButton("Reset");
    reset->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    layout->addWidget(reset);
    layout->addStretch();
}

void BarraLateraleWidget::popolaAnni(const std::set<int>& s)
{
    comboAnno->blockSignals(true);

    // Salva la selezione corrente per non perderla durante l'aggiornamento
    QString current = comboAnno->currentText();

    comboAnno->clear();
    comboAnno->addItem("Tutte");
    for(auto anno:s)
    {
        comboAnno->addItem(QString::number(anno));
    }

    // Ripristina la selezione precedente se esiste ancora, altrimenti torna a "Tutte"
    int index = comboAnno->findText(current);
    if (index >= 0) comboAnno->setCurrentIndex(index);
    else comboAnno->setCurrentIndex(0);

    comboAnno->blockSignals(false);
}

void BarraLateraleWidget::popolaMesi()
{
    comboMese->addItem("Tutte");
    comboMese->addItem("Gennaio");
    comboMese->addItem("Febbraio");
    comboMese->addItem("Marzo");
    comboMese->addItem("Aprile");
    comboMese->addItem("Maggio");
    comboMese->addItem("Giugno");
    comboMese->addItem("Luglio");
    comboMese->addItem("Agosto");
    comboMese->addItem("Settembre");
    comboMese->addItem("Ottobre");
    comboMese->addItem("Novembre");
    comboMese->addItem("Dicembre");
}

void BarraLateraleWidget::popolaTag(const std::set<QString>& t)
{
    //ho dovuto bloccare i segnali perche' quando ho implementato l'observer, ad ogni update i segnali venivano inviati e si creava la lista, portando ad una ricorsione infinita che causava stack overflow
    listaTag->blockSignals(true);

    // Salva le selezioni correnti
    std::vector<QString> selectedTags;
    for(QListWidgetItem* item : listaTag->selectedItems()) {
        selectedTags.push_back(item->text());
    }

    listaTag->clear();
    for(const QString &tag:t) {
        listaTag->addItem(tag);
    }

    // Ripristina le selezioni
    for(int i = 0; i < listaTag->count(); i++) {
        QListWidgetItem* item = listaTag->item(i);
        if (std::find(selectedTags.begin(), selectedTags.end(), item->text()) != selectedTags.end()) {
            item->setSelected(true);
        }
    }

    listaTag->blockSignals(false);
}

bool BarraLateraleWidget::isFiltroDataOn() const
{
    return checkFiltroData->isChecked();
}

bool BarraLateraleWidget::isFiltroAnnoOn() const
{
    return comboAnno->currentText() != "Tutte";
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

QString BarraLateraleWidget::getUrgenzaSelezionata() const
{
    return comboUrgenza->currentText();
}

unsigned int BarraLateraleWidget::getAnnoSelezionato() const
{
    return comboAnno->currentText().toInt();
}

QDate BarraLateraleWidget::getDataSelezionata() const
{
    return modificaData->date();
}

QString BarraLateraleWidget::getPrioritaSelezionata() const
{
    return comboPriorita->currentText();
}

std::vector<QString> BarraLateraleWidget::getTagSelezionati() const
{
    std::vector<QString> selezionati;
    for(QListWidgetItem* item : listaTag->selectedItems())
        selezionati.push_back(item->text());
    return selezionati;
}

bool BarraLateraleWidget::isFiltroMeseAnnoOn() const
{
    // attivo solo se sia il mese che l'anno sono selezionati (FiltroMeseAnno richiede entrambi)
    return comboMese->currentIndex() != 0 && comboAnno->currentText() != "Tutte";
}

unsigned int BarraLateraleWidget::getMeseSelezionato() const
{
    // currentIndex() e' gia' 1-12: "Tutte"=0, "Gennaio"=1, ..., "Dicembre"=12
    // corrisponde direttamente ai valori del'enum MeseTarget del modello
    return comboMese->currentIndex();
}

//scorro tutti gli elementi per indice di riga, li estraggo di volta in volta, e valuto se vi e' la sottostringa, se si le lascio visibili, se no le nascondo
void BarraLateraleWidget::filtraRigheTag(const QString& testoCercato)
{
    for(int i=0; i<listaTag->count(); i++)
    {
        QListWidgetItem* temp=listaTag->item(i);
        if(temp->text().contains(testoCercato, Qt::CaseInsensitive)) temp->setHidden(false); //estrae il testo della riga con text(), poi verifico la sottostringa con il metodo contains di QString
        else temp->setHidden(true);
    }
}

void BarraLateraleWidget::azzeraFiltri()
{
    barraRicerca->clear();
    comboTipo->setCurrentIndex(0);//lo riporto al primo elemento
    comboStato->setCurrentIndex(0);
    comboPriorita->setCurrentIndex(0);
    comboAnno->setCurrentIndex(0);
    comboMese->setCurrentIndex(0);
    checkFiltroData->setChecked(false);
    modificaData->setEnabled(false);
    cercaTag->clear();
    filtraRigheTag(""); // ripristina la visibilità di tutte le righe nascoste dalla ricerca
    for(int i=0; i<listaTag->count(); i++)
    {
        QListWidgetItem* temp=listaTag->item(i);
        temp->setHidden(false); //se nascosta la riporto visibile
        temp->setSelected(false); //se selezionata la deseleziono
    }
}

void BarraLateraleWidget::connectSegnali()
{
    //ablitazione selettore data
    connect(checkFiltroData, &QCheckBox::toggled, modificaData, &QDateEdit::setEnabled);
    //reset, mi appoggio alla funzione interna azzera
    connect(reset, &QPushButton::pressed, this, &BarraLateraleWidget::azzeraFiltri);
    //selezione Tag
    connect(cercaTag, &QLineEdit::textChanged, this, &BarraLateraleWidget::filtraRigheTag);
    //se filtro per data disabilito per mese e per anno
    connect(checkFiltroData, &QCheckBox::toggled, this, [this](bool spuntato){
        modificaData->setEnabled(spuntato);
        comboAnno->setEnabled(!spuntato);
        comboMese->setEnabled(!spuntato);
    });
    //rende cliccabile o meno il selettore di mese in base a quello di anno
    connect(comboAnno, &QComboBox::currentTextChanged, this, [this](const QString& testo){
        bool annoSelezionato=testo!="Tutte";
        comboMese->setEnabled(annoSelezionato&& !checkFiltroData->isChecked());
        if(!annoSelezionato) comboMese->setCurrentIndex(0); //se non e' selezionato l'anno, riporto anche mesi su Tutte
    });
    //segnali modifiche verso la main window
    connect(barraRicerca, &QLineEdit::textChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboTipo, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboStato, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboUrgenza, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboPriorita, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboAnno, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(comboMese, &QComboBox::currentIndexChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(checkFiltroData, &QCheckBox::toggled, this, &BarraLateraleWidget::filtriCambiati);
    connect(modificaData, &QDateEdit::userDateChanged, this, &BarraLateraleWidget::filtriCambiati);
    connect(listaTag, &QListWidget::itemSelectionChanged, this, &BarraLateraleWidget::filtriCambiati);

}

void BarraLateraleWidget::notify(modello::Gestore& gestore)
{
    popolaAnni(gestore.getAnniPresenti());
    popolaTag(gestore.getTagPresenti());
}
}
