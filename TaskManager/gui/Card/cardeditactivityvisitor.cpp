#include "../modello/esame.h"
#include"../modello/appuntamento.h"
#include"../modello/scadenza.h"
#include"../modello/sport.h"
#include"cardscadenza.h"
#include"cardesame.h"
#include"cardappuntamento.h"
#include"cardsport.h"
#include "cardeditactivityvisitor.h"
namespace gui{
namespace card {

//per ogniuna seguo l'ordine creazione-popolamento-assegnazione alla variabile polimorfa da ritornare
void CardEditActivityVisitor::visit(const modello::Esame* e)
{
    CardEsame* card=new CardEsame();
    card->popola(e);
    cardPronta=card;

}

void CardEditActivityVisitor::visit(const modello::Scadenza* s)
{
    CardScadenza* card=new CardScadenza();
    card->popola(s);
    cardPronta=card;
}

void CardEditActivityVisitor::visit(const modello::Sport* s)
{
    CardSport* card=new CardSport();
    card->popola(s);
    cardPronta=card;
}

void CardEditActivityVisitor::visit(const modello::Appuntamento* a)
{
    CardAppuntamento* card=new CardAppuntamento();
    card->popola(a);
    cardPronta=card;
}

AbstractCardEdit* CardEditActivityVisitor::getCard()
{
    return cardPronta;
}

}
}
