# Agenda++ — Task Manager & Libretto Universitario

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg?logo=c%2B%2B)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Qt Framework](https://img.shields.io/badge/Qt-Framework-41CD52.svg?logo=qt)](https://www.qt.io/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

Applicazione desktop per la gestione di impegni quotidiani e la pianificazione della carriera accademica.  
Sviluppata in **C++** con interfaccia grafica in **Qt Widgets**, implementando i principali principi della programmazione orientata agli oggetti (OOP) e design pattern architetturali.

Progetto didattico realizzato per il corso di **Programmazione ad Oggetti** (Corso di Laurea in Informatica, Università degli Studi di Padova).

---

## 👥 Autore

* **Francesco Mazzurana** — [GitHub](https://github.com/MaZzU05)

---

## 🏛️ Architettura e Design Pattern

Il software adotta una rigida separazione dei livelli tra logica di business (`modello/`) e interfaccia utente (`gui/`):

### 1. Gerarchia Polimorfa delle Attività
Una classe base astratta `Attivita` da cui derivano le entità specializzate dell'agenda:
* `Appuntamento`: Impegni con data, fascia oraria e luogo.
* `Scadenza`: Compiti con data limite e stato di completamento.
* `Esame`: Valutazioni universitarie collegate ai CFU e al calcolo delle medie del `Libretto` accademico.
* `Sport`: Sessioni di allenamento con tracciamento temporale e tipologia.

### 2. Visitor Pattern
Utilizzato per estendere le operazioni sulle attività polimorfe senza alterarne la gerarchia:
* **Rendering Grafico (`CardActivityVisitor`, `CardEditActivityVisitor`):** Costruisce dinamicamente le relative card visive e le maschere di modifica per ogni tipo di attività.
* **Persistenza Dati (`JsonSaverVisitor`):** Serializza le entità in formato JSON senza legare la logica di I/O alle classi di dominio.

### 3. Observer Pattern
Il `Gestore` centrale funge da soggetto osservato e notifica le viste registrate (`GestoreObserverInterface`) a ogni aggiunta, modifica, cancellazione o caricamento di dati.

### 4. Strategy / Composite nei Filtri
Motore di ricerca basato sull'interfaccia `AbstractFilter`, che include filtri per data, tag, priorità, nome, anno e filtri combinabili tramite `FiltroCongiuntivo`.

---

## 📂 Struttura del Repository

```text
AgendaPlusPlus/
├── docs/
│   └── Relazione.pdf          # Relazione tecnica di progetto
├── data/
│   └── test_agenda.json       # Dataset di esempio pronto all'uso
├── gui/
│   ├── Card/                  # Widget e visitor per le card delle attività
│   ├── assets/                # Icone grafiche e foglio di stile stile.qss
│   └── ...                    # Viste (Calendario, Elenco, Libretto, Edit)
├── modello/
│   ├── Filtri/                # Filtri di ricerca polimorfi e congiuntivi
│   └── ...                    # Entità (Attivita, Gestore, Libretto, Visitor)
├── Agenda++.pro               # File di configurazione QMake per Qt Creator
├── resources.qrc              # File di risorse compilato di Qt
└── README.md
```
## 🚀 Istruzioni per la Compilazione ed Esecuzione

### Prerequisiti
* Compilatore compatibile **C++17** (`clang++` o `g++`)
* **Qt 5** o **Qt 6** (moduli: `core`, `gui`, `widgets`)
* **Qt Creator** (raccomandato) oppure tool da terminale (`qmake`, `make`)

### Compilazione tramite Qt Creator (Consigliato)
1. Apri **Qt Creator**.
2. Clicca su **Open File or Project...** e seleziona il file `Agenda++.pro` nella cartella del repository.
3. Seleziona il Kit di compilazione installato (es. *Desktop Qt 6.x Clang 64bit*).
4. Premi `Cmd + R` (su macOS) o `Ctrl + R` (su Linux/Windows) per compilare ed eseguire l'applicazione.

### Compilazione da Terminale (macOS / Linux)
Posizionati nella root del progetto ed esegui:

```bash
# 1. Genera il Makefile dal file di progetto Qt
qmake Agenda++.pro

# 2. Compila i sorgenti
make

# 3. Avvia l'eseguibile
./Agenda++
```
## 📄 Note e Licenza
Distribuito sotto licenza MIT. Il codice sorgente e la documentazione tecnica sono messi a disposizione per scopi didattici e di studio.
