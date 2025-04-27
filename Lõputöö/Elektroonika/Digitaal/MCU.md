#MCU #DAC #ADSR #ADC 

-----------------
*Miks?*
- Digitaal signaalide töötlemine (DSP)
	- [[ADSR]] signaalitöötlus
	- Trigeri tuvastus
	- [[Interface#Membraan potentsiomeeter]] väärtuste saamine
- [[LFO]] seadistamine
- [[VCO]] jaoks noodi informatsioon
- Häälestamise võimalus

*Nõuded:*
- **SPI**
	- 3x2 [[DAC]]
	- 1x2 [[ADC]]
- **I2C**
	- >= 4x [[Digitaalsed potentsiomeetrid]]
- **PWM**
	- 4x [[ADSR]] indicator LED'ide jaoks
	- 2x [[LFO]] indicator LED'ide jaoks
- **Enkoodrid**
	- 1x [[LFO]] sagedus ja amplituud
	- 1x [[ADSR]] parameetrid
- **GPIO**
	- 2x [[Interface#Surveandur]] triger (5 V compliant)
	- 2x enkoodrite nupud
	- 3x RGB status LED
	- 4x Multiplexer SPI CS jaoks
- **Misc.**
	- 2x väline kristall
	- Bluetooth?

*Valikud:*
- STM32F401 seeria (LQFP64)
	- -RE (512k / 96k)
	- -RD (384k / 96k)
	- -RC (256k / 64k)
	- -RB (128k / 64k)