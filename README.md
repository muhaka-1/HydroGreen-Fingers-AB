# MicroHydros - Prototyp (HydroGreen Fingers AB)

Välkommen till repositoryt för **MicroHydros** – en kompakt, IoT-baserad hydroponisk odlingsenhet utvecklad av utvecklingsteamet på uppdrag av **HydroGreen Fingers AB**.

---

## 🎯 Projektets syfte
HydroGreen Fingers vision är att göra lokal livsmedelsproduktion tillgänglig i små utrymmen (såsom bostäder, restauranger och kontor) genom sammankopplade små odlingar. 

Detta projekt utgör den första tekniska prototypen för **MicroHydros**. Syftet är att skapa en stabil, välmotiverad och fungerande grundlösning som kan övervaka klimatet i en kompakt odlingsmiljö samt kommunicera insamlad data externt.

---

## 📊 Obligatoriska mätpunkter
Prototypen är designad för att återkommande samla in följande miljödata:
1. **Lufttemperatur inne** i odlingsutrymmet.
2. **Lufttemperatur utanför** odlingsutrymmet.
3. **Temperatur i vatten/näringslösning**.
4. **Relativ luftfuktighet inne** i odlingsutrymmet.

*(Observera: Sensorer ur DHT11- och DHT22-familjerna har uteslutits på grund av tidigare erfarenheter av dålig tillförlitlighet och ersatts med mer robusta komponenter).*

---

## 🛠️ Teknisk stack (Preliminär)
* **Mikrokontroller:** ESP32 (med integrerat Wi-Fi)
* **Sensorer:** 
  * Inne (Temperatur/Luftfuktighet): *Exempelvis BME280 / SHT31*
  * Vatten (Temperatur): *Vattentät DS18B20 (1-Wire)*
  * Ute (Temperatur): *DS18B20 / BME280*
* **Programmeringsspråk:** C++ (Arduino Framework / ESP-IDF)
* **Kommunikation:** MQTT över Wi-Fi mot en extern broker/mottagare
* **Versionshantering:** Git & GitHub

---

## 📁 Repositoryts struktur
* `/src` – Källkod för mikrokontrollern
* `/docs` – Projektplan, kravspecifikation, arkitekturdiagram och testdokumentation
* `/hardware` – Kopplingsscheman och komponentlistor

---

## 🚀 Komma igång / Bygga systemet

### Förutsättningar
* **Hårdvara:** ESP32, valda sensorer, kopplingstavla och kablage.
* **Mjukvara:** PlatformIO eller Arduino IDE installerat på datorn.

### Steg-för-steg för att köra prototypen
1. Klona repositoryt:
   ```bash
   git clone repo
