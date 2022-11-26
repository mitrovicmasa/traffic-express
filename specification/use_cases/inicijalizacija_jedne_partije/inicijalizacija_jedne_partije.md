## Incijalizacija jedne partije

**Kratak opis:** Aplikacija inicijalizuje sve objekte i kreira partiju na osnovu broja igrača.

**Akteri:** Igrači

**Preduslovi:** Igrači su kliknuli dugme “Ready”.

**Postuslovi:** Aplikacija započinje partiju. 

**Osnovni tok:** 
1. Aplikacija dohvata informacije o igračima. 
2. Aplikacija inicijalizuje osnovne objekte.
3. Za svakog igrača:
   * 3.1. Aplikacija nasumičnom odabirom dodeljuje nekog od preostalih bandita. 
   * 3.2. Aplikacija incijalizuje špil karata i špil metaka za svakog igrača.
   * 3.3. Aplikacija dodeljuje igraču početnu vrednost blaga.
4. Aplikacija formira niz vagona i niz rundi. 
5. Za svaki vagon u nizu:
   * 5.1. Aplikacija dodeljuje blago vagonu, na osnovu pravila igre.
6. Aplikacija postavlja maršala u lokomotivu. 
7. Aplikacija nasumično bira redosled kojim će igrači igrati.

**Alternativni tokovi:**
* A1: Neočekivani izlaz iz aplikacije: Ukoliko u bilo kom koraku korisnik prekine aplikaciju, sve zapamćene informacije o partiji se poništavaju i aplikacija završava rad. Slučaj upotrebe je završen. 

**Podtokovi:** /

**Specijalni zahtevi:** /

**Dodatne informacije:** /
