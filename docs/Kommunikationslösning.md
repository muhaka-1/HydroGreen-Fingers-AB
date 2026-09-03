Kommunikationslösningen ska väljas under vecka 1 efter en jämförelse av möjliga alternativ.
Projektunderlaget nämner bland annat:
MQTT,
HTTP/REST,
Bluetooth/BLE,
seriell kommunikation till gateway.
Preliminärt alternativ: MQTT
En möjlig arkitektur är:
Sensorer → Embedded Controller → MQTT → Broker → Externt system
MQTT är särskilt intressant eftersom MicroHydros i framtiden kan bestå av flera uppkopplade odlingsenheter.
Men slutligt val ska dokumenteras och motiveras utifrån projektets faktiska behov.
