#ADSR #DAC

------------------
# ADSR Signaal
- **A** - Attack ehk Rünne
- **D** - Decay ehk Langus
- **S** - Sustain ehk Hoid
- **R** - Release ehk Vabastus

*Miks?*
- Kontrollida signaali volüümi vastavalt parameetritele

*Milline?*
- Täis analoog
	- + Ei pea programmeerima
	- - Temperatuurist sõltuv, ruumi nõudev
- Täis digitaalne
	- + Täpne ADSR väljund
	- - Peab programmeerima, Väike resolutsioon teeb sammuliseks

*Kuidas?*
- [[MCU]]s genereerib signaali
- Juhised saadab [[DAC]]i

*Kiirus:*
- Võiks reageerida sama kiiresti või kiiremini kui [[Interface#Surveandur]]

----------
### Signaali suund: [[VCA]]