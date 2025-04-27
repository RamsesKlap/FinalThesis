#Sagedus #Volüüm #LFO
- [ ] Leia sobivad potentsiomeetrid
- [ ] 🔼 Otsustada mitu parameetrit tuleb
- [ ] Leida sobivad vedrud
--------------------
# Volüümi modulatsioon
... on selleks, et keset mängimist väljundsignaali amplituudi mõjutada.

*Miks?*
- Võimalus mängides helidünaamikat mõjutada
- Paika panna maksimaalse volüümi

*Nõuded?*
- Peab võimaldama lineaarsed volüümi muutust 0 - 100%
- Volüüm jääb sinna paika kuhu jätan

*Kuidas?*
- Potentsiomeeter
- OP-võimendi

------------
# Sageduse modulatsioon
... on selleks, et keset mängimist väljundsignaali sagedust mõjutada.

*Miks?*
- Võimalus mängides vahepealseid noote kätte saada - nö *bend-imine*
- Saaks tekitada huvitavaid efekte

*Nõuded?*
- Peab sagedust tõstma kuni **1 sammu** võrra
- Peab automaatselt 0-i minema

*Nice to have:*
- Tarkvaraliselt reguleeritavad
- Iga keele jaoks eraldi modulatsioon

*Kuidas?*
- Potentsiomeeter pingejagurina
	1. $+0.166 \: V$
	2. [[VCO#Summeerimine]] && GND
	3. $-0.166 \: V$
- Enne sisendeid trimmerid/[[Digitaalsed potentsiomeetrid]]
	- Kindla väärtuse saavutamiseks
	- [[VCO#Häälestamine]]
- 0-i saamiseks kasutada [[Väändevedru]]

---------
## LFO modulatsioon
**Nice to have!**

*Miks?*
- Saaks keset mängimist [[LFO]]-d reguleerida

## Võimalikud lahendused
*Rotary*
- + Levinud lahendus, valikus *center tapped* variante
- - Ruumi nõudev, trajektoor ringjooneline

*Slide*
- + Vähe ruumi nõudev, lineaarne trajektoor
- - Center tapped variante vähe
- [Võimalik lahendus](https://www.youtube.com/watch?time_continue=781&v=ra76YaZqjaI&embeds_referring_euri=https%3A%2F%2Fwww.reddit.com%2F)

*Joystick*
- + Soodne, saab liikumist piirata ühesuunaliseks, ei pea vedru süsteemi välja mõtlema
- - Vajab lisamehhanikat, liiguvad väiksema distantsi