#5V #12V #3V3

----------------
# +/- 12 V
... on toide, mida kasutada enamus süntesaatorite toiminguteks, mis tuleb [Eurorack](https://en.wikipedia.org/wiki/Eurorack) standardist.

*Miks?*
- Süntesaatori tuumikute toitmise jaoks
- Üldkasutuslik toide
- DIY süntesaatorite maailm on enamasti selle toite peal

*Kust?*
- DC toiteplokk
	- **Pinge:** 24 VDC
	- Tekitab virtuaalse GND, et saada +/- 12 V
- AC toiteplokk
	- **Pinge:** 12 VAC
	- Vajab alaldit, et +/- 12 V saada

----------------
# 5 V
... on toide, mida kasutada süntesaatori parameetrite loogika jaoks.

*Miks?*
- [[ADSR]] signaali triger
- [[Interface]] sisenditeks
- Toide [[ADC]] ja [[DAC]] jaoks

*Kust?*
- Muundada [[Toide#+/- 12 V]] toitepinge 5 V jaoks

---------------------
# 3v3
... on toide digitaalsüsteemide jaoks.

*Milleks?*
- Toide [[MCU]] jaoks
- Toide [[ADC]] ja [[DAC]] jaoks
- Toide [[Digitaalsed potentsiomeetrid]]-e jaoks

*Kust?*
- Muundada [[Toide#+/- 12 V]] või [[Toide#5 V]] pinge 3v3 jaoks
