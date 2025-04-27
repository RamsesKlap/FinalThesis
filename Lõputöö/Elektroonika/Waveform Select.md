- [ ] 🔽 Debounce'i skeem
--------------
# Miks?
- Selleks, et keset mängimist kõrgemaid või madalamaid noote kätte saada

# Kuidas?
- Kasutada Mom-Off-Mom rocker lülitit
- Selle väljund läheb 3/4-bit binary counterisse
- Counter-i väljund läheb kahte "5:1" Muxi, kus läheb +/- 2 V [[VCO]]sse

# Kuidas valid?
- Rotary encoder
	- Enkoodri otsa panna üks flip flop, mis seadistab suuna (vt pilt sellest kaustast)
- Binary up/down counter
	- Loeb kas 0 -> 9 või vastupidi, skippides 10 - 15
- Multiplexer
	- 2x 16:1 multiplekserit, mida juhitakse paralleelselt
	- Sisendid 10 - 15 ignoreeritakse

---------
### Signaali suund: [[VCA]]