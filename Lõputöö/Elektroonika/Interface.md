#Membraan #Surveandur

--------------
# Membraan potentsiomeeter
… on potentsiomeeter, mis on tehtud lapikuks membraaniks.

*Miks?*
- Hea madala profiiliga kasutajaliides
- Simuleerib keelt
- Lihtne digitaliseerida
- Trigeri tuvastus [[ADSR]]i jaoks
	- Võib ka asendada [[#Surveandur]]

*Kuidas?*
- Pingejagur 
	- Ühendused:
	1. ([[Toide#5 V]])
	2. [[ADC]]
		- Iga potentsiomeetri jaoks eraldi sisend
	3. GND
- **Kasutada 2x** kahe "keele" jaoks

*Tootevalikud:*
- [TSP-L-0400-203-1%-ST](https://www.digikey.ee/en/products/detail/spectra-symbol/TSP-L-0400-203-1-ST/17050994) 
	- [Ametlik veebileht](https://www.spectrasymbol.com/buy-position-sensors)
	- **Tootja:** Spectra Symbol
	- **Pikkus:** 400 mm
	- **Takistus:** $20\:k\ohm$
	- Erinevad ühenduse tüübid
	- Ainult *Digikey*-st saadav

*Märkmed*
- Enne [[ADC]]-d oleks vaja panna madalpääsfilter, et kõrgemaid müra sagedusid vähendada
- Spectra Symbol-i membraan potentsiomeetri rise-fall ajad:
	- *5 - 0 V* - Keskmiselt 10,5 ms (Fall) ja 5,03 ms (Rise)
	- *0 - 5 V* - Keskmiselt 8,95 ms (Fall) ja 12,86 ms (Rise)
	- Esimesel oli pull up takisti ning teisel pull down
	- 3386 Hz LPF ($1 nF\:ja\:47 k\ohm$)

---------------
# Surveandur
... on takisti, mille sisendtakistus muutub vastavalt rõhule, mis talle rakendatakse.

*Miks?*
- Hea viis reguleerida [[VCF]]i
- Võimalus saada trigerit

*Tootevalikud:*
- [SEN0299](https://www.digikey.ee/en/products/detail/dfrobot/SEN0299/10136552) 
	- [Ametlik veebileht](https://www.dfrobot.com/product-1845.html)
	- **Tootja:** DF Robot
	- **Hind:** ~13€
	- **Pikkus:** 400 mm
	- **Reageerimisaeg:** $10\:ms$
	- **Survevahemik:** 20 - 10 000 g
- [34-00072](https://www.digikey.ee/en/products/detail/interlink-electronics/34-00072/7672217)
	- **Tootja:** Interlink Electronics
	- **Hind:** ~33€
	- **Pikkus:** 400 mm
	- **Reageerimisaeg:** $3\:\micro s$ 
	- **Survevahemik:** 20 - 2 000 g

------------
### Signaali suund: [[VCO]]