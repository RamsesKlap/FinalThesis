#ADC 

---------
*Milleks?*
- [[Interface#Membraan potentsiomeeter]]i väljundi digitaliseerimiseks/kvantimiseks

*Nõuded:*
- Reageerimiskiirus võiks olla vähem kui *40 ms*, ideaalselt 0,5 ms lähedal -> **25 S/s - 2 kS/s** x 10...
	- Inimkuulmine kuuleb helide viivituse kuni umbes 0,5 ms vahemikuga
	- Pilli mängimisel tuntakse latency-t alates 40 ms
- Rohkem kui 12-bitti pole vaja (0,8 mV samm 3,3 V puhul)
- 2 kanalit
- SPI ühendusega kiiruse jaoks
- Delta-Sigma või SAR

*Nice to have*
- Track and hold / Sample and hold

*Valikud (2 kanalit)*
[Mouseri link filtriga](https://www.mouser.ee/c/semiconductors/data-converter-ics/analog-to-digital-converters-adc/?architecture=SAR~~Sigma-Delta&interface%20type=3-Wire%2C%20Microwire%2C%20SPI%7C~3-Wire%2C%20QSPI%2C%20SPI~~3-Wire%2C%20SPI%7C~I2C%2C%20SPI%7C~SPI&mounting%20style=SMD%2FSMT&number%20of%20channels=2%20Channel&resolution=8%20bit~~12%20bit&instock=y&active=y&rp=semiconductors%2Fdata-converter-ics%2Fanalog-to-digital-converters-adc%7C~Interface%20Type%7C~Architecture%7C~Resolution)
- [MCP3202](https://www.mouser.ee/ProductDetail/Microchip-Technology/MCP3202-BI-SN?qs=C%252BuF95oynlkGMhp5%2FSqbew%3D%3D)
	- 3,63 €/tk
	- [Teek, mis pole STM32-le](https://github.com/souviksaha97/MCP3202/tree/master)
	- Sampling kiirus: *100 kS/s at 5 V*
	- Resolutsioon: *12 bitti*
	- Kanaleid: *2*
	- Tüüp: *SAR*
- [MCP3008](https://www.mouser.ee/ProductDetail/Microchip-Technology/MCP3008T-E-SL?qs=8Wlm6%252BaMh8Tmb4M1ZqzJvQ%3D%3D)
	- 2,76 €/tk
	- [Teek](https://github.com/bhf32/MCP3008-STM32/tree/main)
	- Sampling kiirus: *200 kS/s at 5 V*
	- Resolutsioon: *10 bitti*
	- Kanaleid: *4*
	- Tüüp: *SAR*

*Valikud (1-kanal)*
[Mouseri link filtriga](https://www.mouser.ee/c/semiconductors/data-converter-ics/analog-to-digital-converters-adc/?architecture=SAR&interface%20type=3-Wire%2C%20Microwire%2C%20SPI%7C~3-Wire%2C%20QSPI%2C%20SPI~~3-Wire%2C%20SPI%7C~I2C%2C%20SPI%7C~SPI&mounting%20style=SMD%2FSMT&number%20of%20channels=1%20Channel&resolution=8%20bit~~12%20bit&instock=y&active=y&rp=semiconductors%2Fdata-converter-ics%2Fanalog-to-digital-converters-adc%7C~Interface%20Type%7C~Resolution&sort=pricing)
- [ADS7866](https://www.mouser.ee/ProductDetail/Texas-Instruments/ADS7866IDBVT?qs=%252BvKcWiXw%252BzS702eoPmcsqA%3D%3D)
	- 3,91 €/tk
	- Teeki pole, kuid vist pole vaja
		- Tõmmates CS madalaks hakkab põhimõtteliselt kohe andmeid saatma
	- Sampling kiirus: *200 kS/s*
	- Conversion time: *3,82 us*
	- Resolutsioon: *12 bitti*
	- Kanaleid: *1*
	- Tüüp: *SAR*
- [ADS7041](https://www.mouser.ee/ProductDetail/Texas-Instruments/ADS7041IDCUR?qs=pqSajtDZXRXIgoND%252Bu4s8g%3D%3D)
	- 1,75 €/tk
	- Sama olukord teegiga
	- Sampling kiirus: *... 1 MS/s*
	- Conversion time: *165 ns*
	- Resolutsioon: *10 bitti*
	- Kanaleid: *1*
	- Tüüp: *SAR*
- [ADS7887](https://www.mouser.ee/ProductDetail/Texas-Instruments/ADS7887SDCKT?qs=%252BvKcWiXw%252BzRenXT9uRJbow%3D%3D)
	- 3,91 €/tk
	- Sampling kiirus: *1 - 1,25 MS/s*
	- Conversion time: *560 ns* 
	- Resolutsioon: *10 bitti*
	- Kanaleid: *1*
	- Tüüp: *SAR*