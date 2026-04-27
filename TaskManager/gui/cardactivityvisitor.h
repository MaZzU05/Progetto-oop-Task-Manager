#ifndef CARDACTIVITYVISITOR_H
#define CARDACTIVITYVISITOR_H
#include"cardattivita.h"
#include"../modello/constactivityvisitorinterface.h"
namespace gui
{
class CardActivityVisitor:public modello::ConstActivityVisitorInterface
{
private:
    CardAttivita* widget=nullptr;
public:
    void visit(const modello::Esame* e) override;
    void visit(const modello::Scadenza* s) override;
    void visit(const modello::Appuntamento* i) override;
    void visit(const modello::Sport* s) override;
    CardAttivita* getWidget();
};
}
#endif // CARDACTIVITYVISITOR_H
