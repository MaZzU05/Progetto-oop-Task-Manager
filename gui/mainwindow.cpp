#include "mainwindow.h"
#include<QIcon>
#include<QInputDialog>
#include<QMessageBox>
#include<QFileDialog>
#include<QDir>
#include<QTableWidget>
#include "../modello/Filtri/filtrourgente.h"
#include"finestrainizializzazionelibretto.h"
#include "../modello/Filtri/filtropriorita.h"
#include"../modello/Filtri/filtrocongiuntivo.h"
#include"../modello/Filtri/filtroanno.h"
#include"../modello/Filtri/filtrocompletate.h"
#include"../modello/Filtri/filtrotipo.h"
#include"../modello/Filtri/filtrotag.h"
#include"../modello/Filtri/filtronome.h"
#include"../modello/Filtri/filtrodata.h"
#include"../modello/Filtri/filtromeseanno.h"
namespace gui
{
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setup();
    connectSegnali();

}

void MainWindow::setup()
{
    //preparo menu
    preparaMenuAzioni();
    QWidget* temp=new QWidget();
    setCentralWidget(temp);
    finestraPrincipale=new QStackedWidget(this);
    QHBoxLayout* layout=new QHBoxLayout(temp);
    centrale=new VistaElenco(this);
    finestraPrincipale->addWidget(centrale);
    calendarioCentrale=new VistaCalendario(this);
    finestraPrincipale->addWidget(calendarioCentrale);
    dettaglioCentrale=new VistaDettaglio(this);
    finestraPrincipale->addWidget(dettaglioCentrale);
    librettoCentrale=new VistaLibretto(&gestorePrincipale.getLibretto());
    finestraPrincipale->addWidget(librettoCentrale);
    editCentrale=new VistaEdit(this);
    finestraPrincipale->addWidget(editCentrale);
    barraLaterale=new BarraLateraleWidget(this);
    layout->addWidget(barraLaterale);
    QVBoxLayout* layoutCentrale=new QVBoxLayout();
    QHBoxLayout* layoutBottoni=new QHBoxLayout();
    QHBoxLayout* layoutBottoniVista=new QHBoxLayout();
    layoutBottoniVista->setAlignment(Qt::AlignRight);
    QHBoxLayout* layoutBottoniAzioni=new QHBoxLayout();
    layoutBottoniAzioni->setAlignment(Qt::AlignLeft);
    bottoneVistaLista=new QPushButton(this);
    QIcon iconaLista(":/gui/assets/icona_lista.png");
    bottoneVistaLista->setIcon(iconaLista);
    bottoneVistaLista->setIconSize(QSize(24,24));
    bottoneVistaLista->setToolTip("Vista ad elenco"); //aggiunge il testo informativo quando vi si passa sopra
    layoutBottoniVista->addWidget(bottoneVistaLista);
    bottoneVistaCalendario=new QPushButton(this);
    QIcon iconaCalendario(":/gui/assets/icona_calendario.png");
    bottoneVistaCalendario->setIcon(iconaCalendario);
    bottoneVistaCalendario->setIconSize(QSize(24,24));
    bottoneVistaCalendario->setToolTip("Vista a Calendario");
    layoutBottoniVista->addWidget(bottoneVistaCalendario);
    bottoneVistaLibretto=new QPushButton(this);
    QIcon iconaLibretto(":/gui/assets/icona_scuola.png");
    bottoneVistaLibretto->setIcon(iconaLibretto);
    bottoneVistaLibretto->setIconSize(QSize(24,24));
    bottoneVistaLibretto->setToolTip("Vista a Libretto");
    layoutBottoniVista->addWidget(bottoneVistaLibretto);
    bottoneAggiungi=new QPushButton(this);
    QIcon iconaAggiungi(":/gui/assets/icona_nuovoElemento.png");
    bottoneAggiungi->setIcon(iconaAggiungi);
    bottoneAggiungi->setIconSize(QSize(24,24));
    bottoneAggiungi->setToolTip("Aggiungi Attività");
    bottoneAggiungi->setShortcut(QKeySequence("Ctrl+N"));//shortcut per aggiungere attivita
    layoutBottoniAzioni->addWidget(bottoneAggiungi);
    bottoneModifica=new QPushButton(this);
    bottoneModifica->setEnabled(false); //di default non cliccabile
    QIcon iconaModifica(":/gui/assets/icona_modificaElemento.png");
    bottoneModifica->setIcon(iconaModifica);
    bottoneModifica->setIconSize(QSize(24,24));
    bottoneModifica->setToolTip("Modifica Attività");
    bottoneModifica->setShortcut(QKeySequence("Ctrl+E"));//shortcut per modificare attivita
    layoutBottoniAzioni->addWidget(bottoneModifica);
    bottoneElimina=new QPushButton(this);
    bottoneElimina->setEnabled(false);
    QIcon iconaElimina(":/gui/assets/icona_rimuoviElemento.png");
    bottoneElimina->setIcon(iconaElimina);
    bottoneElimina->setIconSize(QSize(24,24));
    bottoneElimina->setToolTip("Elimina Attività");
    bottoneElimina->setShortcut(QKeySequence("Ctrl+Backspace"));//shortcut per cancellare attivita
    layoutBottoniAzioni->addWidget(bottoneElimina);
    layoutBottoni->addLayout(layoutBottoniAzioni);
    layoutBottoni->addLayout(layoutBottoniVista);
    layoutCentrale->addLayout(layoutBottoni);
    layoutCentrale->addWidget(finestraPrincipale);
    layout->addLayout(layoutCentrale);
    //provo a dare le dimensioni, 1/5 barra laterale, 4/5 vista centrale
    layout->setStretchFactor(barraLaterale,1);
    layout->setStretchFactor(layoutCentrale,4);
    gestorePrincipale.registraObserver(centrale);
    gestorePrincipale.registraObserver(calendarioCentrale);
    gestorePrincipale.registraObserver(barraLaterale);
    gestorePrincipale.registraObserver(librettoCentrale);
    applicaFiltri(); //serve per creare il filtro iniziale vuoto e notificare tutte le viste
}

void MainWindow::preparaMenuAzioni()
{
    menuFile=this->menuBar()->addMenu("File");
    azioneSalva=new QAction("Salva", this);
    azioneSalva->setIcon(QIcon(":/gui/assets/icona_salvataggio.png"));
    azioneSalva->setShortcut(QKeySequence::Save);//per le shortcut piu' comuni uso il selettore automatico
    azioneSalva->setShortcutVisibleInContextMenu(true); //per vedere la shortcut scritta in parte all'elemento grafico
    azioneCarica=new QAction("Carica", this);
    azioneCarica->setIcon(QIcon(":/gui/assets/icona_apertura.png"));
    azioneCarica->setShortcut(QKeySequence::Open);
    azioneCarica->setShortcutVisibleInContextMenu(true);
    menuFile->addAction(azioneSalva);
    menuFile->addAction(azioneCarica);
    //creo un menu con azioni non cliccabili che saranno delle voci che rappresentano tutte le scorciatoie da tastiera
    menuAiuto=this->menuBar()->addMenu("Aiuto");
    QMenu* sottoMenuScorciatoie=menuAiuto->addMenu("Scorciatoie da tastiera");
    sottoMenuScorciatoie->setIcon(QIcon(":/gui/assets/icona_info.png"));
    QAction* voceSalva=new QAction("Salva Ctrl+S");
    voceSalva->setEnabled(false);//non cliccabile
    sottoMenuScorciatoie->addAction(voceSalva);
    QAction* voceCarica=new QAction("Carica Ctrl+O");
    voceCarica->setEnabled(false);
    sottoMenuScorciatoie->addAction(voceCarica);
    QAction* voceAggiungi=new QAction("Aggiungi Attivita Ctrl+N");
    voceAggiungi->setEnabled(false);
    sottoMenuScorciatoie->addAction(voceAggiungi);
    QAction* voceElimina=new QAction("Elimina Attivita Selezionata Ctrl+Backspace");
    voceElimina->setEnabled(false);
    sottoMenuScorciatoie->addAction(voceElimina);
    QAction* voceModifica=new QAction("Modifica Attivita Selezionata Ctrl+E");
    voceModifica->setEnabled(false);
    sottoMenuScorciatoie->addAction(voceModifica);
}

bool MainWindow::salvataggio()
{
    //con QFileDialog salvo il path selezionato da un utente con una stringa, che passero' al gestore per il salvataggio vero e proprio
    QString percorsoSalvataggio=QFileDialog::getSaveFileName(this, "Salva l'agenda", QDir::homePath(), "File JSON (*.json)"); //indico come directory di partenza la home, e come formato per il salvataggio il json
    //verifico se l'utente ha scelto o ha premuto annulla
    if(percorsoSalvataggio.isEmpty())
    {
        QMessageBox::warning(this, "Operazione annullata", "File non salvato");
        return false;
    }
    else
    {
        if(gestorePrincipale.salva(percorsoSalvataggio))
        {
            QMessageBox::information(this, "File salvato", "Operazione avvenuta con successo");
            return true;
        }
        else
        {
            QMessageBox::critical(this, "Errore", "File non salvato, riprova");
            return false;
        }
    }

}

void MainWindow::caricaAgenda()
{
    // Verifico se ci sono dati non salvati prima di caricare un nuovo file
    if(gestorePrincipale.haModificheNonSalvate())
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Attenzione");
        msgBox.setText("Ci sono modifiche non salvate. Caricando un nuovo file, perderai i dati correnti. Vuoi salvare prima di procedere?");
        QPushButton *bottoneSalva = msgBox.addButton("Salva", QMessageBox::AcceptRole);
        msgBox.addButton("Continua senza salvare", QMessageBox::DestructiveRole); //dato che il bottone continua lo creo solo per farlo visualizzare, non mi serve controllare che sia stato premuto o altro, dunque non mi serve salvarlo
        QPushButton *bottoneAnnulla = msgBox.addButton("Annulla", QMessageBox::RejectRole);
        
        msgBox.exec();

        if (msgBox.clickedButton() == bottoneSalva) {
            if (!salvataggio()) {
                return; // Se fallisce o annulla il salvataggio, blocco il caricamento
            }
        } else if (msgBox.clickedButton() == bottoneAnnulla) {
            return; // L'utente ha annullato l'operazione
        }
    }

    QString percorsoFile=QFileDialog::getOpenFileName(this, "Carica l'agenda", QDir::homePath(), "File JSON (*.json)"); //analogo al salvataggio, sta volta per il caricamento
    if(percorsoFile.isEmpty())
    {
        QMessageBox::warning(this, "Operazione annullata", "File non caricato");
    }
    else
    {
        if(gestorePrincipale.carica(percorsoFile))
        {

            QMessageBox::information(this, "File Caricato", "Operazione avvenuta con successo");
        }
        else
        {
            QMessageBox::critical(this, "Errore", "File non caricato correttamente, riprova");
        }
    }
}

void MainWindow::connectSegnali()
{
    //per ogni cambio vista imposto l'indice corrispondente, per tutte le viste mostro la barra laterale di ricerca, tranne per la vistaDettaglio e la vistaLibretto, dunque nelle altre la setto sempre visible, e viceversa
    connect(bottoneVistaLista, &QPushButton::pressed, this, [this](){
        barraLaterale->setVisible(true);
        //mostro i bottoni di modifica ecc
        bottoneAggiungi->setVisible(true);
        bottoneModifica->setVisible(true);
        bottoneElimina->setVisible(true);
        finestraPrincipale->setCurrentIndex(0);
    });
    connect(bottoneVistaCalendario, &QPushButton::pressed, this, [this](){
        barraLaterale->setVisible(true);
        //nascondo i bottoni di modifica ecc
        bottoneAggiungi->setVisible(false);
        bottoneModifica->setVisible(false);
        bottoneElimina->setVisible(false);
     finestraPrincipale->setCurrentIndex(1);
    });
    connect(bottoneVistaLibretto, &QPushButton::clicked, this, [this](){
        modello::Libretto& libretto=gestorePrincipale.getLibretto();
        if(libretto.getCfu()==0)
        {
            //creo e lancio la finestra di selezione
            FinestraInizializzazioneLibretto finestraLibretto(this);
            if(finestraLibretto.exec()==QDialog::Accepted)
            {

                gestorePrincipale.inizializzaLibretto(finestraLibretto.getNomeCorso(), finestraLibretto.getCFU());
                finestraPrincipale->setCurrentIndex(3);
                //nascondo i bottoni di modifica ecc
                bottoneAggiungi->setVisible(false);
                bottoneModifica->setVisible(false);
                bottoneElimina->setVisible(false);
                barraLaterale->setVisible(false);
            }
            else
            {
                QMessageBox::warning(this, "Operazione bloccata", "Non e' possibile accedere a questa pagina senza selezionare la tipologia di laurea");

            }
        }
        else
        {
            finestraPrincipale->setCurrentIndex(3);
            bottoneAggiungi->setVisible(false);
            bottoneModifica->setVisible(false);
            bottoneElimina->setVisible(false);
            barraLaterale->setVisible(false);
        }

    });
    connect(bottoneAggiungi, &QPushButton::clicked, this, [this](){
        editCentrale->impostaPerCreazione(gestorePrincipale.generaNuovoId());
        finestraPrincipale->setCurrentIndex(4);
        //nascondo parti da non visualizzare
        bottoneAggiungi->setVisible(false);
        bottoneModifica->setVisible(false);
        bottoneElimina->setVisible(false);
        barraLaterale->setVisible(false);
    });
    connect(bottoneModifica, &QPushButton::clicked, this, [this](){
        if(attivitaSelezionata)
            {
            editCentrale->impostaPerModifca(attivitaSelezionata);
            finestraPrincipale->setCurrentIndex(4);
            //nascondo parti da non visualizzare
            bottoneAggiungi->setVisible(false);
            bottoneModifica->setVisible(false);
            bottoneElimina->setVisible(false);
            barraLaterale->setVisible(false);
        }
    });
    connect(bottoneElimina, &QPushButton::clicked, this, [this](){
        if(attivitaSelezionata)
            {
            //chiedo conferma dell'eliminazione
            QMessageBox::StandardButton risposta= QMessageBox::question(this, "Conferma Eliminazione", "Sei sicuro di voler eliminare definitivamente questa attività?");
            //guardo se ha selezionato yes
            if(risposta==QMessageBox::Yes)
            {
                gestorePrincipale.removeAttivita(attivitaSelezionata->getID());
                attivitaSelezionata=nullptr;
                bottoneModifica->setEnabled(false);
                bottoneElimina->setEnabled(false);
                finestraPrincipale->setCurrentIndex(0); //se sono nella vista dettaglio, dato che si svuota, mi sposto nella vista elemco
                //e rendo visibili le parti nascoste
                barraLaterale->setVisible(true);
                bottoneAggiungi->setVisible(true);

            }
        }
    });
    connect(editCentrale, &VistaEdit::operazioneConfermata, this, [this](modello::Attivita* a){
        gestorePrincipale.removeAttivita(a->getID()); //se sto creando non fa nulla e va bene cosi
        attivitaSelezionata=nullptr;
        bottoneModifica->setEnabled(false);
        bottoneElimina->setEnabled(false);
        gestorePrincipale.addAttivita(a);
        finestraPrincipale->setCurrentIndex(0);//va alla vista elenco
        // e reimposta le parti visibili
        barraLaterale->setVisible(true);
        bottoneAggiungi->setVisible(true);
        bottoneModifica->setVisible(true);
        bottoneElimina->setVisible(true);

    });
    connect(editCentrale, &VistaEdit::operazioneAnnulata, this, [this]()
            {
        finestraPrincipale->setCurrentIndex(0);//va alla vista elenco
        // e reimposta le parti visibili
        barraLaterale->setVisible(true);
        bottoneAggiungi->setVisible(true);
        bottoneModifica->setVisible(true);
        bottoneElimina->setVisible(true);

    });
    //per abilitare i bottoni di modifica ed elimina in vistaElenco
    connect(centrale, &VistaElenco::attivitaSelezionata, this, &MainWindow::modificaSelezionata);
  //come sopra ma per la vista dettaglio
    connect(dettaglioCentrale, &VistaDettaglio::attivitaSelezionata, this, &MainWindow::modificaSelezionata);

    connect(calendarioCentrale, &VistaCalendario::attivitaSelezionata, this, [this](modello::Attivita* a) {
        barraLaterale->setVisible(false);
        dettaglioCentrale->mostraAttivita(a);
        //mostro i bottoni di modifica ecc ma non quello di aggiunta
        bottoneAggiungi->setVisible(false);
        bottoneModifica->setVisible(true);
        bottoneElimina->setVisible(true);
        finestraPrincipale->setCurrentIndex(2);
    });
    //per ritornare alla vista calendario dalla vista dettaglio
    connect(dettaglioCentrale, &VistaDettaglio::tornaIndietro, this, [this](){
        barraLaterale->setVisible(true);
        //nascondo i bottoni di modifica ecc
        bottoneAggiungi->setVisible(false);
        bottoneModifica->setVisible(false);
        bottoneElimina->setVisible(false);
        finestraPrincipale->setCurrentIndex(1);
    });
    //per ricerca real-time, ogni variazione nei filtri attiva il segnale
    connect(barraLaterale, &BarraLateraleWidget::filtriCambiati, this, &MainWindow::applicaFiltri);
    //per salvare
    connect(azioneSalva, &QAction::triggered, this, [this](){
        salvataggio();
    });
    //per caricare i file
    connect(azioneCarica, &QAction::triggered, this, [this](){
        caricaAgenda();
    });
}

void MainWindow::applicaFiltri()
{
    //lavoro per filtro congiuntivo, per ogni filtro utilizzato, lo aggiungo al filtro congiuntivo
    modello::filtro::FiltroCongiuntivo* congiuntivo= new modello::filtro::FiltroCongiuntivo();;
    modello::filtro::FiltroNome* perNome=new modello::filtro::FiltroNome(barraLaterale->getTestoRicerca());
    congiuntivo->addFiltro(perNome);
    QString tipoSelezionato=barraLaterale->getTipoSelezionato();
    if(tipoSelezionato!="Tutte")
    {modello::filtro::FiltroTipo* perTipo;
      if(tipoSelezionato=="Appuntamento")
        {

            perTipo=new modello::filtro::FiltroTipo(modello::filtro::FiltroTipo::ricercaTipo::cercaAppuntamento);
        }
        else if(tipoSelezionato=="Esame")
        {
            perTipo=new modello::filtro::FiltroTipo(modello::filtro::FiltroTipo::ricercaTipo::cercaEsame);
        }
        else if(tipoSelezionato=="Scadenza")
        {
            perTipo=new modello::filtro::FiltroTipo(modello::filtro::FiltroTipo::ricercaTipo::cercaScadenza);
        }
        else
        {
            perTipo=new modello::filtro::FiltroTipo(modello::filtro::FiltroTipo::ricercaTipo::cercaSport);
        }
        congiuntivo->addFiltro(perTipo);
    }
    QString stato=barraLaterale->getStatoSelezionato();
    if(stato!="Tutte")
      {
        modello::filtro::FiltroCompletate* completate;
        if(stato=="Completate")
        {
            completate=new modello::filtro::FiltroCompletate(true);
        }
        else
        {
            completate=new modello::filtro::FiltroCompletate(false);
        }
        congiuntivo->addFiltro(completate);
      }
    QString urgenza=barraLaterale->getUrgenzaSelezionata();
      if(urgenza!="Tutte")
    {
        modello::filtro::FiltroUrgente* urgente;
        if(urgenza=="Urgente")
          {
            urgente=new modello::filtro::FiltroUrgente(true);
        }
        else
        {
            urgente=new modello::filtro::FiltroUrgente(false);
        }
        congiuntivo->addFiltro(urgente);
      }
    QString priorita=barraLaterale->getPrioritaSelezionata();
      if(priorita!="Tutte")
      {
        modello::filtro::FiltroPriorita* perPriorita;
        if(priorita=="Alta")
          {
            perPriorita=new modello::filtro::FiltroPriorita(modello::Priority::alta);

          }
        else if(priorita=="Media")
          {
            perPriorita=new modello::filtro::FiltroPriorita(modello::Priority::media);
          }
        else
          {
             perPriorita=new modello::filtro::FiltroPriorita(modello::Priority::bassa);
          }
          congiuntivo->addFiltro(perPriorita);
      }
      //aggiungo il filtro per anno solo se il filtro meseAnno e il filtroData non sono attivi, mi basta verificarli secondo questo ordine
      if(barraLaterale->isFiltroDataOn())
      {
          modello::filtro::FiltroData* perData=new modello::filtro::FiltroData(barraLaterale->getDataSelezionata());
          congiuntivo->addFiltro(perData);
      }
      else if(barraLaterale->isFiltroMeseAnnoOn())
      {
          modello::filtro::FiltroMeseAnno* perMeseAnno=new modello::filtro::FiltroMeseAnno(static_cast<modello::filtro::MeseTarget>(barraLaterale->getMeseSelezionato()), barraLaterale->getAnnoSelezionato());
          congiuntivo->addFiltro(perMeseAnno);
      }
      else       if(barraLaterale->isFiltroAnnoOn())
      {
          modello::filtro::FiltroAnno* perAnno=new modello::filtro::FiltroAnno(barraLaterale->getAnnoSelezionato());
          congiuntivo->addFiltro(perAnno);
      }
      std::vector<QString> tag=barraLaterale->getTagSelezionati();
      //scorro tutti i tag selezionati, e per ogniuno aggiungo un filtro tag al filtro congiuntivo
      for(const QString& t:tag)
      {
          modello::filtro::FiltroTag* perTag=new modello::filtro::FiltroTag(t);
          congiuntivo->addFiltro(perTag);
      }
      gestorePrincipale.setFiltro(congiuntivo);

}

void MainWindow::modificaSelezionata(modello::Attivita* a)
{
    //se e' un attivita selezionata
    if(a)
    {
        bottoneModifica->setEnabled(true);
        bottoneElimina->setEnabled(true);
        attivitaSelezionata=a;
    }
    else
    {
        //altrimenti deseleziono
        bottoneModifica->setEnabled(false);
        bottoneElimina->setEnabled(false);
        attivitaSelezionata=a;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (gestorePrincipale.haModificheNonSalvate()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Modifiche non salvate");
        msgBox.setText("Ci sono modifiche non salvate. Vuoi salvare prima di uscire?");
        
        // Uso bottoni personalizzati per avere i testi in italiano
        QPushButton *bottoneSalva = msgBox.addButton("Salva", QMessageBox::AcceptRole);
        QPushButton *bottoneScarta = msgBox.addButton("Non Salvare", QMessageBox::DestructiveRole);
        msgBox.addButton("Annulla", QMessageBox::RejectRole);//non mi serve salvarlo su puntatore, dato che mi serve solo che compaia
        msgBox.exec();

        if (msgBox.clickedButton() == bottoneSalva) {
            if (salvataggio()) {
                event->accept();
            } else {
                event->ignore(); // Se l'utente annulla il salvataggio o fallisce
            }
        } else if (msgBox.clickedButton() == bottoneScarta) {
            event->accept(); // Esce senza salvare
        } else {
            event->ignore(); // Annulla la chiusura
        }
    } else {
        event->accept();
    }
}

}
