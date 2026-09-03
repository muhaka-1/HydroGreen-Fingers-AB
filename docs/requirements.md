Kundbrevet är inte en färdig teknisk kravspecifikation. Projektets uppgift är därför att översätta kundens behov till konkreta tekniska krav. Detta är uttryckligen en del av uppdraget.
6.1 Funktionella krav

FR-01 – Intern temperatur
Systemet ska kunna mäta lufttemperaturen inne i odlingsutrymmet.

FR-02 – Extern temperatur
Systemet ska kunna mäta lufttemperaturen utanför odlingsutrymmet.

FR-03 – Vattentemperatur
Systemet ska kunna mäta temperaturen i vatten/näringslösning.

FR-04 – Luftfuktighet
Systemet ska kunna mäta relativ luftfuktighet inne i odlingsutrymmet.

FR-05 – Periodisk mätning
Systemet ska genomföra mätningar återkommande med ett definierat mätintervall.

FR-06 – Databehandling
Embedded-systemet ska läsa, bearbeta och strukturera sensordata.

FR-07 – Kommunikation
Embedded-systemet ska kunna överföra mätdata till ett externt system.

FR-08 – Felhantering
Systemet ska kunna identifiera och hantera exempelvis:

sensorfel,
saknat mätvärde,
timeout,
kommunikationsfel,
orimliga mätvärden.


7. Icke-funktionella krav
Krav
Beskrivning
NFR-01 Systemet ska vara stabilt under längre mätning
NFR-02 Sensorval ska vara tekniskt motiverat
NFR-03 DHT11/DHT22 får inte användas
NFR-04 Mätdata ska vara tydligt strukturerad
NFR-05 Systemet ska vara möjligt att vidareutveckla
NFR-06 Källkod ska versionshanteras med Git
NFR-07 Lösningen ska vara dokumenterad
NFR-08 Viktiga tekniska beslut ska kunna förklaras
NFR-09 Prototypen ska kunna demonstreras
NFR-10 Lösningen ska ha rimlig komplexitet för projektets tidsram

