# Tidsplan
Projektet pågår i fyra veckor. Kursunderlaget föreslår:
vecka 1: kravanalys/research/planering,
vecka 2: implementation/integration,
vecka 3: kommunikation/testning,
vecka 4: färdigställande/överlämning.
Vår detaljerade plan
        Vecka
        Datum
        Fokus
        Resultat

Vecka 1
31 aug–4 sep
Krav, research, sensorval, arkitektur
Projektplan, backlog, sensorbeslut, PoC

Vecka 2
7–11 sep
Embedded + sensorer
Alla fyra mätningar fungerar

Vecka 3
14–18 sep
Kommunikation + test
Data skickas externt, integrationstest

Vecka 4
21–25 sep
Stabilisering + dokumentation + demo
Slutprodukt, dokumentation, presentation


### Vecka 1 – Krav, research och PoC
Mål
Fastställa vad som ska byggas och hur det rimligen ska byggas.
Tasks
analysera kundbrevet,
skapa kravspecifikation,
prioritera krav,
skapa backlog,
skapa GitHub repository,
undersöka sensoralternativ,
jämföra sensorer,
välja preliminära komponenter,
undersöka MQTT vs HTTP,
definiera preliminär arkitektur,
bygga första sensor-PoC.
Veckans Definition of Done
Vid slutet av vecka 1 ska teamet ha:
projektplan,
kravlista,
backlog,
arkitekturförslag,
sensorjämförelse,
preliminära sensorval,
kommunikationsbeslut/förslag,
fungerande första tekniska PoC.

### Vecka 2 – Embedded implementation
Mål
Få hela sensorinsamlingen att fungera.
Tasks
integrera intern temperatur,
integrera extern temperatur,
integrera vattentemperatur,
integrera luftfuktighet,
implementera periodisk sampling,
implementera data structure,
implementera validation,
implementera error handling,
genomföra sensorintegrationstest.
Veckans mål
4 Sensors
    ↓
Embedded MCU
    ↓
Validated measurement
    ↓
Structured data
Vid slutet av vecka 2 ska de fyra obligatoriska mätpunkterna kunna demonstreras.

### Vecka 3 – Kommunikation och testning
Mål
Få data från embedded-systemet till ett externt system.
Tasks
konfigurera Wi-Fi/kommunikation,
implementera MQTT eller HTTP,
skicka strukturerade mätvärden,
hantera kommunikationsfel,
testa reconnect,
testa invalid data,
testa sensorfel,
genomföra integrationstest,
genomföra längre stabilitetstest.
Resultat
Sensors
   ↓
Embedded
   ↓
Validation
   ↓
Communication
   ↓
External System

### Vecka 4 – Stabilisering och överlämning
Mål
Förvandla prototypen från fungerande utvecklingsversion till en stabil demonstrationsversion.
Tasks
fixa identifierade buggar,
köra regressionstester,
genomföra sluttest,
färdigställa README,
färdigställa teknisk dokumentation,
färdigställa arkitekturdiagram,
dokumentera sensorval,
dokumentera kommunikationslösning,
dokumentera begränsningar,
skapa demo-scenario,
förbereda presentation,
förbereda överlämning,
skriva individuell reflektion.
Projektets slutleverans omfattar projektplan/krav, Git-repository, fungerande prototyp, teknisk dokumentation, testdokumentation, demonstration/överlämning och individuell reflektionsrapport.
