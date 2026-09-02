# 🌱 MicroHydros

### IoT- och embeddedprototyp för HydroGreen Fingers AB

> **En grönare framtid, en liten odling i taget.**

MicroHydros är ett IoT- och embeddedprojekt utvecklat som en första teknisk prototyp åt **HydroGreen Fingers AB**. Projektets mål är att utveckla en kompakt och stabil lösning för kontinuerlig övervakning av klimatet i en mindre hydroponisk odlingsmiljö.

Prototypen fokuserar på att samla in miljödata, behandla mätvärden i ett embedded-system och kommunicera informationen till ett externt system.

Projektet genomförs inom utbildningen **IoT- och embeddedutvecklare** vid JENSEN yrkeshögskola.

---

## 📋 Projektöversikt

| Information       | Detalj                         |
| ----------------- | ------------------------------ |
| **Projekt**       | MicroHydros                    |
| **Kund**          | HydroGreen Fingers AB          |
| **Projektperiod** | 31 augusti – 25 september 2026 |
| **Omfattning**    | 20 YH-poäng                    |
| **Projektform**   | Teamprojekt                    |
| **Område**        | IoT / Embedded Systems         |
| **Status**        | 🚧 Under utveckling            |

---

## 🎯 Projektets mål

MicroHydros ska demonstrera en fungerande embedded- och IoT-prototyp som kan samla in relevanta miljödata från en liten hydroponisk odlingsmiljö.

Prototypen ska framför allt kunna:

* mäta temperatur inne i odlingsutrymmet,
* mäta temperatur utanför odlingsutrymmet,
* mäta temperaturen i vatten/näringslösning,
* mäta relativ luftfuktighet inne i odlingsutrymmet,
* genomföra mätningar återkommande över tid,
* behandla mätdata i embedded-systemet,
* upptäcka och hantera orimliga eller felaktiga mätvärden,
* kommunicera mätdata till ett externt system.

Projektet fokuserar på en **stabil och välmotiverad prototyp** snarare än ett stort antal halvfärdiga funktioner.

---

# 🌿 Bakgrund

HydroGreen Fingers AB utvecklar småskaliga hydroponiska odlingssystem med visionen att göra lokal livsmedelsproduktion möjlig även i miljöer med mycket begränsat utrymme.

MicroHydros är tänkt som en kompakt odlingsenhet för exempelvis:

* bostäder,
* restauranger,
* skolor,
* kontor,
* andra mindre inomhusmiljöer.

Eftersom enheten använder artificiell belysning och innehåller elektronik, pumpar och odlingsmiljö i ett begränsat utrymme kan temperatur och luftfuktighet förändras relativt snabbt.

Kontinuerlig miljöövervakning är därför en central del av den framtida produkten.

---

# 🏗️ Föreslagen systemarkitektur

Den övergripande arkitekturen bygger på följande flöde:

```text
┌───────────────────────┐
│   Hydroponisk miljö   │
│                       │
│  🌡 Intern temperatur │
│  🌡 Extern temperatur │
│  💧 Vattentemperatur  │
│  💦 Luftfuktighet     │
└───────────┬───────────┘
            │
            │ Sensorvärden
            ▼
┌───────────────────────────┐
│     Embedded-enhet        │
│                           │
│  Sensor drivers           │
│  Measurement scheduler    │
│  Data validation          │
│  Data processing          │
│  Communication            │
└────────────┬──────────────┘
             │
             │ IoT-kommunikation
             ▼
┌───────────────────────────┐
│     Externt system        │
│                           │
│ MQTT broker / API /       │
│ Gateway / Server          │
└────────────┬──────────────┘
             │
             ▼
┌───────────────────────────┐
│   Framtida molntjänst     │
│                           │
│ Historiska mätvärden      │
│ Analys                    │
│ Notifieringar             │
└───────────────────────────┘
```

Den slutliga kommunikationslösningen fastställs efter teknisk utvärdering.

---

# 📁 Repositorystruktur

En möjlig struktur:

```text
MicroHydros/
│
├── README.md
│
├── firmware/
│   ├── src/
│   ├── include/
│   ├── lib/
│   └── platformio.ini
│
├── docs/
│   ├── project-plan.md
│   ├── requirements.md
│   ├── architecture.md
│   ├── sensor-selection.md
│   ├── communication.md
│   ├── testing.md
│   ├── risks.md
│   └── decisions/
│
├── tests/
│   ├── unit/
│   └── integration/
│
├── diagrams/
│   └── architecture.png
│
└── .github/
    └── workflows/
        └── ci.yml
```

Den slutliga strukturen kan anpassas efter den hårdvara och kommunikationslösning som väljs.

---

# 📚 Teknisk dokumentation

| Dokument                   | Beskrivning                             |
| -------------------------- | --------------------------------------- |
| `docs/project-plan.md`     | Projektplan och tidsplan                |
| `docs/requirements.md`     | Funktionella och icke-funktionella krav |
| `docs/architecture.md`     | Systemarkitektur                        |
| `docs/sensor-selection.md` | Sensorresearch och sensorval            |
| `docs/communication.md`    | Kommunikationslösning                   |
| `docs/testing.md`          | Teststrategi och testresultat           |
| `docs/risks.md`            | Risker och begränsningar                |
| `docs/decisions/`          | Tekniska beslut och motiveringar        |

---

# 🔧 Teknikområden

Projektet fokuserar på:

* **Embedded Systems**
* **IoT**
* **Sensorintegration**
* **C/C++**
* **Mikrokontroller**
* **Datainsamling**
* **Data validation**
* **MQTT / HTTP**
* **Wi-Fi**
* **Git & GitHub**
* **Jira**
* **Confluence**
* **Agile / Scrum**
* **Testning**
* **Systemarkitektur**

---

# 🚫 Sensorbegränsning

Den tidigare prototypen använde sensorer ur familjerna **DHT11 och DHT22**.

På grund av tidigare problem med bland annat:

* mätkvalitet,
* stabilitet,
* tillförlitlighet,
* lämplighet för den aktuella miljön,

ska **DHT11 och DHT22 inte användas i MicroHydros-prototypen**.

Sensorerna ska istället väljas genom teknisk jämförelse och motiveras utifrån projektets behov.

Exempel på utvärderingskriterier:

* noggrannhet,
* upplösning,
* mätområde,
* responstid,
* kommunikationsgränssnitt,
* strömförbrukning,
* kostnad,
* tillgänglighet,
* miljötålighet,
* integrationsmöjligheter.

---

# 📐 Funktionella krav

## FR-01 – Intern lufttemperatur

Systemet ska kunna mäta lufttemperaturen inne i odlingsmiljön.

## FR-02 – Extern lufttemperatur

Systemet ska kunna mäta lufttemperaturen utanför odlingsmiljön.

## FR-03 – Vattentemperatur

Systemet ska kunna mäta temperaturen i vatten eller näringslösning.

## FR-04 – Relativ luftfuktighet

Systemet ska kunna mäta relativ luftfuktighet inne i odlingsmiljön.

## FR-05 – Återkommande mätningar

Systemet ska genomföra mätningar återkommande så att en serie mätvärden kan skapas över tid.

## FR-06 – Databehandling

Embedded-systemet ska behandla och strukturera insamlade mätvärden innan de kommuniceras vidare.

## FR-07 – Extern kommunikation

Systemet ska kunna kommunicera mätdata från embedded-enheten till ett externt system.

## FR-08 – Felhantering

Systemet ska ha någon form av hantering för felaktiga, saknade eller orimliga mätvärden.

---

# ⚙️ Icke-funktionella krav

## NFR-01 – Stabilitet

Prototypen ska kunna genomföra återkommande mätningar utan onödiga avbrott.

## NFR-02 – Underhållbarhet

Kod och systemstruktur ska vara organiserade så att lösningen kan vidareutvecklas.

## NFR-03 – Testbarhet

Viktiga funktioner ska kunna testas och verifieras separat.

## NFR-04 – Dokumentation

En annan utvecklare ska kunna förstå systemets huvudsakliga uppbyggnad och komma igång med projektet.

## NFR-05 – Utbyggbarhet

Arkitekturen bör möjliggöra framtida integration av fler sensorer och externa tjänster.

## NFR-06 – Spårbarhet

Projektets utveckling ska kunna följas genom Git, issues, pull requests och dokumentation.

---




# 🔬 Sensor Research

Sensorvalet är en viktig del av projektet.

Teamet ska undersöka flera möjliga komponenter och dokumentera varför de valda sensorerna är lämpliga för MicroHydros.

Sensorerna ska bland annat utvärderas utifrån:

| Kriterium        | Fråga                                          |
| ---------------- | ---------------------------------------------- |
| Noggrannhet      | Hur nära det verkliga värdet kan sensorn mäta? |
| Upplösning       | Hur små förändringar kan upptäckas?            |
| Mätområde        | Vilka temperatur-/fuktighetsintervall stöds?   |
| Responstid       | Hur snabbt reagerar sensorn på förändringar?   |
| Gränssnitt       | I²C, SPI, 1-Wire, analogt etc.?                |
| Stabilitet       | Hur stabil är mätningen över tid?              |
| Miljö            | Är sensorn lämplig för odlingsmiljön?          |
| Strömförbrukning | Hur mycket energi kräver sensorn?              |
| Kostnad          | Är komponenten rimlig för en prototyp?         |
| Tillgänglighet   | Är komponenten lätt att få tag på?             |

### Sensorbeslut

De slutliga sensorvalen dokumenteras i:

`docs/sensor-selection.md`

Beslutet ska innehålla:

1. alternativa sensorer,
2. teknisk jämförelse,
3. vald sensor,
4. motivering,
5. identifierade begränsningar.

---

# 📡 Kommunikationsstrategi

MicroHydros ska demonstrera att mätdata kan lämna embedded-systemet.

Följande alternativ kan utvärderas:

* MQTT,
* HTTP/REST,
* Bluetooth/BLE,
* seriell kommunikation via gateway,
* annan relevant IoT-kommunikation.

### Rekommenderad riktning

En kommunikationslösning bör väljas utifrån:

* enkel integration,
* tillförlitlighet,
* låg komplexitet,
* möjlighet till flera enheter,
* framtida molnintegration,
* möjlighet att hantera historiska mätvärden.

Kommunikationsvalet dokumenteras i:

`docs/communication.md`

---

# 📊 Datamodell

Mätdata bör struktureras på ett sätt som fungerar både för prototypen och framtida utveckling.

Exempel:

```json
{
  "device_id": "microhydros-001",
  "timestamp": "2026-09-02T08:30:00Z",
  "temperature_inside_c": 23.4,
  "temperature_outside_c": 20.1,
  "water_temperature_c": 21.8,
  "humidity_inside_percent": 58.2
}
```

Den exakta datastrukturen kan förändras under utvecklingen.

Viktiga egenskaper är:

* unik enhetsidentifierare,
* tidsstämpel,
* tydliga mätvärden,
* definierade enheter,
* möjlighet till historisk lagring,
* möjlighet till framtida utbyggnad.

---

# 🛡️ Felhantering och validering

Prototypen ska inte automatiskt lita på varje mätvärde.

Systemet bör kunna identifiera exempelvis:

```text
Sensor disconnected
        │
        ▼
Invalid reading
        │
        ▼
Validation
        │
   ┌────┴────┐
   │         │
Valid      Invalid
   │         │
   ▼         ▼
Send       Reject/
data       log error
```

Exempel på situationer som bör hanteras:

* sensor saknas,
* kommunikationsfel,
* timeout,
* orimligt temperaturvärde,
* orimlig luftfuktighet,
* saknat mätvärde,
* tillfälligt ogiltigt sensorvärde.

Exakta gränsvärden ska dokumenteras tillsammans med den tekniska implementationen.

---

# ⏱️ Mätintervall

Mätningar ska genomföras återkommande.

Exakt mätintervall bestäms efter teknisk utvärdering.

Vid beslutet bör teamet ta hänsyn till:

* hur snabbt klimatet förändras,
* sensorernas responstid,
* energiförbrukning,
* kommunikationskostnad,
* mängden historisk data,
* systemets belastning.

Målet är ett mätintervall som ger tillräckligt bra tidsupplösning utan onödig belastning.

---

# 🧪 Teststrategi

Projektets viktigaste funktioner ska testas systematiskt.

Varje test bör dokumentera:

| Fält               | Beskrivning              |
| ------------------ | ------------------------ |
| Test-ID            | Unik identifierare       |
| Funktion           | Vad testas?              |
| Förutsättning      | Vad krävs innan testet?  |
| Testmetod          | Hur genomförs testet?    |
| Förväntat resultat | Vad ska hända?           |
| Faktiskt resultat  | Vad hände?               |
| Status             | PASS / FAIL              |
| Kommentar          | Eventuella observationer |

### Exempel på tester

* Sensor kan initieras.
* Intern temperatur kan läsas.
* Extern temperatur kan läsas.
* Vattentemperatur kan läsas.
* Luftfuktighet kan läsas.
* Mätningar upprepas automatiskt.
* Ogiltiga mätvärden hanteras.
* Kommunikation fungerar.
* Mätdata har korrekt format.
* Embedded-systemet fortsätter fungera under längre körning.
* Mätvärden är rimliga jämfört med förväntade miljöförhållanden.

Testdokumentation finns i:

`docs/testing.md`

---

# 📦 Projektets leverabler

Vid projektets slut ska följande finnas:

* [ ] Projektplan och krav
* [ ] Komplett Git-repository
* [ ] Fungerande embeddedprototyp
* [ ] Sensorintegration
* [ ] Kommunikationslösning
* [ ] Felhantering
* [ ] Teknisk dokumentation
* [ ] Arkitekturdiagram
* [ ] Sensorjämförelse och sensorval
* [ ] Testdokumentation
* [ ] Demonstration
* [ ] Muntlig överlämning
* [ ] Individuell reflektionsrapport

---

# 📅 Projektplan

Projektet genomförs under fyra veckor.

| Vecka       | Fokus                                 | Huvudresultat                                  |
| ----------- | ------------------------------------- | ---------------------------------------------- |
| **Vecka 1** | Kravanalys, research och planering    | Projektplan, backlog, sensorresearch, PoC      |
| **Vecka 2** | Implementation och integration        | Sensorer och embedded-system fungerar          |
| **Vecka 3** | Kommunikation, test och stabilisering | Kommunikationslösning och testresultat         |
| **Vecka 4** | Färdigställande och överlämning       | Sluttest, dokumentation, demo och presentation |

---

# 📋 Agile / Scrum

Projektet drivs med ett enkelt agilt arbetssätt.

Teamet använder bland annat:

* Jira för backlog och arbetsuppgifter,
* Confluence för teknisk dokumentation,
* GitHub för versionshantering,
* Pull Requests för kodgranskning,
* Issues för problem och förbättringar.

Föreslagen arbetsstruktur:

```text
Backlog
   │
   ▼
Sprint Planning
   │
   ▼
To Do
   │
   ▼
In Progress
   │
   ▼
Code Review
   │
   ▼
Testing
   │
   ▼
Done
```

Backloggen ska hållas uppdaterad under projektperioden.

---

# 🌳 Git-strategi

Projektets programkod versionshanteras med Git.

Föreslaget arbetsflöde:

```text
main
 │
 ├── feature/sensor-integration
 │
 ├── feature/data-validation
 │
 ├── feature/mqtt-communication
 │
 └── feature/testing
```

Arbetsflöde:

```text
Issue
  ↓
Feature branch
  ↓
Implementation
  ↓
Commit
  ↓
Pull Request
  ↓
Code Review
  ↓
Merge
```

Commit-meddelanden bör vara tydliga och beskriva förändringen.

Exempel:

```text
feat: add water temperature sensor
feat: implement measurement validation
fix: handle sensor timeout
test: add invalid temperature test
docs: document sensor selection
```

---

# ⚠️ Risker

| Risk                        | Konsekvens                  | Åtgärd                                 |
| --------------------------- | --------------------------- | -------------------------------------- |
| Sensor ger instabila värden | Felaktig miljödata          | Jämföra och testa alternativa sensorer |
| Sensorfel                   | Mätdata saknas              | Implementera felhantering              |
| Kommunikationsproblem       | Data når inte extern tjänst | Testa kommunikation separat            |
| För stor projektomfattning  | Ofärdig prototyp            | Prioritera MVP                         |
| Dålig Git-struktur          | Svår spårbarhet             | Använd branches och PR                 |
| Otillräcklig testning       | Dold instabilitet           | Definiera testfall tidigt              |
| Tidsbrist                   | Vissa leverabler saknas     | Prioritera obligatoriska krav          |

---

# 🚧 Avgränsningar

Följande funktioner ingår **inte som obligatoriska delar** av första prototypen:

* färdig kommersiell molnplattform,
* mobilapplikation,
* avancerat webbgränssnitt,
* maskininlärning,
* automatisk bevattningsreglering,
* automatisk styrning av belysning,
* avancerade prediktionsalgoritmer,
* färdig fysisk produktdesign.

Sådana funktioner kan övervägas som framtida utveckling efter att projektets grundläggande krav är uppfyllda.

---

# 🚀 Framtida utveckling

MicroHydros är tänkt att kunna utvecklas till ett större uppkopplat odlingssystem.

Möjliga framtida funktioner:

```text
MicroHydros Device
        │
        ▼
   IoT Gateway
        │
        ▼
    Cloud API
        │
   ┌────┴────┐
   ▼         ▼
Database   Analytics
   │         │
   └────┬────┘
        ▼
 Dashboard / App
        │
        ▼
 Notifications
```

Framtida utveckling kan exempelvis omfatta:

* historisk datalagring,
* klimatgrafer,
* automatisk avvikelsedetektering,
* notifieringar,
* flera MicroHydros-enheter,
* central molntjänst,
* webbgränssnitt,
* mobilapplikation,
* automatisk styrning av belysning,
* automatisk bevattning,
* prediktiv analys.

---

# 🏆 Definition of Done

En funktion betraktas som klar när:

* [ ] Implementationen fungerar.
* [ ] Koden är versionshanterad.
* [ ] Relevant test är genomfört.
* [ ] Felhantering är implementerad där det behövs.
* [ ] Kodgranskning är genomförd när relevant.
* [ ] Dokumentation är uppdaterad.
* [ ] Jira-uppgiften är uppdaterad.
* [ ] Funktionen kan demonstreras.

---


# 👥 Team

Projektet utvecklas av ett team inom utbildningen **IoT- och embeddedutvecklare**.

Alla teammedlemmar deltar i:

* kravanalys,
* tekniska beslut,
* implementation,
* testning,
* dokumentation,
* problemlösning,
* demonstration och överlämning.

Individuella bidrag kan följas genom Git-historik, Jira, Pull Requests och projektets övriga planeringsunderlag.

---

# 📌 Projektstatus

**Status:** 🚧 Under utveckling

### MVP

* [ ] Kravanalys klar
* [ ] Sensorresearch klar
* [ ] Sensorval beslutat
* [ ] Embeddedplattform beslutad
* [ ] Intern temperatur implementerad
* [ ] Extern temperatur implementerad
* [ ] Vattentemperatur implementerad
* [ ] Luftfuktighet implementerad
* [ ] Återkommande mätningar implementerade
* [ ] Datahantering implementerad
* [ ] Felhantering implementerad
* [ ] Kommunikation implementerad
* [ ] Tester genomförda
* [ ] Dokumentation färdig
* [ ] Demonstration genomförd

---

# 🎓 Projektets koppling till kursens mål

MicroHydros är utformat för att demonstrera förmågan att:

* analysera ett kundbehov,
* formulera och prioritera tekniska krav,
* planera ett utvecklingsprojekt,
* arbeta agilt i team,
* utveckla och integrera hårdvara och mjukvara,
* använda Git och versionshantering,
* testa och utvärdera en teknisk lösning,
* dokumentera tekniska beslut,
* genomföra en professionell överlämning,
* reflektera över projektets arbetssätt.

---

# 📄 Licens

Detta repository är ett utbildningsprojekt inom IoT- och embeddedutveckling.

Projektet är utvecklat som en teknisk prototyp inom ramen för **MicroHydros Development Initiative**.

---

## 🌱 MicroHydros

> **En liten odling förändrar inte världen.
> Tusentals sammankopplade små odlingar kanske gör det.**

**Projektperiod:** 31 augusti – 25 september 2026
**HydroGreen Fingers AB × IoT- och embeddedutveckling**
