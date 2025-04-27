#LFO #DAC 
- [ ] 🔼 Nuputa välja kuidas amplituudi ja sagedust kontrollida
-----------------
*Milleks?*
- Tekitada vibratot 
- Dünaamika mõjutamiseks

*Nõuded:*
- Sagedus
	- LFOd on üldjuhul 1 - 20 Hz (kuulamispiirkonnast madalam)
	- Turvalisuse mõistes võib teha 1 - 50 Hz
- Amplituud
	- Pilli mängides varieeritakse umbes ½ - 1 tooni
	- Ehk maksimaalne pinge oleks $\frac{1\:V}{12} = 0,083\:V$
	- Peak-to-peak pinge oleks $2*0,083\:V=0,166\:V$

*Kuidas?*
- **Analoog**
	- Koostada reguleeritav siinussignaaligeneraator
	- + Resolutsioon hea
	- - Siinusignaaligeneraatorid on ebastabiilsed, temperatuurist sõltuv, ruumi nõudev
- **Digitaalne**
	- [[MCU]]st saata välja juhised [[DAC]]ile, et koostada siinussignaal
		- Valikus on [[DAC#DAC63202]] integraal skeem, milles on signaaligeneraator sisse ehitatud
	- + Väike, üsnagi lihtne koostada
	- - Resolutsioon võib mõjutada

----------
### Signaali suund: [[VCO#Summeerimine]]