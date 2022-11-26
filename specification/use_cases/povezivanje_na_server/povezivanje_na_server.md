## Povezivanje na server

**Kratak opis:** Igrač upisuje svoje ime i bira kada je spreman za početak partije.

**Akteri:** Igrači.

**Preduslovi:** Igrači su kliknuli dugme “Play” iz glavnog menija.

**Postuslovi:** Aplikacija je zapamtila informacije o igračima. 

**Osnovni tok:** 
1. Aplikacija prikazuje dijalog za podešavanje imena.
2. Igrač je pritisnuo dugme “Connect”.
	* 2.1. Ako je Igrač upisao svoje ime:
		* 2.1.1. Aplikacija čuva ime. Prelazi se na korak 3.
	* 2.2. Ako Igrač nije ništa upisao u polje za ime:
		* 2.2.1. Aplikacija mu dodeljuje nasumično ime. Prelazi se na korak 3.
3. Klijent šalje serveru TCP zahtev za povezivanje.
4. Server odobrava taj zahtev i proverava da li je klijent prvi koji se povezuje na server.
    * 4.1. Ako je Igrač prvi koji se konektovao na server:
		* 4.1.1. Igraču se dodeljuje uloga vlasnika sobe. Prelazi se na korak 5.
5. Uspostavlja se TCP konekcija i otvara se soba za čekanje.
6. Igrač pritiska dugme “Ready”. 
7. Ako je Igrač vlasnik sobe:
    * 7.1. Igrač pritiska dugme “Start” i pokreće se partija sa svim Igračima koji su označili da su spremni.


**Alternativni tokovi:**
* A1: Neočekivani izlaz iz aplikacije: Ukoliko u bilo kom koraku korisnik prekine aplikaciju, sve zapamćene informacije o partiji se poništavaju i aplikacija završava rad. Slučaj upotrebe je završen. 

**Podtokovi:** /

**Specijalni zahtevi:** /

**Dodatne informacije:** / 