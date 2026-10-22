#ifndef CARDEDITACTIVITYVISITOR_H
#define CARDEDITACTIVITYVISITOR_H

#include "../modello/constactivityvisitorinterface.h"
#include"abstractcardedit.h"
namespace gui{
namespace card{

class CardEditActivityVisitor : public modello::ConstActivityVisitorInterface
{
private:
    AbstractCardEdit* cardPronta;
public:
    void visit(const modello::Esame* e) override;
    void visit(const modello::Scadenza* s) override;
    void visit(const modello::Appuntamento* i) override;
    void visit(const modello::Sport* s) override;
    AbstractCardEdit* getCard();

};
}
}
#endif // CARDEDITACTIVITYVISITOR_H
