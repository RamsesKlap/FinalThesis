#DAC 

-----------
*Milleks?*
- [[ADSR]], [[LFO]], [[VCO]] signaalide väljastamiseks

*Nõuded:*
- Sama kiire, kui mitte kiirem, kui [[ADC]]
	- *25 S/s - 2 kS/s* x 10...
- Minimaalselt 10 bitti
	- Teoorias saaks 6 bitisega ka hakkama, aga sealt võib tulla suuremad vead
- Kokku 5 kanalit
	- 2 x [[ADSR]]
	- 2 x [[VCO]]
	- 1 x [[LFO]]
- SPI ühendusega kiiruse jaoks

*Nice to have:*
- Sisse ehitatud signaaligeneraator [[LFO]] jaoks

*Valikud:*
- [DACx3202](https://www.mouser.ee/ProductDetail/Texas-Instruments/DAC63202RTER?qs=vvQtp7zwQdPHQC4JGzOJhQ%3D%3D)
	- *4,23 €/tk* (x = 6) v *3,16 €/tk* (x = 5)
	- Resolutsioon: *12 v 10 bitti*
	- Config jääb flash mällu alles
	- Sisemine signaaligeneraator
	- Oleks hea LFO jaoks
- [DAC8562](https://www.mouser.ee/ProductDetail/Texas-Instruments/DAC8562TDGSR?qs=yajEpaT76uRlRTSVGMxFig%3D%3D)
	- *8,83 €/tk*
	- Resolutsioon: *16 bitti*
	- [Teek](https://github.com/darrenaw1/DAC8562-Driver)
- [DAC60501](https://www.mouser.ee/c/?q=DAC60501)
	- *2,21 €/tk*
	- Resolutsioon: *12 bitti*
	- [Teek](https://github.com/mozinitu/dac80508/blob/main/src/dac80508.c)
- 

*Ühe kanaliga*
- 