# UML – Lista classi per draw.io

> **Convenzioni notazione UML**
> - `+` pubblico · `-` privato · `#` protetto
> - *corsivo* → metodo/classe **astratto** (in draw.io: spunta la checkbox "italic" sul testo)
> - `«interface»` → interfaccia (stereotipo nel titolo)
> - `«enumeration»` → tipo enumerativo (stereotipo nel titolo)
> - `{abstract}` → annotazione da aggiungere accanto al nome del metodo astratto

---

## `«enumeration»` Priority
*(namespace modello)*

**Valori:**
```
bassa
media
alta
```

---

## `«enumeration»` MeseTarget
*(namespace modello::filtro)*

**Valori:**
```
Gennaio = 1
Febbraio
Marzo
Aprile
Maggio
Giugno
Luglio
Agosto
Settembre
Ottobre
Novembre
Dicembre
```

---

## `«enumeration»` ricercaTipo
*(inner enum di FiltroTipo)*

**Valori:**
```
cercaEsame
cercaAppuntamento
cercaScadenza
cercaSport
```

---

## `«interface»` ActivityVisitorInterface
*(namespace modello)*

**Metodi** (tutti pubblici e astratti — in corsivo):
```
+ ~ActivityVisitorInterface()
+ visit(e : Esame*) : void
+ visit(s : Scadenza*) : void
+ visit(a : Appuntamento*) : void
+ visit(s : Sport*) : void
```

---

## `«interface»` ConstActivityVisitorInterface
*(namespace modello)*

**Metodi** (tutti pubblici e astratti — in corsivo):
```
+ ~ConstActivityVisitorInterface()
+ visit(e : const Esame*) : void
+ visit(s : const Scadenza*) : void
+ visit(a : const Appuntamento*) : void
+ visit(s : const Sport*) : void
```

---

## *Attivita* — classe astratta
*(namespace modello — titolo in corsivo)*

**Attributi:**
```
- title : QString
- id : unsigned int
- note : QString
- complete : bool
- tag : vector<QString>
- dataCreazione : QDateTime
- dataFine : QDateTime
- durata : unsigned int
- priorita : Priority
```

**Metodi:**
```
+ Attivita(title, id, note, dataFine, durata, complete, priorita)
+ ~Attivita()
+ clone() : Attivita*                                      {abstract}
+ getTitle() : const QString&
+ setTitle(tit : const QString&) : void
+ getID() : unsigned int
+ getNote() : const QString&
+ setNote(nota : const QString&) : void
+ getAllTag() : const vector<QString>&
+ addTag(t : const QString&) : void
+ tagIsIn(t : const QString&) : bool
+ getPriority() : Priority
+ changePriority(nuova : Priority) : void
+ isComplete() : bool
+ setComplete(flag : bool) : void
+ changeDate(d : const QDate&) : void
+ changeTime(t : const QTime&) : void
+ changeDataCreazione(dt : const QDateTime&) : void
+ getDate() : const QDateTime&
+ getDataCreazione() : const QDateTime&
+ getDurata() : unsigned int
+ setDurata(d : unsigned int) : void
+ avvieneInData(d : const QDate&) : bool                   {abstract}
+ accept(visitor : ActivityVisitorInterface*) : void       {abstract}
+ accept(visitor : ConstActivityVisitorInterface*) : void  {abstract}
+ isUrgente() : bool                                       {abstract}
```

---

## Appuntamento
*(namespace modello — estende Attivita)*

**Attributi:**
```
- luogo : QString
- inPresenza : bool
- partecipanti : vector<QString>
```

**Metodi:**
```
+ Appuntamento(title, id, note, dataFine, luogo, durata, inPresenza, complete, priorita)
+ clone() : Appuntamento*
+ getLuogo() : const QString&
+ setLuogo(l : const QString&) : void
+ isInPresenza() : bool
+ setPresenza(b : bool) : void
+ addPartecipante(p : const QString&) : bool
+ removePartecipante(p : const QString&) : void
+ getAllPartecipanti() : vector<QString>
+ accept(visitor : ActivityVisitorInterface*) : void
+ accept(visitor : ConstActivityVisitorInterface*) : void
+ isUrgente() : bool
```

---

## Scadenza
*(namespace modello — estende Attivita)*

**Attributi:**
```
- giorniPreavviso : unsigned int
- todoList : vector<SottoTask>
```

**Metodi:**
```
+ Scadenza(title, id, note, dataFine, giorniPreavviso, durata, complete, priorita)
+ clone() : Scadenza*
+ getGiorniPreavviso() : unsigned int
+ setGiorniPreavviso(g : unsigned int) : void
+ addPassaggio(desc : const QString&) : void
+ setPassaggioCompletato(tag_Elemento : const QString&, completato : bool) : void
+ getAllSottoTask() : vector<pair<QString, bool>>
+ getNumPassaggiTotali() : unsigned int
+ getNumPassaggiCompletati() : unsigned int
+ getPassaggiCompletati() : vector<QString>
+ getPassaggiNonCompletati() : vector<QString>
+ accept(visitor : ActivityVisitorInterface*) : void
+ accept(visitor : ConstActivityVisitorInterface*) : void
+ isUrgente() : bool
```

---

## `«inner»` SottoTask
*(inner class di Scadenza)*

**Attributi:**
```
- descrizione : QString
- completa : bool
```

**Metodi:**
```
+ SottoTask(descrizione : const QString&, completa : bool)
```

---

## Esame
*(namespace modello — estende Attivita)*

**Attributi:**
```
- cfu : unsigned int
- voto : unsigned int
- lode : bool
- sede : QString
- professori : vector<QString>
```

**Metodi:**
```
+ Esame(title, id, note, sede, cfu, dataEsame, durata, complete, priorita)
+ clone() : Esame*
+ getCFU() : unsigned int
+ getVoto() : unsigned int
+ setVoto(v : unsigned int) : bool
+ isPassed() : bool
+ changeCfu(c : unsigned int) : void
+ modifyLode(l : bool) : void
+ hasLode() : bool
+ setSede(s : const QString&) : void
+ getSede() : const QString&
+ isProfessorIn(p : const QString&) : bool
+ addProfessor(p : const QString&) : void
+ removeProfessor(p : const QString&) : bool
+ getAllProf() : vector<QString>
+ accept(visitor : ActivityVisitorInterface*) : void
+ accept(visitor : ConstActivityVisitorInterface*) : void
+ isUrgente() : bool
```

---

## Sport
*(namespace modello — estende Attivita)*

**Attributi:**
```
- luogo : QString
- dataInizio : QDate
- giorni_sport : vector<Qt::DayOfWeek>
```

**Metodi:**
```
+ Sport(title, id, note, dataFine, durata, dataInizio, luogo, complete, priorita)
+ clone() : Sport*
+ getLuogo() : const QString&
+ setLuogo(l : const QString&) : void
+ getOraAllenamento() : const QTime
+ setGiornoSettimana(d : Qt::DayOfWeek) : void
+ removeGiornoSettimana(d : Qt::DayOfWeek) : void
+ getAllGiorniSettimanali() : vector<Qt::DayOfWeek>
+ isGiornoAllenamento(d : Qt::DayOfWeek) : bool
+ setDataInizio(d : const QDate&) : void
+ getDataInizio() : QDate
+ accept(visitor : ActivityVisitorInterface*) : void
+ accept(visitor : ConstActivityVisitorInterface*) : void
+ isUrgente() : bool
+ avvieneInData(d : const QDate&) : bool
```

---

## Gestore
*(namespace modello)*

**Attributi:**
```
- listaAttivita : vector<Attivita*>
```

**Metodi:**
```
+ Gestore()
+ ~Gestore()
+ Gestore(g : const Gestore&)
+ operator=(g : const Gestore&) : Gestore&
+ generaNuovoId() : unsigned int
+ addAttivita(a : Attivita*) : void
+ removeAttivita(id : unsigned int) : bool
+ svuota() : void
+ getAllAttivita() : const vector<Attivita*>&
+ getAttivitaById(id : unsigned int) : Attivita*
+ filtra(af : const AbstractFilter&) : vector<Attivita*>
+ salva(nomeFile : const QString&) : bool
+ carica(nomeFile : const QString&) : bool
```

---

## Libretto
*(namespace modello)*

**Attributi:**
```
- cfu_totali : unsigned int
- attivita : const vector<Attivita*>&
```

**Metodi:**
```
+ Libretto(cfu_totali : unsigned int, attivita : const vector<Attivita*>&)
+ getCfuCompletati() : unsigned int
+ getCfuMancanti() : unsigned int
+ getMediaPesata() : double
+ getVotoFinaleAtteso() : double
+ getEsamiSuperati() : vector<const Esame*>
+ getEsamiNonSuperati() : vector<const Esame*>
+ getEsamiFuturi() : vector<const Esame*>
```

---

## JsonSaverVisitor
*(namespace modello — realizza ConstActivityVisitorInterface)*

**Attributi:**
```
- daSalvare : QJsonObject
```

**Metodi:**
```
- preparaBase(a : const Attivita*) : void
+ JsonSaverVisitor()
+ visit(e : const Esame*) : void
+ visit(s : const Scadenza*) : void
+ visit(i : const Appuntamento*) : void
+ visit(s : const Sport*) : void
+ getJsonObject() : QJsonObject
```

---
---

# Filtri — namespace modello::filtro

---

## *AbstractFilter* — classe astratta
*(titolo in corsivo)*

**Metodi:**
```
+ ~AbstractFilter()
+ filtra(a : const Attivita*) : bool    {abstract}
```

---

## FiltroCongiuntivo
*(estende AbstractFilter)*

**Attributi:**
```
- filtri : vector<AbstractFilter*>
```

**Metodi:**
```
+ FiltroCongiuntivo()
+ ~FiltroCongiuntivo()
+ addFiltro(f : AbstractFilter*) : void
+ filtra(a : const Attivita*) : bool
```

---

## FiltroAnno
*(estende AbstractFilter)*

**Attributi:**
```
- annoTarget : int
```

**Metodi:**
```
+ FiltroAnno(annoTarget : int)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroMeseAnno
*(estende AbstractFilter)*

**Attributi:**
```
- target : MeseTarget
- annoTarget : int
```

**Metodi:**
```
+ FiltroMeseAnno(target : MeseTarget, annoTarget : int)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroData
*(estende AbstractFilter)*

**Attributi:**
```
- target : QDate
```

**Metodi:**
```
+ FiltroData(target : const QDate&)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroNome
*(estende AbstractFilter)*

**Attributi:**
```
- nomeTarget : QString
```

**Metodi:**
```
+ FiltroNome(nomeTarget : const QString&)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroPriorita
*(estende AbstractFilter)*

**Attributi:**
```
- prioritaTarget : Priority
```

**Metodi:**
```
+ FiltroPriorita(prioritaTarget : Priority)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroTag
*(estende AbstractFilter)*

**Attributi:**
```
- tagTarget : QString
```

**Metodi:**
```
+ FiltroTag(tagTarget : const QString&)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroCompletate
*(estende AbstractFilter)*

**Attributi:**
```
- target : bool
```

**Metodi:**
```
+ FiltroCompletate(target : bool)
+ filtra(a : const Attivita*) : bool
```

---

## FiltroTipo
*(estende AbstractFilter)*

**Attributi:**
```
- tipo_cercato : ricercaTipo
```

**Metodi:**
```
+ FiltroTipo(tipo_cercato : ricercaTipo)
+ filtra(a : const Attivita*) : bool
```

---

## `«inner»` checkVisitor
*(inner class di FiltroTipo — realizza ConstActivityVisitorInterface)*

**Attributi:**
```
- trovato : bool
- tipoTarget : ricercaTipo
```

**Metodi:**
```
+ checkVisitor(tipoTarget : ricercaTipo)
+ visit(e : const Esame*) : void
+ visit(s : const Scadenza*) : void
+ visit(a : const Appuntamento*) : void
+ visit(s : const Sport*) : void
```

---

## Riepilogo connettori (relazioni)

| Da | Tipo freccia draw.io | A | Molteplicità / Note |
|---|---|---|---|
| Appuntamento | --|> generalizzazione | Attivita | |
| Scadenza | --|> generalizzazione | Attivita | |
| Esame | --|> generalizzazione | Attivita | |
| Sport | --|> generalizzazione | Attivita | |
| JsonSaverVisitor | ..|> realizzazione | ConstActivityVisitorInterface | |
| checkVisitor | ..|> realizzazione | ConstActivityVisitorInterface | |
| Scadenza | --* composizione | SottoTask | todoList 0..* |
| FiltroTipo | --* composizione | checkVisitor | inner class |
| FiltroCongiuntivo | --o aggregazione | AbstractFilter | filtri 0..* |
| Gestore | --o aggregazione | Attivita | listaAttivita 0..* |
| Libretto | -- associazione | Attivita | ref const |
| Libretto | ..> dipendenza | Esame | usa |
| Gestore | ..> dipendenza | AbstractFilter | usa |
| FiltroCongiuntivo | --|> generalizzazione | AbstractFilter | |
| FiltroAnno | --|> generalizzazione | AbstractFilter | |
| FiltroMeseAnno | --|> generalizzazione | AbstractFilter | |
| FiltroData | --|> generalizzazione | AbstractFilter | |
| FiltroNome | --|> generalizzazione | AbstractFilter | |
| FiltroPriorita | --|> generalizzazione | AbstractFilter | |
| FiltroTag | --|> generalizzazione | AbstractFilter | |
| FiltroCompletate | --|> generalizzazione | AbstractFilter | |
| FiltroTipo | --|> generalizzazione | AbstractFilter | |
