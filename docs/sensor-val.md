# 🔬 Sensorval – MicroHydros

## 1. Syfte

Sensorvalet är en viktig del av MicroHydros eftersom systemets kvalitet beror på att sensorerna kan ge tillförlitliga mätvärden under lång tid.

MicroHydros ska kunna övervaka odlingsmiljön och samla in mätdata som kan användas av systemets mikrokontroller, backend och IoT-plattform.

Vid sensorvalet har följande kriterier använts:

* Noggrannhet
* Upplösning
* Mätområde
* Responstid
* Gränssnitt
* Stabilitet
* Miljötålighet
* Strömförbrukning
* Kostnad
* Tillgänglighet
* Enkel integration med mikrokontroller

---

# 2. Krav på sensorerna

MicroHydros behöver sensorer som fungerar i en fuktig odlingsmiljö och som kan anslutas till en modern mikrokontroller, exempelvis ESP32.

De viktigaste kraven är:

| Krav             | Målsättning                                 |
| ---------------- | ------------------------------------------- |
| Temperatur       | Tillräcklig noggrannhet för odlingsmiljön   |
| Luftfuktighet    | Minst 0–100 % RH mätområde                  |
| Gränssnitt       | Digitalt gränssnitt, helst I²C eller 1-Wire |
| Stabilitet       | Lämplig för kontinuerlig mätning            |
| Strömförbrukning | Låg, särskilt för batteridrivna noder       |
| Miljö            | Ska fungera i fuktig odlingsmiljö           |
| Integration      | Ska vara enkel att använda med ESP32        |
| Kostnad          | Rimlig för prototyp och framtida expansion  |

---

# 3. Alternativa sensorer

## 3.1 SHT31

SHT31 från Sensirion är en digital temperatur- och luftfuktighetssensor.

Sensorn har:

* Temperatur noggrannhet: typiskt ±0,2 °C
* Luftfuktighetsnoggrannhet: typiskt ±2 % RH
* Luftfuktighetsområde: 0–100 % RH
* Temperaturmätområde: -40 till +125 °C
* I²C-gränssnitt
* Responstid för luftfuktighet: cirka 8 s
* Temperaturresponstid: >2 s
* Låg strömförbrukning
* Fabrikskalibrering

Sensirion anger även att SHT31 finns i versioner med skyddande kapsling, vilket är intressant för en fuktig odlingsmiljö.

### Fördelar

* Hög noggrannhet
* Mätningsområde som passar odlingsmiljöer
* Digital I²C-kommunikation
* Låg energiförbrukning
* Enkel att integrera med ESP32
* Finns med skyddande variant
* Temperatur och luftfuktighet i samma komponent

### Nackdelar

* Mäter inte jord-/substratfuktighet
* Luftfuktighetsmätningen är relativt långsam jämfört med vissa andra sensorer
* Sensorn bör skyddas mot direkt vatten och kondens

---

# 3.2 BME280

BME280 från Bosch Sensortec mäter:

* Temperatur
* Relativ luftfuktighet
* Lufttryck

Sensorn har ett temperaturmätområde på -40 till +85 °C och ett luftfuktighetsområde på 0–100 % RH. Den stöder både I²C och SPI. Luftfuktighetens responstid anges till cirka 1 sekund och typisk luftfuktighetsnoggrannhet är ±3 % RH.

### Fördelar

* Tre mätvärden i samma sensor
* I²C och SPI
* Mycket låg strömförbrukning
* Snabb respons för luftfuktighet
* Liten fysisk storlek
* Väletablerad inom IoT-projekt

### Nackdelar

* Luftfuktighetsnoggrannheten är sämre än SHT31
* Lufttrycksmätningen behövs inte nödvändigtvis för MicroHydros
* Kräver skydd mot direkt vatten/kondens
* Ytterligare funktionalitet innebär inte automatiskt högre nytta för projektet

---

# 3.3 SHTC3

SHTC3 från Sensirion är en mycket liten digital temperatur- och luftfuktighetssensor som är särskilt optimerad för låg energiförbrukning.

Tekniska data:

* Luftfuktighetsnoggrannhet: typiskt ±2 % RH
* Temperatur noggrannhet: typiskt ±0,2 °C
* Luftfuktighetsområde: 0–100 % RH
* Temperaturmätområde: -40 till +125 °C
* I²C
* Luftfuktighetsresponstid: cirka 8 s
* Temperaturresponstid: cirka 5 s
* Mycket låg energiförbrukning
* Matningsspänning: 1,62–3,6 V

Sensirion anger ett energibehov under 1 µJ per mätning och en typisk medelström på cirka 0,5 µA i den specificerade mätkonfigurationen.

### Fördelar

* Mycket låg energiförbrukning
* Bra noggrannhet
* I²C
* Mycket liten
* Bra för batteridrivna IoT-noder

### Nackdelar

* Långsammare responstid än BME280
* Mindre fysisk storlek kan göra prototypmontering svårare
* Ingen lufttrycksmätning
* Kräver skydd mot kondens och direkt vatten

---

# 3.4 DS18B20

DS18B20 är en digital temperatursensor som använder 1-Wire.

Tillverkarens specifikationer anger:

* Temperaturmätområde: -55 till +125 °C
* Noggrannhet: ±0,5 °C mellan -10 och +85 °C
* Upplösning: 9–12 bitar
* 1-Wire-kommunikation
* Unikt 64-bitars serienummer för varje sensor
* Kan användas med flera sensorer på samma buss

DS18B20 är därför särskilt intressant om MicroHydros behöver mäta temperatur på flera olika platser.

### Fördelar

* Enkel digital kommunikation
* Flera sensorer kan dela samma 1-Wire-buss
* Unikt ID för varje sensor
* Bra för distribuerade temperaturmätningar
* Finns i kapslade/vattentåliga varianter
* Billig och lätt att använda

### Nackdelar

* Mäter endast temperatur
* Sämre temperaturprecision än SHT31/SHTC3
* Mätningen kan vara långsammare vid högsta upplösning
* Kräver 1-Wire istället för I²C

---

# 4. Teknisk jämförelse

| Kriterium                    | SHT31         | BME280        | SHTC3         | DS18B20              |
| ---------------------------- | ------------- | ------------- | ------------- | -------------------- |
| Temperatur                   | Ja            | Ja            | Ja            | Ja                   |
| Luftfuktighet                | Ja            | Ja            | Ja            | Nej                  |
| Lufttryck                    | Nej           | Ja            | Nej           | Nej                  |
| Temperatur noggrannhet       | ±0,2 °C typ.  | God           | ±0,2 °C typ.  | ±0,5 °C              |
| RH noggrannhet               | ±2 % RH typ.  | ±3 % RH       | ±2 % RH typ.  | –                    |
| RH-område                    | 0–100 %       | 0–100 %       | 0–100 %       | –                    |
| Temperaturmätområde          | -40–125 °C    | -40–85 °C     | -40–125 °C    | -55–125 °C           |
| Gränssnitt                   | I²C           | I²C / SPI     | I²C           | 1-Wire               |
| RH-responstid                | ~8 s          | ~1 s          | ~8 s          | –                    |
| Energiförbrukning            | Låg           | Mycket låg    | Extremt låg   | Låg                  |
| ESP32-integration            | Enkel         | Enkel         | Enkel         | Enkel                |
| Flera sensorer på samma buss | Ja*           | Ja*           | Ja*           | Ja                   |
| Lämplig för odlingsmiljö     | Ja, med skydd | Ja, med skydd | Ja, med skydd | Ja, särskilt kapslad |
| Extra mätning                | –             | Lufttryck     | –             | –                    |

* I²C-enheter kan dela buss men måste hantera adresser; vid flera identiska sensorer kan en I²C-multiplexer behövas beroende på sensor och modul.

---

# 5. Bedömning utifrån projektets kriterier

## Noggrannhet

SHT31 och SHTC3 har mycket bra noggrannhet för temperatur och luftfuktighet.

SHT31 har typiskt ±0,2 °C temperaturprecision och ±2 % RH. SHTC3 har motsvarande typiska värden på ±0,2 °C och ±2 % RH.

BME280 är också tillräckligt noggrann för en odlingsapplikation men har typiskt ±3 % RH.

**Bedömning: SHT31/SHTC3 bäst.**

---

## Upplösning

SHTC3 anger en ADC-upplösning på 0,01 % RH och 0,01 °C.

DS18B20 har konfigurerbar upplösning från 9 till 12 bitar.

För MicroHydros är hög upplösning positivt eftersom små förändringar i odlingsmiljön kan upptäckas och loggas.

**Bedömning: SHT31/SHTC3 mycket bra. DS18B20 tillräcklig för temperatur.**

---

## Mätområde

Alla tre kombinerade temperatur-/luftfuktighetssensorer täcker det område som krävs för normal inomhusodling.

SHT31 och SHTC3 går från -40 till +125 °C och 0–100 % RH. BME280 går från -40 till +85 °C och 0–100 % RH.

**Bedömning: Alla är lämpliga.**

---

## Responstid

BME280 har snabbast angiven luftfuktighetsrespons, cirka 1 sekund.

SHT31 och SHTC3 har cirka 8 sekunders RH-responstid i de angivna testförhållandena.

För MicroHydros behöver sensorn normalt inte reagera på förändringar inom millisekunder. Därför är 8 sekunder acceptabelt för miljöövervakning.

**Bedömning: BME280 bäst på responstid, men SHT31 är tillräckligt snabb.**

---

# 6. Gränssnitt

SHT31, BME280 och SHTC3 använder I²C, medan BME280 dessutom stöder SPI. DS18B20 använder 1-Wire.

För MicroHydros är I²C särskilt lämpligt eftersom flera digitala sensorer kan anslutas till samma buss.

ESP32 har inbyggt stöd för I²C och passar därför bra för denna arkitektur.

**Bedömning: I²C-sensorerna är förstahandsvalet.**

---

# 7. Stabilitet och miljö

Sensorerna är avsedda för digital miljömätning och har fabrikskalibrering.

SHTC3 har exempelvis specificerad långtiddrift på mindre än 0,25 % RH per år och mindre än 0,02 °C per år typiskt.

Det är dock viktigt att komma ihåg att en sensor för luftfuktighet inte automatiskt är vattentät.

MicroHydros bör därför:

* undvika direkt vattenkontakt med sensorn,
* undvika kondens på sensorelementet,
* placera sensorn där luft kan cirkulera,
* använda lämpligt skydd/filter vid behov,
* inte placera en vanlig PCB-modul direkt i vatten.

**Bedömning: SHT31 är lämplig med korrekt mekaniskt skydd.**

---

# 8. Strömförbrukning

Alla kandidater är relativt energieffektiva.

BME280 anger exempelvis cirka 1,8 µA vid 1 Hz för temperatur och luftfuktighet och cirka 0,1 µA i sleep mode.

SHTC3 är särskilt optimerad för batteridrivna applikationer och har mycket låg energiförbrukning.

För en nätansluten prototyp är skillnaden mindre kritisk, men för framtida batteridrivna sensornoder blir den viktigare.

**Bedömning: SHTC3 bäst, BME280/SHT31 också mycket bra.**

---

# 9. Kostnad och tillgänglighet

För en prototyp bör komponenten vara vanlig och enkel att köpa från elektronikdistributörer.

SHT31, BME280 och DS18B20 är etablerade sensorer med många färdiga breakout boards och bibliotek för mikrokontrollers.

DS18B20 är särskilt attraktiv för prototyper eftersom den finns i många olika kapslingar och är enkel att använda med ESP32.

**Bedömning: DS18B20 och BME280 är mycket bra ur prototypperspektiv. SHT31 är dock det bättre valet när mätprecision prioriteras.**

---

# 10. Sensorbeslut

## 🥇 Primärt val: SHT31

**MicroHydros väljer SHT31 som primär sensor för temperatur och relativ luftfuktighet.**

### Motivering

SHT31 ger den bästa kombinationen av:

* hög noggrannhet,
* bra temperaturprecision,
* ±2 % RH typisk luftfuktighetsnoggrannhet,
* 0–100 % RH mätområde,
* -40 till +125 °C temperaturintervall,
* I²C-kommunikation,
* låg energiförbrukning,
* enkel ESP32-integration,
* fabrikskalibrering,
* tillgängliga skyddade varianter.

Sensirion specificerar SHT31 till typiskt ±0,2 °C för temperatur och ±2 % RH för relativ luftfuktighet.

Det gör sensorn väl lämpad för MicroHydros, där stabil och tillförlitlig miljöövervakning är viktigare än att mäta mycket snabbt.

---

# 11. Sekundärt val: DS18B20

**DS18B20 används som kompletterande temperatursensor när temperatur behöver mätas på flera fysiska platser.**

Exempel:

```text
ESP32
 │
 ├── I²C ── SHT31
 │            ├── Temperatur
 │            └── Luftfuktighet
 │
 └── 1-Wire ── DS18B20
                ├── Temperatur punkt 1
                ├── Temperatur punkt 2
                └── Temperatur punkt 3
```

Det unika 64-bitars ID:t hos varje DS18B20 gör det möjligt att identifiera flera temperatursensorer på samma 1-Wire-buss.

Detta är användbart om MicroHydros senare behöver mäta exempelvis:

* vattentemperatur,
* temperatur nära odlingsbehållaren,
* temperatur vid olika delar av systemet.

---

# 12. Alternativ: BME280

BME280 är ett bra alternativ om MicroHydros senare behöver mäta **lufttryck**.

Den största fördelen är att tre mätvärden finns i samma sensor:

```text
BME280
 ├── Temperatur
 ├── Luftfuktighet
 └── Lufttryck
```

BME280 stöder både I²C och SPI och har låg energiförbrukning.

Eftersom lufttryck inte är ett primärt krav för MicroHydros väljs den dock inte som huvudsensor.

---

# 13. Alternativ: SHTC3

SHTC3 är ett mycket bra alternativ om framtida MicroHydros-versioner ska vara batteridrivna.

Den har:

* ±2 % RH typisk noggrannhet,
* ±0,2 °C typisk temperaturprecision,
* I²C,
* mycket låg energiförbrukning,
* 0–100 % RH,
* -40 till +125 °C.

Den väljs inte som primär sensor eftersom SHT31 ger en mer lämplig balans mellan prestanda, prototypvänlighet och tillgänglighet för projektets nuvarande behov.

---

# 14. Viktig begränsning – luftfuktighet är inte jordfuktighet

En viktig teknisk begränsning är att SHT31, BME280 och SHTC3 mäter **relativ luftfuktighet**.

De mäter alltså inte mängden vatten i odlingssubstratet.

Om MicroHydros ska övervaka vattenhalten i jord eller annat odlingsmedium behövs en separat sensor.

För detta bör en **kapacitiv fuktsensor** användas istället för en billig resistiv sensor.

### Rekommenderad princip

```text
              MicroHydros
                   │
        ┌──────────┴──────────┐
        │                     │
      SHT31              Kapacitiv
        │              fuktsensor
        │                     │
   Lufttemperatur       Substratfuktighet
   Luftfuktighet
```

Den kapacitiva sensorn bör kalibreras mot det specifika odlingsmediet eftersom råvärdet inte automatiskt motsvarar en universell procentandel vatten.

---

# 15. Slutligt sensorpaket

För MicroHydros rekommenderas följande sensorarkitektur:

| Funktion                | Sensor                   | Beslut          |
| ----------------------- | ------------------------ | --------------- |
| Lufttemperatur          | SHT31                    | ✅ Primär        |
| Luftfuktighet           | SHT31                    | ✅ Primär        |
| Extra temperaturpunkter | DS18B20                  | ✅ Sekundär      |
| Vattentemperatur        | DS18B20, kapslad variant | ✅ Rekommenderad |
| Substratfuktighet       | Kapacitiv fuktsensor     | ✅ Vid behov     |
| Lufttryck               | BME280                   | ⚪ Valfri        |
| Batteridriven miljönod  | SHTC3                    | ⚪ Alternativ    |

---

# 16. Slutligt beslut

### 🥇 SHT31 – huvudval

SHT31 väljs som MicroHydros huvudsensor för temperatur och relativ luftfuktighet eftersom den erbjuder en bra kombination av noggrannhet, stabilitet, låg energiförbrukning och enkel I²C-integration.

### 🥈 DS18B20 – kompletterande sensor

DS18B20 används där flera separata temperaturmätpunkter behövs, särskilt för vatten- eller andra temperaturmätningar. Dess 1-Wire-gränssnitt och unika ID gör den lämplig för flera sensorer på samma buss.

### 🥉 Kapacitiv fuktsensor – vid behov

Om projektet behöver mäta vattenhalten i odlingsmedium ska en separat kapacitiv fuktsensor användas. SHT31 ska inte användas för detta eftersom den mäter luftfuktighet.

### Alternativ

BME280 behålls som ett alternativ om lufttryck senare blir relevant. SHTC3 är ett alternativ för batteridrivna noder där extremt låg energiförbrukning prioriteras.

---

# 17. Identifierade begränsningar

Följande begränsningar har identifierats:

1. **SHT31 är inte vattentät.** Den måste skyddas mot direkt vatten och kondens.
2. **SHT31 mäter luftfuktighet, inte substratfuktighet.**
3. **Luftfuktighetens responstid är cirka 8 sekunder**, vilket är tillräckligt för miljöövervakning men inte för mycket snabba processer.
4. **Sensorplaceringen påverkar resultatet.** Värme från ESP32, regulatorer och andra komponenter kan påverka temperaturmätningen.
5. **Kondens kan påverka mätningen och sensorns livslängd.**
6. **Kapacitiva fuktsensorer behöver kalibreras** mot det odlingsmedium som används.
7. **I²C-adresser måste hanteras** om flera identiska I²C-sensorer används på samma buss.
8. **DS18B20 mäter endast temperatur** och ersätter därför inte en kombinerad temperatur-/luftfuktighetssensor.

---

# 18. Slutsats

Efter jämförelsen väljs **SHT31 som primär miljösensor för MicroHydros**.

SHT31 uppfyller projektets viktigaste krav på noggrannhet, mätområde, digital kommunikation, energiförbrukning och integration med en ESP32-baserad IoT-arkitektur.

**DS18B20** används som kompletterande temperaturgivare när flera mätpunkter eller vatten-/vätsketemperatur behöver övervakas.

Om MicroHydros behöver mäta vattenhalten i odlingsmediet kompletteras systemet med en **kapacitiv fuktsensor**.

Detta ger en flexibel sensorarkitektur:

```text
                    ┌──────────────────┐
                    │      ESP32       │
                    │   MicroHydros    │
                    └────────┬─────────┘
                             │
              ┌──────────────┼──────────────┐
              │              │              │
             I²C           1-Wire         Analog
              │              │              │
              ▼              ▼              ▼
          ┌────────┐    ┌──────────┐   ┌────────────┐
          │ SHT31  │    │ DS18B20  │   │ Kapacitiv  │
          │        │    │          │   │ fuktsensor │
          ├────────┤    ├──────────┤   └────────────┘
          │ Temp.  │    │ Vatten-  │
          │ RH     │    │ temp.    │
          └────────┘    │ Temp.    │
                        └──────────┘
```

**Sensorbeslut: SHT31 + DS18B20 + kapacitiv fuktsensor vid behov.**


### Källor

De tekniska värdena ovan bygger främst på tillverkarnas aktuella dokumentation för Bosch Sensortec BME280, Sensirion SHT31/SHTC3 och Analog Devices DS18B20.

SHT31 – Sensirion
BME280 – Bosch Sensortec
SHTC3 – Sensirion
DS18B20 – Analog Devices