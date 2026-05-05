#include "abstractcardedit.h"
#include<QHBoxLayout>
namespace gui
{
namespace card
{
AbstractCardEdit::AbstractCardEdit(QWidget *parent)
    : QWidget(parent)
{
    setup();
    connectSegnali();
}

void AbstractCardEdit::setup()
{
    //uniformo lo stile dei bottoni
    //note: quando un ancestor ha un setStyleSheet Qt disabilita il renderer nativo per tutti i figli.
    //aggiungo regole esplicite con palette() per ripristinare la resa corretta di SpinBox, ComboBox e DateEdit su tema chiaro e Linux
    /*this->setStyleSheet(
        // bottoni
        "QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } "
        "QPushButton:hover { background-color: lightblue; } "
        "QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; } "
        // QSpinBox: ripristina sfondo e frecce
        "QSpinBox { background-color: palette(base); color: palette(text); } "
        "QSpinBox::up-button   { subcontrol-origin: border; subcontrol-position: top right;    width: 16px; border: 1px solid grey; border-radius: 2px; } "
        "QSpinBox::down-button { subcontrol-origin: border; subcontrol-position: bottom right; width: 16px; border: 1px solid grey; border-radius: 2px; } "
        "QSpinBox::up-arrow   { width: 7px; height: 7px; } "
        "QSpinBox::down-arrow { width: 7px; height: 7px; } "
        // QComboBox: ripristina sfondo e colori nel dropdown
        "QComboBox { background-color: palette(base); color: palette(text); } "
        "QComboBox QAbstractItemView { background-color: palette(base); color: palette(text); "
        "    selection-background-color: palette(highlight); selection-color: palette(highlighted-text); } "
        // QDateEdit: sfondo e popup calendario
        "QDateEdit { background-color: palette(base); color: palette(text); } "
        "QCalendarWidget QAbstractItemView { background-color: palette(base); color: palette(text); "
        "    selection-background-color: palette(highlight); selection-color: palette(highlighted-text); } "
        "QCalendarWidget QWidget#qt_calendar_navigationbar { background-color: palette(window); color: palette(window-text); } "
    );
*/
    this->setStyleSheet("QPushButton { background-color: transparent; padding: 5px; border: 1px solid grey; border-radius: 10px; } QPushButton:hover { background-color: lightblue; } QPushButton:pressed { background-color: #e0e0e0; border: 1px solid #b0b0b0; }");
    layoutPrincipale=new QVBoxLayout(this);
    //la parte alta conterra' gli attributi della base, la parte bassa verra' popolata nelle derivate con le parti spedcifiche
    parteAlta=new QVBoxLayout();
    QHBoxLayout* layoutTitolo=new QHBoxLayout();
    layoutTitolo->setAlignment(Qt::AlignLeft);
    labelTitolo=new QLabel("Titolo: ", this);
    layoutTitolo->addWidget(labelTitolo);
    inserisciTitolo=new QLineEdit(this);
    inserisciTitolo->setPlaceholderText("inserisci titolo");
    layoutTitolo->addWidget(inserisciTitolo);
    parteAlta->addLayout(layoutTitolo);
    QHBoxLayout* layoutData=new QHBoxLayout();
    layoutData->setAlignment(Qt::AlignLeft);
    labelData=new QLabel("Data: ", this);
    layoutData->addWidget(labelData);
    selezionaData=new QDateEdit(this);
    selezionaData->setDate(QDate::currentDate());
    selezionaData->setDisplayFormat("dd.MM.yyyy");
    selezionaData->setCalendarPopup(true); //abilito il mini calendario per selezionare la data
    layoutData->addWidget(selezionaData); //li imposto al giorno attuale
    parteAlta->addLayout(layoutData);
    QHBoxLayout* layoutOra=new QHBoxLayout();
    layoutOra->setAlignment(Qt::AlignLeft);
    labelOra=new QLabel("Orario: ", this);
    layoutOra->addWidget(labelOra);
    selezionaOra=new QTimeEdit(this);
    selezionaOra->setTime(QTime::currentTime());//e all'ora attuale
    layoutOra->addWidget(selezionaOra);
    parteAlta->addLayout(layoutOra);
    QHBoxLayout* layoutDurata=new QHBoxLayout();
    layoutDurata->setAlignment(Qt::AlignLeft);
    labelDurata=new QLabel("Durata in minuti: ", this);
    layoutDurata->addWidget(labelDurata);
    inserisciDurata=new QSpinBox(this);
    inserisciDurata->setMinimum(0); //imposto il valore minimo a 0, non si possono avere minuti positivi
    inserisciDurata->setMaximum(10000); //di default arriva fino a 99, questa quantita in ore sono circa 165, mi sembra piu' che sufficiente
    layoutDurata->addWidget(inserisciDurata);
    parteAlta->addLayout(layoutDurata);
    QHBoxLayout* layoutStato=new QHBoxLayout();
    layoutStato->setAlignment(Qt::AlignLeft);
    labelStato=new QLabel("Stato: ", this);
    layoutStato->addWidget(labelStato);
    boxStato=new QCheckBox(this);
    boxStato->setText("Completata");
    layoutStato->addWidget(boxStato);
    parteAlta->addLayout(layoutStato);
    QHBoxLayout* layoutPriorita=new QHBoxLayout();
    layoutPriorita->setAlignment(Qt::AlignLeft);
    labelPriorita=new QLabel("Priorità: ", this);
    layoutPriorita->addWidget(labelPriorita);
    comboPriorita=new QComboBox(this);
    comboPriorita->addItem("Alta");
    comboPriorita->addItem("Media");
    comboPriorita->addItem("Bassa");
    layoutPriorita->addWidget(comboPriorita);
    parteAlta->addLayout(layoutPriorita);
    QHBoxLayout* layoutTag=new QHBoxLayout();
    layoutTag->setAlignment(Qt::AlignLeft);
    labelTag=new QLabel("Tag: ", this);
    layoutTag->addWidget(labelTag);
    QVBoxLayout* layoutTagInterno=new QVBoxLayout();
    QHBoxLayout* layoutTagTools=new QHBoxLayout();
    inserisciTag=new QLineEdit(this);
    inserisciTag->setPlaceholderText("inserisci tag");
    layoutTagTools->addWidget(inserisciTag);
    bottoneAggiungiTag=new QPushButton("Aggiungi", this);
    layoutTagTools->addWidget(bottoneAggiungiTag);
    bottoneTogliTag=new QPushButton("Rimuovi", this);
    layoutTagTools->addWidget(bottoneTogliTag);
    layoutTagInterno->addLayout(layoutTagTools);
    listaTag=new QListWidget(this);
    layoutTagInterno->addWidget(listaTag);
    layoutTag->addLayout(layoutTagInterno);
    parteAlta->addLayout(layoutTag);
    QHBoxLayout* layoutNote=new QHBoxLayout();
    layoutNote->setAlignment(Qt::AlignLeft);
    labelNote=new QLabel("Note: ", this);
    layoutNote->addWidget(labelNote);
    inserisciNote=new QTextEdit(this);
    inserisciNote->setPlaceholderText("inserisci note");
    //imposto lo stile del QTextEdit, se no risulta sgradevole non avendo contorni ne niente, mi uniformo con le parti dell cardAttivita
    inserisciNote->setStyleSheet("QTextEdit { border: 1px solid #e0e0e0; border-radius: 10px; padding: 10px; background-color: transparent;}");
    layoutNote->addWidget(inserisciNote);
    parteAlta->addLayout(layoutNote);
    layoutPrincipale->addLayout(parteAlta);
    parteBassa=new QVBoxLayout();
    layoutPrincipale->addLayout(parteBassa);

}
void AbstractCardEdit::connectSegnali()
{
    //per togliere il tag selezionato collego il click del bottone con una lambda che toglie l'elemento dalla list
    connect(bottoneTogliTag, &QPushButton::clicked, this, [this](){
        int riga=listaTag->currentRow(); //estraggo la riga
        //controllo che ve ne sia una selezionata
        if(riga!=-1)
          delete listaTag->takeItem(riga);
    });
    connect(bottoneAggiungiTag, &QPushButton::clicked, this, [this](){
        //controllo che abbia inserito il testo
        if(!inserisciTag->text().isEmpty())
            {
            bool check=true;
            //controllo che il tag non sia gia' presente, ignoro gli spazi
            for(int i=0; i<listaTag->count()&&check; i++)
            {
                check=(listaTag->item(i)->text().trimmed()!=inserisciTag->text().trimmed()); //trimmed rimuove gli spazi
            }
            //inserisco solo se non presente
        if(check)
                listaTag->addItem(inserisciTag->text());

        }
    });
}
void AbstractCardEdit::addWidget(QWidget* widget)
{
    parteBassa->addWidget(widget);
}
//tutti i getter degli elementi della base selezionati, da utilizzare per la costruzione nella derivata
const QString AbstractCardEdit::getTitle() const
{
    return inserisciTitolo->text();
}
QTime AbstractCardEdit::getTime() const
{
    return selezionaOra->time();
}
QDate AbstractCardEdit::getDate() const
{
    return selezionaData->date();
}
unsigned int AbstractCardEdit::getDurata() const
{
    return inserisciDurata->value();
}
modello::Priority AbstractCardEdit::getPriorita() const
{
    if(comboPriorita->currentText()=="Alta")
        return modello::Priority::alta;
    else if(comboPriorita->currentText()=="Media")
        return modello::Priority::media;
    else
        return modello::Priority::bassa;
}
std::vector<QString> AbstractCardEdit::getTag() const
{
    std::vector<QString> aux;
    for(int i=0; i<listaTag->count(); i++)
        aux.push_back(listaTag->item(i)->text());
    return aux;
}
const QString AbstractCardEdit::getNote() const
{
    return inserisciNote->toPlainText(); //per il QTextEdit essendo che accetta le formattazioni va usato questo
}

bool AbstractCardEdit::isComplete() const
{
    return boxStato->isChecked();
}
void AbstractCardEdit::nascondiDurata()
{
    labelDurata->setVisible(false);
    inserisciDurata->setVisible(false);
}
void AbstractCardEdit::preparaBase(const modello::Attivita* a)
{
    inserisciTitolo->setText(a->getTitle());
    selezionaData->setDate(a->getDate().date());
    selezionaOra->setTime(a->getDate().time());
    inserisciDurata->setValue(a->getDurata());
    comboPriorita->setCurrentIndex(static_cast<int>(a->getPriority())); //ho seguito l'ordine dell'enum
    std::vector<QString> aux=a->getAllTag();
    for(const QString& tag:aux)
        listaTag->addItem(tag);
    inserisciNote->setPlainText(a->getNote());
}

QString AbstractCardEdit::validazioneBase()
{
    //deve avere un titolo
    if(inserisciTitolo->text().isEmpty())
        return "Devi inserire un titolo!";
    //non puo' esistere un attivita selezionata che deve ancora avvenire
    if(boxStato->isChecked()&&QDate::currentDate().daysTo(getDate())<0)
        return "Non puoi completare un attività futura";
    return "";

}

}
}
