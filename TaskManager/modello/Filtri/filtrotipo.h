#ifndef FILTROTIPO_H
#define FILTROTIPO_H
#include"abstractfilter.h"
#include"../constactivityvisitorinterface.h"
namespace modello{
namespace filtro
{
class FiltroTipo:public AbstractFilter
{
public:
    enum class ricercaTipo{cercaEsame, cercaAppuntamento, cercaScadenza, cercaSport};
    //creo un visitor interno per evitare di fare RTTI e per evitare di dover far const cast ereditando direttamente FiltroTipo da ConstActivityVisitor per quanto riguarda la accept, ed mantengo la const correctness senza dover ripristinare un boleano che metto membro del visitor e non della classe stessa
private:
    ricercaTipo tipo_cercato;
    class checkVisitor: public modello::ConstActivityVisitorInterface
    {
        friend class FiltroTipo;
    private:
        bool trovato;
        ricercaTipo tipoTarget;
      public:
        checkVisitor(ricercaTipo tipoTarget);
        void visit(const Esame* e) override;
        void visit(const Scadenza* s) override;
        void visit(const Appuntamento* i) override;
        void visit(const Sport* s) override;
    };
public:

    FiltroTipo(ricercaTipo tipo_cercato);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROTIPO_H
