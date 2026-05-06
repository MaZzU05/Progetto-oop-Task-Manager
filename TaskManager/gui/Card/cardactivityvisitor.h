#ifndef CARDACTIVITYVISITOR_H
#define CARDACTIVITYVISITOR_H
#include"cardattivita.h"
#include"../modello/constactivityvisitorinterface.h"
#include"../modello/activityvisitorinterface.h"
namespace gui
{
namespace card
{
//class CardActivityVisitor:public modello::ConstActivityVisitorInterface
class CardActivityVisitor:public modello::ActivityVisitorInterface
{
private:
    CardAttivita* widget=nullptr;
public:
    void visit(modello::Esame* e) override;
    void visit(modello::Scadenza* s) override;
    void visit(modello::Appuntamento* i) override;
    void visit(modello::Sport* s) override;
    CardAttivita* getWidget();
};
}}
#endif // CARDACTIVITYVISITOR_H
