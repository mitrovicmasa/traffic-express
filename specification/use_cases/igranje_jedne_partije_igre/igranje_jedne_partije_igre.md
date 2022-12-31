### Igranje jedne partije igre:

**Kratak opis:** Igrač započinje jednu partiju igre iz glavnog menija aplikacije. Aplikacija učitava povezivanje na server. Nakon odigrane partije, aplikacija korisniku prikazuje informacije o osvojenim poenima i pobedniku. 

**Akteri:** Igrači - igraju jednu partiju igre

**Preduslovi:** Aplikacija je pokrenuta i prikazuje se glavni meni. 

**Postuslovi:** Igrač je vraćen u glavni meni.

**Osnovni tok:**
1. Igrač bira dugme “Play” iz glavnog menija. Prelazi se na slučaj upotrebe “Povezivanje na server”.
2. Aplikacija dohvata informacije o povezanim igračima.
3. Aplikacija konstruiše novu partiju i prelazi se na slučaj upotrebe “Inicijalizacija jedne partije”.
4. Sve dok ima igrača:
	* 4.1. Igrač bira početnu poziciju svog bandita.
5. Sve dok ima faza u partiji, za svaku fazu:
	* 5.1. Aplikacija izvršava akciju koja je dodeljena trenutnoj fazi.
	* 5.2. Za svakog igrača:
		* 5.2.1. Igrač vuče 6 karata iz svog špila.
	* 5.3. Sve dok ima minifaza u trenutnoj fazi, za svaku minifazu:
		* 5.3.1. Za svaki potez igrača u partiji:
			* 5.3.1.1. Ako je igrač izabrao jednu kartu iz ruke:
				* 5.3.1.1.1. Aplikacija pamti njegovu kartu i prikazuje je u skladu sa minifazom. Po završetku, prelazi se na korak 5.3.1.3.
			* 5.3.1.2. Ako je igrač odabrao da vuče 3 karte iz špila:
				* 5.3.1.2.1. Aplikacija nasumično dodeljuje igraču 3 karte iz špila. Prelazi se na korak 5.3.1.3.
			* 5.3.1.3. Aplikacija obaveštava da je potez gotov.
		* 5.3.2. Aplikacija obaveštava da je minifaza gotova. 
	* 5.4. Aplikacija prolazi kroz zapamćene karte igrača.
	* 5.5. Sve dok ima karata, za svaku zapamćenu kartu bandita:
		* 5.5.1. Igrač bira kako će da se odigra njegova karta.
		* 5.5.2. Aplikacija izvršava potez Igrača. 
		* 5.5.3. Aplikacija prikazuje šta je Igrač odigrao. 
	* 5.6. Aplikacija obaveštava da je faza gotova. 
6. Aplikacija obaveštava da je igra završena i prelazi se na slučaj upotrebe “Prikazivanje rang liste”. 
7. Aplikacija prelazi na glavni meni. 

**Alternativni tokovi:**
* A1: Neočekivani izlaz iz aplikacije: Ukoliko u bilo kom koraku korisnik prekine aplikaciju, sve zapamćene informacije o partiji se poništavaju i aplikacija završava rad. Slučaj upotrebe je završen. 
* A2: Prekid konekcije sa serverom: Ukoliko se u bilo kom trenutku igrač diskonektuje sa servera, aplikacija nastavlja partiju umesto njega igrajući nasumične poteze. Aplikacija prikazuje igraču prikazuje poruku da je diskonektovan i vraća ga u glavni meni. Slučaj upotrebe je završen. 

**Podtokovi:** /

**Specijalni zahtevi:** Svaki igrač mora biti povezan na internet i posedovati kod sebe klijent aplikacije. Server aplikacije mora biti pokrenut u trenutku pokretanja partije. 

**Dodatne informacije:** 

