#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define FILE_NAME "comenzi.txt"
#define HISTORY_FILE "istoric_comenzi.txt"
#define MAX_PRODUSE 100

typedef struct {
    char nume[50];
    int cantitate;
    char adresa[100];
} Comanda;

void printColor(const char *text, int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h, &info);
    SetConsoleTextAttribute(h, color);
    printf("%s", text);
    SetConsoleTextAttribute(h, info.wAttributes);
}

void salvareComanda(Comanda c) {
    FILE *f = fopen(HISTORY_FILE, "a");
    if (!f) {
        printf("Eroare la deschiderea fisierului istoric.\n");
        return;
    }
    fprintf(f, "Produs: %s\nCantitate: %d\nAdresa: %s\n\n", c.nume, c.cantitate, c.adresa);
    fclose(f);
}

void afisareIstoric() {
    printf("\nISTORIC COMENZI\n");
    FILE *f = fopen(HISTORY_FILE, "r");
    if (!f) {
        printf("Istoricul este gol.\n");
        system("pause");
        return;
    }

    char linie[200];
    while (fgets(linie, sizeof(linie), f)) {
        if (strncmp(linie, "Produs: ", 8) == 0) {
                printf("\nProdus:");
            printColor(linie + 8, 14);
        } else if (strncmp(linie, "Cantitate: ", 11) == 0) {
             printf("\nCantitate:");
            printColor(linie + 11, 10);
        } else if (strncmp(linie, "Adresa: ", 8) == 0) {
             printf("\nAdresa:");
            printColor(linie + 8, 11);
        } else {
            printf("%s", linie);
        }
    }

    fclose(f);
    system("pause");
}

void plasareComanda() {
    FILE *f = fopen(FILE_NAME, "r");
    if (!f) {
        printf("Nu s-a putut deschide meniul.\n");
        system("pause");
        return;
    }

    char nume[50], cantStr[10];
    Comanda produse[MAX_PRODUSE];
    int total = 0;

    while (fgets(nume, sizeof(nume), f) && fgets(cantStr, sizeof(cantStr), f)) {
        nume[strcspn(nume, "\r\n")] = 0;
        cantStr[strcspn(cantStr, "\r\n")] = 0;
        strcpy(produse[total].nume, nume);
        produse[total].cantitate = atoi(cantStr);
        total++;
    }
    fclose(f);

    printf("\nMENIU\n");
    for (int i = 0; i < total; i++) {
        printf("%d. ", i + 1);
        printColor(produse[i].nume, 14);
        printf("\nCantitate disponibila: ");
        char cantStr[10];
        sprintf(cantStr, "%d\n", produse[i].cantitate);
        printColor(cantStr, 10);
    }

    int opt, qty;
    printf("\nAlege produsul (1-%d): ", total);
    scanf("%d", &opt);
    getchar();

    if (opt < 1 || opt > total) {
        printf("Optiune invalida.\n");
        system("pause");
        return;
    }

    printf("Cantitate dorita (max %d): ", produse[opt - 1].cantitate);
    scanf("%d", &qty);
    getchar();

    if (qty < 1 || qty > produse[opt - 1].cantitate) {
        printf("Cantitate invalida.\n");
        system("pause");
        return;
    }

    Comanda c;
    strcpy(c.nume, produse[opt - 1].nume);
    c.cantitate = qty;

    printf("Introduceti adresa de livrare: ");
    fgets(c.adresa, sizeof(c.adresa), stdin);
    c.adresa[strcspn(c.adresa, "\r\n")] = 0;

    salvareComanda(c);

    printf("\nComanda a fost salvata cu succes!\n");
    system("pause");
}

void comandaPersonalizata() {
    Comanda c;
 printf("\nCOMANDA PERSONALIZATA\n");
    printf("Alimente dorite: ");
    fgets(c.nume, sizeof(c.nume), stdin);
    c.nume[strcspn(c.nume, "\r\n")] = 0;

    if (strlen(c.nume) == 0) {
        printf("Numele produsului este gol. Comanda anulata.\n");
        system("pause");
        return;
    }

    printf("Cantitatea dorita: ");
    scanf("%d", &c.cantitate);
    getchar();

    if (c.cantitate <= 0) {
        printf("Cantitate invalida!\n");
        system("pause");
        return;
    }

    printf("Adresa de livrare: ");
    fgets(c.adresa, sizeof(c.adresa), stdin);
    c.adresa[strcspn(c.adresa, "\r\n")] = 0;

    if (strlen(c.adresa) == 0) {
        printf("Adresa este goala. Comanda anulata.\n");
        system("pause");
        return;
    }

    salvareComanda(c);

    printf("\nComanda personalizata a fost salvata!\n");
    system("pause");
}

void meniu() {
    printf("\nMENIU\n");
    printf("1. Selectarea restaurantului\n");
    printf("2. Vizualizare istoric comenzi\n");
    printf("3. Iesire\n");
    printf("Alege: ");
}

void meniuRestaurant() {
    printf("\nMENIU RESTAURANT\n");
    printf("1. Vizualizare meniul restaurantului\n");
    printf("2. Plasare comanda personalizata\n");
    printf("3. Inapoi la meniul principal\n");
    printf("Alege: ");
}

int main() {
    int optiunePrincipal, optiuneRestaurant;

    do {
        system("cls");
        meniu();
        scanf("%d", &optiunePrincipal);
        getchar();

        switch (optiunePrincipal) {
            case 1:
                do {
                    system("cls");
                    meniuRestaurant();
                    scanf("%d", &optiuneRestaurant);
                    getchar();

                    switch (optiuneRestaurant) {
                        case 1:
                            system("cls");
                            plasareComanda();
                            break;
                        case 2:
                            system("cls");
                            comandaPersonalizata();
                            break;
                        case 3:
                            printf("Inapoi la meniul principal.\n");
                            break;
                        default:
                            printf("Optiune invalida.\n");
                            system("pause");
                    }
                } while(optiuneRestaurant != 3);
                break;

            case 2:
                system("cls");
                afisareIstoric();
                break;

            case 3:
                printf("Iesire din aplicatie.\n");
                break;

            default:
                printf("Optiune invalida.\n");
                system("pause");
        }

    } while (optiunePrincipal != 3);

    return 0;
}
