/*
 * FILE DI TEST - test_modello.cpp
 *
 * Come usarlo:
 *   1) Aggiungi questo file in TaskManager.pro sotto SOURCES
 *   2) Aggiungi  QT += testlib  nel .pro
 *   3) In main.cpp chiama:  return QTest::qExec(new TestModello, argc, argv);
 *      (oppure compila solo questo come target separato)
 *
 * I test NON sono scritti per essere "facili da superare": verificano la logica
 * reale e alcuni casi limite che potrebbero rivelare bug.
 */

#include <QtTest/QtTest>
#include <QDateTime>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>
#include <QTemporaryFile>

#include "modello/esame.h"
#include "modello/scadenza.h"
#include "modello/appuntamento.h"
#include "modello/sport.h"
#include "modello/gestore.h"
#include "modello/jsonsavervisitor.h"
#include "modello/Filtri/filtrocompletate.h"
#include "modello/Filtri/filtronome.h"
#include "modello/Filtri/filtropriorita.h"
#include "modello/Filtri/filtrotipo.h"

using namespace modello;

class TestModello : public QObject
{
    Q_OBJECT

// ─────────────────────────────────────────────────────────────────────────────
// Helper per costruire oggetti comuni
// ─────────────────────────────────────────────────────────────────────────────
private:
    QDateTime futuro(int giorniDaOggi, int ore = 10) const
    {
        return QDateTime(QDate::currentDate().addDays(giorniDaOggi),
                         QTime(ore, 0));
    }

    Esame* creaEsame(int giorniAllaData = 30,
                     unsigned int cfu = 6,
                     Priority p = Priority::bassa) const
    {
        return new Esame("Analisi", 1, "", "Aula 1", cfu,
                         futuro(giorniAllaData), 90, false, p);
    }

    Scadenza* creaScadenza(int giorniAllaData = 10,
                           unsigned int preavviso = 3) const
    {
        return new Scadenza("Progetto", 2, "", futuro(giorniAllaData),
                            preavviso);
    }

    Appuntamento* creaAppuntamento(int giorniAllaData = 5,
                                   bool inPresenza = true) const
    {
        return new Appuntamento("Meeting", 3, "", futuro(giorniAllaData),
                                "Sala A", 60, inPresenza);
    }

    Sport* creaSport(int giorniAlFine = 30) const
    {
        return new Sport("Nuoto", 4, "", futuro(giorniAlFine), 60,
                         QDate::currentDate(), "Piscina");
    }

// ─────────────────────────────────────────────────────────────────────────────
private slots:

    // =========================================================================
    // ESAME
    // =========================================================================

    void esame_costruttore_votoDefault()
    {
        Esame* e = creaEsame();
        // Il voto deve essere 0 per default all'atto della costruzione
        QCOMPARE(e->getVoto(), 0u);
        // Un esame appena creato non è passato
        QVERIFY(!e->isPassed());
        // Un esame appena creato non ha lode
        QVERIFY(!e->hasLode());
        delete e;
    }

    void esame_setVoto_valido()
    {
        Esame* e = creaEsame();
        bool ok = e->setVoto(28);
        QVERIFY(ok);
        QCOMPARE(e->getVoto(), 28u);
        // setVoto deve settare complete automaticamente
        QVERIFY(e->isComplete());
        // 28 < 30 → lode deve essere false anche se era stata impostata prima
        QVERIFY(!e->hasLode());
        delete e;
    }

    void esame_setVoto_invalido()
    {
        Esame* e = creaEsame();
        bool ok = e->setVoto(31); // voto fuori range
        QVERIFY(!ok);
        QCOMPARE(e->getVoto(), 0u); // non deve cambiare
        delete e;
    }

    void esame_lode_soloConVoto30()
    {
        Esame* e = creaEsame();
        e->setVoto(28);
        e->modifyLode(true); // non deve funzionare: voto != 30
        QVERIFY(!e->hasLode());

        e->setVoto(30);
        e->modifyLode(true);
        QVERIFY(e->hasLode());

        // Se si rimette un voto != 30 la lode deve sparire
        e->setVoto(29);
        QVERIFY(!e->hasLode());
        delete e;
    }

    void esame_professor_addRemove()
    {
        Esame* e = creaEsame();
        e->addProfessor("Rossi");
        e->addProfessor("Bianchi");
        // Duplicato: non deve essere aggiunto
        e->addProfessor("Rossi");
        QCOMPARE((int)e->getAllProf().size(), 2);

        bool removed = e->removeProfessor("Rossi");
        QVERIFY(removed);
        QCOMPARE((int)e->getAllProf().size(), 1);

        // Rimozione elemento non presente
        bool removedMissing = e->removeProfessor("Verdi");
        QVERIFY(!removedMissing);
        delete e;
    }

    void esame_isUrgente_completoNonUrgente()
    {
        Esame* e = creaEsame(5, 6, Priority::alta);
        e->setVoto(28); // lo completo
        // Un esame completato NON deve mai essere urgente
        QVERIFY(!e->isUrgente());
        delete e;
    }

    void esame_isUrgente_passato()
    {
        // Esame con data passata e non completato → urgente
        Esame* e = creaEsame(-1, 6, Priority::bassa);
        QVERIFY(e->isUrgente());
        delete e;
    }

    void esame_changeCfu_zeroIgnorato()
    {
        Esame* e = creaEsame(30, 9);
        e->changeCfu(0); // 0 CFU non ha senso, deve essere ignorato
        QCOMPARE(e->getCFU(), 9u);
        e->changeCfu(12);
        QCOMPARE(e->getCFU(), 12u);
        delete e;
    }

    // =========================================================================
    // SCADENZA
    // =========================================================================

    void scadenza_todoList_addECount()
    {
        Scadenza* s = creaScadenza();
        s->addPassaggio("Scrivi introduzione");
        s->addPassaggio("Scrivi conclusione");
        QCOMPARE(s->getNumPassaggiTotali(), 2u);
        QCOMPARE(s->getNumPassaggiCompletati(), 0u);
        delete s;
    }

    void scadenza_todoList_completaPassaggio()
    {
        Scadenza* s = creaScadenza();
        s->addPassaggio("A");
        s->addPassaggio("B");
        s->setPassaggioCompletato("A", true);
        QCOMPARE(s->getNumPassaggiCompletati(), 1u);
        QCOMPARE((int)s->getPassaggiCompletati().size(), 1);
        QCOMPARE((int)s->getPassaggiNonCompletati().size(), 1);
        delete s;
    }

    void scadenza_isUrgente_altaPriorita()
    {
        // Priority::alta → sempre urgente se non completata
        Scadenza* s = new Scadenza("X", 1, "", futuro(100), 5, 0,
                                   false, Priority::alta);
        QVERIFY(s->isUrgente());
        delete s;
    }

    void scadenza_isUrgente_completaNonUrgente()
    {
        Scadenza* s = new Scadenza("X", 1, "", futuro(100), 5, 0, true);
        QVERIFY(!s->isUrgente());
        delete s;
    }

    // =========================================================================
    // APPUNTAMENTO
    // =========================================================================

    void appuntamento_addPartecipante_mailValida()
    {
        Appuntamento* a = creaAppuntamento();
        QVERIFY(a->addPartecipante("mario.rossi@example.com"));
        QCOMPARE((int)a->getAllPartecipanti().size(), 1);
        delete a;
    }

    void appuntamento_addPartecipante_stringaNonMail()
    {
        Appuntamento* a = creaAppuntamento();
        // Una stringa senza @ non è una mail valida
        QVERIFY(!a->addPartecipante("mariorossi"));
        QCOMPARE((int)a->getAllPartecipanti().size(), 0);
        delete a;
    }

    void appuntamento_addPartecipante_mailSenzaDominio()
    {
        Appuntamento* a = creaAppuntamento();
        QVERIFY(!a->addPartecipante("user@"));
        QCOMPARE((int)a->getAllPartecipanti().size(), 0);
        delete a;
    }

    void appuntamento_addPartecipante_noDuplicati()
    {
        Appuntamento* a = creaAppuntamento();
        a->addPartecipante("x@y.it");
        a->addPartecipante("x@y.it"); // duplicato
        QCOMPARE((int)a->getAllPartecipanti().size(), 1);
        delete a;
    }

    void appuntamento_removePartecipante()
    {
        Appuntamento* a = creaAppuntamento();
        a->addPartecipante("x@y.it");
        a->removePartecipante("x@y.it");
        QCOMPARE((int)a->getAllPartecipanti().size(), 0);
        delete a;
    }

    void appuntamento_isUrgente_completoNonUrgente()
    {
        Appuntamento* a = new Appuntamento("M", 1, "", futuro(0, 1),
                                           "Qui", 30, true, true, Priority::alta);
        QVERIFY(!a->isUrgente());
        delete a;
    }

    void appuntamento_isUrgente_passato()
    {
        // Data passata e non completato → urgente
        Appuntamento* a = new Appuntamento("M", 1, "", futuro(-1),
                                           "Qui", 30, true, false, Priority::bassa);
        QVERIFY(a->isUrgente());
        delete a;
    }

    // =========================================================================
    // SPORT
    // =========================================================================

    void sport_setRemoveGiorno()
    {
        Sport* s = creaSport();
        s->setGiornoSettimana(Qt::Monday);
        s->setGiornoSettimana(Qt::Wednesday);
        // Duplicato: non deve essere aggiunto
        s->setGiornoSettimana(Qt::Monday);
        QCOMPARE((int)s->getAllGiorniSettimanali().size(), 2);

        s->removeGiornoSettimana(Qt::Monday);
        QCOMPARE((int)s->getAllGiorniSettimanali().size(), 1);
        QVERIFY(!s->isGiornoAllenamento(Qt::Monday));
        delete s;
    }

    void sport_avvieneInData_inRange()
    {
        QDate oggi = QDate::currentDate();
        QDate dopodomani = oggi.addDays(2);
        Sport* s = new Sport("Calcio", 1, "",
                             QDateTime(oggi.addDays(7), QTime(18, 0)),
                             60, oggi, "Campo");
        Qt::DayOfWeek giornoDopodomani =
            static_cast<Qt::DayOfWeek>(dopodomani.dayOfWeek());
        s->setGiornoSettimana(giornoDopodomani);
        QVERIFY(s->avvieneInData(dopodomani));
        delete s;
    }

    void sport_avvieneInData_fuoriRange()
    {
        QDate oggi = QDate::currentDate();
        Sport* s = new Sport("Calcio", 1, "",
                             QDateTime(oggi.addDays(3), QTime(18, 0)),
                             60, oggi.addDays(1), "Campo");
        s->setGiornoSettimana(Qt::Monday);
        // oggi è prima di dataInizio → non avviene
        QVERIFY(!s->avvieneInData(oggi));
        delete s;
    }

    // =========================================================================
    // GESTORE
    // =========================================================================

    void gestore_addRemoveAttivita()
    {
        Gestore g;
        Esame* e = creaEsame();
        g.addAttivita(e); // prende ownership
        QCOMPARE((int)g.getAllAttivita().size(), 1);

        bool removed = g.removeAttivita(1);
        QVERIFY(removed);
        QCOMPARE((int)g.getAllAttivita().size(), 0);
    }

    void gestore_removeAttivita_idInesistente()
    {
        Gestore g;
        bool removed = g.removeAttivita(999);
        QVERIFY(!removed);
    }

    void gestore_generaNuovoId_daList()
    {
        Gestore g;
        QCOMPARE(g.generaNuovoId(), 1u); // lista vuota → 1
        g.addAttivita(new Esame("A", 5, "", "X", 6, futuro(10), 60));
        QCOMPARE(g.generaNuovoId(), 6u); // max id = 5 → nuovo = 6
    }

    void gestore_noDuplicati()
    {
        Gestore g;
        Esame* e = creaEsame();
        g.addAttivita(e);
        g.addAttivita(e); // stesso puntatore: non deve essere aggiunto due volte
        QCOMPARE((int)g.getAllAttivita().size(), 1);
    }

    void gestore_copyConstructor_deepCopy()
    {
        Gestore g1;
        g1.addAttivita(creaEsame());
        Gestore g2(g1);
        // Le liste devono avere la stessa dimensione...
        QCOMPARE(g1.getAllAttivita().size(), g2.getAllAttivita().size());
        // ...ma i puntatori devono essere diversi (deep copy)
        QVERIFY(g1.getAllAttivita()[0] != g2.getAllAttivita()[0]);
    }

    void gestore_operatorAssign_deepCopy()
    {
        Gestore g1;
        g1.addAttivita(creaEsame());
        Gestore g2;
        g2 = g1;
        QCOMPARE(g1.getAllAttivita().size(), g2.getAllAttivita().size());
        QVERIFY(g1.getAllAttivita()[0] != g2.getAllAttivita()[0]);
    }

    void gestore_salvaCarica_roundtrip()
    {
        // Crea file temporaneo per il test
        QTemporaryFile tmpFile;
        tmpFile.setFileTemplate(QDir::tempPath() + "/test_XXXXXX.json");
        QVERIFY(tmpFile.open());
        QString path = tmpFile.fileName();
        tmpFile.close(); // lo chiudiamo, userà il Gestore

        Gestore g1;

        // Esame
        Esame* e = new Esame("Analisi", 1, "nota", "Aula 1", 9,
                             QDateTime(QDate(2026,6,15), QTime(9,0)), 120,
                             false, Priority::media);
        e->setVoto(28);
        e->addProfessor("Rossi");
        e->addTag("matematica");
        g1.addAttivita(e);

        // Scadenza
        Scadenza* s = new Scadenza("Progetto", 2, "", futuro(20), 5, 0,
                                   false, Priority::bassa);
        s->addPassaggio("Capitolo 1");
        s->setPassaggioCompletato("Capitolo 1", true);
        g1.addAttivita(s);

        // Appuntamento
        Appuntamento* a = new Appuntamento("Meeting", 3, "", futuro(3),
                                           "Sala B", 60, true, false, Priority::alta);
        a->addPartecipante("x@y.it");
        g1.addAttivita(a);

        // Sport
        Sport* sp = new Sport("Nuoto", 4, "", futuro(60), 90,
                              QDate::currentDate(), "Piscina",
                              false, Priority::bassa);
        sp->setGiornoSettimana(Qt::Tuesday);
        sp->setGiornoSettimana(Qt::Thursday);
        g1.addAttivita(sp);

        // Salva
        QVERIFY(g1.salva(path));

        // Carica in un gestore nuovo
        Gestore g2;
        QVERIFY(g2.carica(path));

        // Numero attività
        QCOMPARE(g1.getAllAttivita().size(), g2.getAllAttivita().size());

        // Verifica Esame
        Attivita* loadedE = g2.getAttivitaById(1);
        QVERIFY(loadedE != nullptr);
        QCOMPARE(loadedE->getTitle(), QString("Analisi"));
        QCOMPARE(loadedE->getPriority(), Priority::media);
        Esame* loadedEsame = dynamic_cast<Esame*>(loadedE);
        QVERIFY(loadedEsame != nullptr);
        QCOMPARE(loadedEsame->getVoto(), 28u);
        QCOMPARE((int)loadedEsame->getAllProf().size(), 1);
        QCOMPARE((int)loadedE->getAllTag().size(), 1);

        // Verifica Scadenza
        Attivita* loadedS = g2.getAttivitaById(2);
        QVERIFY(loadedS != nullptr);
        Scadenza* loadedSc = dynamic_cast<Scadenza*>(loadedS);
        QVERIFY(loadedSc != nullptr);
        QCOMPARE(loadedSc->getNumPassaggiTotali(), 1u);
        QCOMPARE(loadedSc->getNumPassaggiCompletati(), 1u);

        // Verifica Appuntamento
        Attivita* loadedA = g2.getAttivitaById(3);
        QVERIFY(loadedA != nullptr);
        Appuntamento* loadedApp = dynamic_cast<Appuntamento*>(loadedA);
        QVERIFY(loadedApp != nullptr);
        QVERIFY(loadedApp->isInPresenza());
        // ATTENZIONE: addPartecipante usa la regex → se la mail non passa, size=0
        // Questo test può rivelare il bug discusso nella revisione
        QCOMPARE((int)loadedApp->getAllPartecipanti().size(), 1);

        // Verifica Sport
        Attivita* loadedSp = g2.getAttivitaById(4);
        QVERIFY(loadedSp != nullptr);
        Sport* loadedSport = dynamic_cast<Sport*>(loadedSp);
        QVERIFY(loadedSport != nullptr);
        QCOMPARE((int)loadedSport->getAllGiorniSettimanali().size(), 2);
    }

    // =========================================================================
    // JSON SAVER VISITOR
    // =========================================================================

    void jsonSaver_preparaBase_campiPresenti()
    {
        Esame* e = new Esame("Fisica", 42, "note test", "Aula 3", 6,
                             QDateTime(QDate(2026, 9, 1), QTime(10, 0)),
                             90, false, Priority::alta);
        e->addTag("scienze");
        JsonSaverVisitor v;
        e->accept(&v);
        QJsonObject obj = v.getJsonObject();

        QCOMPARE(obj["Tipo"].toString(), QString("Esame"));
        QCOMPARE(obj["title"].toString(), QString("Fisica"));
        QCOMPARE(obj["id"].toInt(), 42);
        QCOMPARE(obj["note"].toString(), QString("note test"));
        QVERIFY(obj.contains("dataCreazione"));
        QVERIFY(obj.contains("dataFine"));
        QCOMPARE(obj["durata"].toInt(), 90);
        QCOMPARE(obj["priorita"].toInt(), static_cast<int>(Priority::alta));
        QCOMPARE(obj["tag"].toArray().size(), 1);
        delete e;
    }

    void jsonSaver_riutilizzoVisitor_nonAccumula()
    {
        // Verifica che riutilizzare lo stesso visitor NON mescoli i dati
        // (potenziale bug se daSalvare non viene resettato)
        Esame* e = new Esame("Fisica", 1, "", "A", 6, futuro(30), 60);
        Scadenza* s = new Scadenza("Scad", 2, "", futuro(10), 3);

        JsonSaverVisitor v;
        e->accept(&v);
        QJsonObject objE = v.getJsonObject();

        s->accept(&v);
        QJsonObject objS = v.getJsonObject();

        // Dopo aver visitato la Scadenza, il tipo deve essere "Scadenza"
        QCOMPARE(objS["Tipo"].toString(), QString("Scadenza"));
        // e NON deve avere campi tipici di Esame come cfu
        // (se daSalvare non viene pulito tra un visit e l'altro, "cfu" rimane)
        // N.B.: questo test potrebbe FALLIRE se preparaBase non resetta daSalvare
        QVERIFY(!objS.contains("sede"));

        delete e;
        delete s;
    }

    // =========================================================================
    // FILTRI
    // =========================================================================

    void filtroCompletate_filtraCorretti()
    {
        Gestore g;
        Esame* e1 = creaEsame(); // non completato
        Esame* e2 = creaEsame(); e2->setVoto(27); // completato
        e2->getID(); // solo per evitare warning
        // Usiamo id diversi manualmente
        Esame* ec = new Esame("A", 10, "", "X", 6, futuro(10), 60, true);
        Esame* enc = new Esame("B", 11, "", "X", 6, futuro(10), 60, false);
        g.addAttivita(ec);
        g.addAttivita(enc);

        filtro::FiltroCompletate fc(true);
        auto completate = g.filtra(fc);
        QCOMPARE((int)completate.size(), 1);
        QVERIFY(completate[0]->isComplete());

        filtro::FiltroCompletate fnc(false);
        auto nonCompletate = g.filtra(fnc);
        QCOMPARE((int)nonCompletate.size(), 1);
        QVERIFY(!nonCompletate[0]->isComplete());

        delete e1;
        delete e2;
    }

    // =========================================================================
    // CLONE (polimorfismo)
    // =========================================================================

    void clone_tipoPreservato()
    {
        Esame* e = creaEsame();
        Attivita* cloned = e->clone();
        QVERIFY(dynamic_cast<Esame*>(cloned) != nullptr);
        // Il clone deve essere indipendente
        QVERIFY(cloned != e);
        delete e;
        delete cloned;
    }

    void clone_sport_indipendente()
    {
        Sport* s = creaSport();
        s->setGiornoSettimana(Qt::Friday);
        Sport* cloned = s->clone();
        // I giorni devono essere copiati
        QCOMPARE(cloned->getAllGiorniSettimanali().size(),
                 s->getAllGiorniSettimanali().size());
        // Modifica al clone non deve influenzare l'originale
        cloned->setGiornoSettimana(Qt::Saturday);
        QVERIFY(!s->isGiornoAllenamento(Qt::Saturday));
        delete s;
        delete cloned;
    }
};

QTEST_MAIN(TestModello)
#include "test_modello.moc"
