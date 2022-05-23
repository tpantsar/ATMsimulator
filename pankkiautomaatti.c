#include <stdio.h>
#include <string.h>

void TyhjennaPuskuri(void); // Tyhjentaa nappaimistopuskurin
void tarkista_tilinumero(void); // Tarkistaa tilinumeron ja pin-koodin
void nayta_alkuvalikko(void); // Tulostaa alkuvalikon kayttajalle
void suorita_toiminto(char valinta); // Valitsee toiminnon (otto, saldo, tapahtumat, liittymän lataus)
int tarkista_paattymisehto(char valinta); // Tarkistaa, jatketaanko pääsilmukan suorittamista
    void toiminto_otto(void);
        int rahasumman_valinta(void);
        void tulosta_tiedot(void);
    void toiminto_saldo(void);
    void toiminto_tapahtumat(void);
    void toiminto_liittyman_lataus(void);
        void liittyman_valinta(char valinta);
        int liittyman_tulostus(void);
        int ladattava_summa(void);
        void hyvaksy_maksu(double lataus, int puhelinnumero);

double saldon_maara = 513.55;

int main(void) {

    int paattymisehto = 1;
    char valintanappain, nappain, lopeta_ohjelma = 'q';

    /* Tarkistaa tilinumeron ja PIN-koodin.
     * Oikea tilinumero on .acc -tiedoston nimi (12345).
     * Oikea PIN-koodi on .acc -tiedoston ensimmäinen rivi. */
    tarkista_tilinumero();

    while (paattymisehto == 1) {

        nayta_alkuvalikko();
        valintanappain = getc(stdin);
        TyhjennaPuskuri();

        if (valintanappain == lopeta_ohjelma) {
            break;
        }
        else {
            suorita_toiminto(valintanappain);
        }
    
        nappain = getc(stdin);
        TyhjennaPuskuri();

        if (tarkista_paattymisehto(nappain) == 0) {
            paattymisehto = 0;
        }
    }
    return(0);
} /* main */


// Tyhjentää näppäimistöpuskurin
void TyhjennaPuskuri(void) {
    while (fgetc(stdin) != '\n');
}

void tarkista_tilinumero(void) {

    int flag1 = 1, flag2 = 1;
    char tilinumero[256], PinKoodi[256], PinKoodi_tarkistus[256];

    FILE *oTiedosto;

    do {
        printf("\nAnna tilinumero > ");
        fgets(tilinumero, 256, stdin);

        if (tilinumero[strlen(tilinumero)-1] == '\n')
            tilinumero[strlen(tilinumero)-1] = '\0';
        else
            TyhjennaPuskuri();

        strcat(tilinumero, ".acc");

        if ((oTiedosto = fopen(tilinumero, "r")) != NULL) {
            printf("Nappaile tunnusluku > ");

            fgets(PinKoodi, 256, stdin);

            if (PinKoodi[strlen(PinKoodi) - 1] == '\n')
                PinKoodi[strlen(PinKoodi) - 1] = '\0';
            else
                TyhjennaPuskuri();

            fgets(PinKoodi_tarkistus, 256, oTiedosto);

            do {
                if (PinKoodi_tarkistus[strlen(PinKoodi_tarkistus) - 1] == '\n')
                    PinKoodi_tarkistus[strlen(PinKoodi_tarkistus) - 1] = '\0';

                if ((flag1 = strcmp(PinKoodi, PinKoodi_tarkistus)) == 0) {
                    flag2 = 0;
                    printf("Saldosi on: %.2lfe", saldon_maara);
                }
                else {
                    flag1 = 0;
                    printf("\nTunnusluku on vaarin, yrita uudelleen!\n");
                }
            } while (flag1 == 1); /* do-while */
        } /* if */
        else {
            printf("\nTilisi on suljettu.\n");
        }
    } while (flag2 == 1); /* do-while */
}

void nayta_alkuvalikko(void) {
    printf("\n");
    printf("\nValitse\n");
    printf("Voit lopettaa STOP-nappaimella (q)\n");
    printf("\n");
    printf("Otto (o)\n");
    printf("Liittyman lataus / Puheaika (l)\n");
    printf("Saldo (s)\n");
    printf("Tapahtumat (t)\n");
}

void suorita_toiminto(char valinta) {

    char    otto = 'o',
            saldo = 's',
            tapahtumat = 't',
            liittyman_lataus = 'l';

    if (valinta == otto) // Rahan otto
        toiminto_otto();

    if (valinta == saldo) // Saldon tarkistus
        toiminto_saldo();

    if (valinta == tapahtumat) // Tapahtumien katselu
        toiminto_tapahtumat();

    if (valinta == liittyman_lataus) // Liittymän lataus
        toiminto_liittyman_lataus();
}

int tarkista_paattymisehto(char valinta) {

    int ehto;

    if (valinta == 'q')
        ehto = 0; // Lopetetaan pääsilmukan suoritus
    else
        ehto = 1; // Jatketaan pääsilmukan suorittamista

    return(ehto);
}

void toiminto_otto(void) {

    int rahasumma = 0;

    printf("\n");
    printf("Otto\n");
    printf("\n");
    printf("Valitse summa: (20, 40, 60, 90, 140, 240)\n");

    rahasumma = rahasumman_valinta(); // Rahan otto tililtä
    saldon_maara -= rahasumma; // Rahan nostaminen muuttaa saldoa
    tulosta_tiedot();
}

int rahasumman_valinta(void) {

    int rahasumma;

    scanf("%d", &rahasumma);
    switch (rahasumma) {
        case 20:
            rahasumma = 20;
            break;

        case 40:
            rahasumma = 40;
            break;

        case 60:
            rahasumma = 60;
            break;

        case 90:
            rahasumma = 90;
            break;

        case 140:
            rahasumma = 140;
            break;

        case 240:
            rahasumma = 240;
            break;

        default:
            break;
    }
    return(rahasumma);
}

void tulosta_tiedot(void) {
    printf("Haluatko tiedot?\n");
    printf("\n");
    printf("%19s\n", "Naytolle");
    printf("Ei kiitos ");
    printf("%10s", "Kuitille\n");

    printf("\n");
    printf("Ota kortti, ole hyva\n");
    printf("Rahat tulossa\n");
    printf("\n");
    printf("Ota rahat, ole hyva\n");
    printf("\n");
    printf("Kiitos kaynnista\n");
    printf("Tervetuloa uudelleen\n");
    printf("\n");
    printf("Katso uudelleen (a)\n");
    printf("Lopeta asiointi (q)\n");
}

void toiminto_saldo(void) {

    double nostettavissa = 400.00;
    double kateisnostovara = 300.00;

    printf("\nTilin tilanne\n");
    printf("\n");
    printf("Tilin saldo %20.2lf+\n", saldon_maara);
    printf("Tililta nostettavissa %10.2lf+\n", nostettavissa);
    printf("Kortin kateisnostovara %9.2lf+\n", kateisnostovara);
    printf("\n");
    printf("Jatka asiointia (a)\n");
    printf("Lopeta asiointi (q)\n");
}

void toiminto_tapahtumat(void) {
    printf("\n");
    printf("Haluatko tiedot?\n");
    printf("\n");
    printf("Naytolle\n");
    printf("Kuitille\n");
    printf("Jatka asiointia (a)\n");
    printf("Lopeta asiointi (q)\n");
}

void toiminto_liittyman_lataus(void) {

    int     puhelinnumero = 0,
            lataus_summa = 0;

    char    valinta,
            alkuun = 'a';

    printf("\n");
    printf("Liittyman lataus\n");
    printf("\n");
    printf("Valitse palvelu:\n");
    printf("Saunalahti (s)\n");
    printf("DNA (d)\n");
    printf("Go Mobile (g)\n");
    printf("Alkuun (a)\n");

    valinta = getc(stdin);
    TyhjennaPuskuri();

    if (valinta != alkuun) { // Jos ei paineta alkuun -näppäintä
        liittyman_valinta(valinta);
        puhelinnumero = liittyman_tulostus();
        lataus_summa = ladattava_summa();
        hyvaksy_maksu(lataus_summa, puhelinnumero);
    }
}

void liittyman_valinta(char valinta) {

    char    saunalahti = 's',
            dna = 'd',
            gomobile = 'g',

            a[11] = "Saunalahti",
            b[4] = "DNA",
            c[9] = "GoMobile";

    if (valinta == saunalahti) // Saunalahti
        printf("Syota %s puhelinnumero\n", a);

    if (valinta == dna) // DNA
        printf("Syota %s puhelinnumero\n", b);

    if (valinta == gomobile) // GoMobile
        printf("Syota %s puhelinnumero\n", c);
}

int liittyman_tulostus(void) {

    int numero;

    printf("(esim. 041987...)\n");
    printf("\n");
    printf("ja paina OK\n");
    scanf("%d", &numero);
    printf("Liittyman lataus: (10, 15, 20, 25, 30, 50, 100) euroa.\n");

    return(numero);
}

int ladattava_summa(void) { // Kayttaja valitsee ladattavan summan

    int lataus;

    scanf("%d", &lataus);
    switch (lataus) {
        case 10:
            lataus = 10;
            break;

        case 15:
            lataus = 15;
            break;

        case 20:
            lataus = 20;
            break;

        case 25:
            lataus = 25;
            break;

        case 30:
            lataus = 30;
            break;

        case 50:
            lataus = 50;
            break;

        case 100:
            lataus = 100;
            break;

        default:
            break;
    }
    return(lataus);
}

void hyvaksy_maksu(double lataus, int puhelinnumero) {

    printf("\n");
    printf("Hyvaksy maksu\n");

    printf("\n");
    printf("Puhelinnumero      +358%d\n", puhelinnumero);
    printf("Ladattava summa %8.2lf+\n", lataus);
    printf("Otto tililta %11.2lf-\n", lataus);
    printf("Hyvaksy\n");
    printf("\n");

    printf("Tapahtumaasi kasitellaan\n");
    printf("\n");

    printf("Ota kortti, ole hyva\n");
    printf("Puheaika maksettu\n");
    printf("Latausvahvistus tekstiviestilla.\n");
    printf("Liittymaasi +358%d on ladattu Otto-automaatilta %.2lf euroa puheaikaa.\n", puhelinnumero, lataus);

    printf("\n");
    printf("Kiitos kaynnista\n");
    printf("Tervetuloa uudelleen\n");
    printf("\n");
    printf("Katso uudelleen (a)\n");
    printf("Lopeta asiointi (q)\n");
}