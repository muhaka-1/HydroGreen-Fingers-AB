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