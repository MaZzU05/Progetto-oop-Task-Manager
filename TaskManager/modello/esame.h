#ifndef ESAME_H
#define ESAME_H
#include"attivita.h"
#include<QString>
#include<vector>
namespace modello
{
class Esame:public Attivita
{
private:
    unsigned int cfu;
    unsigned int voto;
    bool lode;
    QString sede;
    std::vector<QString> professori;
public:
    Esame(const QString& title,
          const unsigned int id,
          const QString& note,
          const QString& sede,
          const unsigned int cfu,
          const QDateTime& dataEsame,
          bool complete=false,
          Priority priorita=Priority::bassa);
    unsigned int getCFU() const;
    unsigned int getVoto() const;
    bool setVoto(unsigned int); //ritorna true se voto valido (<=30) e lo modifica,  false altrimenti senza modifiche
    bool isPassed() const;
    void changeCfu(unsigned int);
    void modifyLode(bool l);
    bool hasLode() const;
    void setSede(const QString&);
    const QString& getSede() const;
    bool isProfessorIn(const QString&) const;
    void addProfessor(const QString&);
    bool removeProfessor(const QString&);
    void accept(ActivityVisitorInterface* visitor) override;
    void accept(ConstActivityVisitorInterface* visitor) const override;
    bool isUrgente() const override;

};
}
#endif // ESAME_H
