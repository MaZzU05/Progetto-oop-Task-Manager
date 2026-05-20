#include "vistadettaglio.h"
#include "Card/cardactivityvisitor.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
namespace gui {
VistaDettaglio::VistaDettaglio(QWidget *parent) : QWidget(parent) { setup(); }

void VistaDettaglio::setup() {
  layout = new QVBoxLayout(this);
  QHBoxLayout *layoutAlto = new QHBoxLayout();
  layoutAlto->setAlignment(Qt::AlignLeft);
  QPushButton *backButton = new QPushButton(this);
  QIcon backIcon(":/gui/assets/freccia_sx.png");
  backButton->setIcon(backIcon);
  backButton->setIconSize(
      QSize(24, 24)); // la ingrandisco leggermente, qt la faceva troppo piccola
  layoutAlto->addWidget(backButton);
  connect(backButton, &QPushButton::pressed, this,
          &VistaDettaglio::tornaIndietro);
  layout->addLayout(layoutAlto);
  areaScorrimento = new QScrollArea(this);
  areaScorrimento->setFrameShape(QFrame::NoFrame);
  layout->addWidget(areaScorrimento);
  contenitoreCentrale = new QWidget(this);
  layoutCentrale = new QVBoxLayout(contenitoreCentrale);
  layoutCentrale->setAlignment(Qt::AlignTop);
  areaScorrimento->setWidget(contenitoreCentrale);
  areaScorrimento->setWidgetResizable(true);
}

void VistaDettaglio::setWidget(QWidget *nuovaCard) {
  QLayoutItem *daEliminare;
  // uso il while anche se ho un solo elemento, cosi' e' gia' robusta per
  // eventuali modifiche
  while ((daEliminare = layoutCentrale->takeAt(0)) != nullptr) {
    QWidget *elementoInterno = daEliminare->widget();
    delete elementoInterno;
    delete daEliminare;
  }
  layoutCentrale->addWidget(nuovaCard);
}

void VistaDettaglio::mostraAttivita(modello::Attivita *a) {
  // replico il pattern per la emit di VistaElenco, rivolto ad una singola
  // attivita
  attivitaCorrente = a;
  card::CardActivityVisitor visitor;
  attivitaCorrente->accept(&visitor);
  card::CardAttivita *cardDaVisualizzare = visitor.getWidget();
  setWidget(cardDaVisualizzare);
  connect(cardDaVisualizzare, &card::CardAttivita::selezionata, this,
          [this, a](card::CardAttivita *, bool espansa) {
            if (espansa) {
              // lo dico alla mainWindow
              // emit attivitaSelezionata(a);
              Q_EMIT attivitaSelezionata(a);
            } else {
              // la si sta chiudendo
              Q_EMIT attivitaSelezionata(
                  nullptr); // necessario per indicare la deselezione
            }
          });
}
} // namespace gui
