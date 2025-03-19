#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hof.h"

#define HOF_SIZE 10  // Maximálny počet hráčov v Hall of Fame

int load(struct player list[]) {
    FILE *file = fopen(HOF_FILE, "r");  // Otvorím súbor na čítanie;
    if (!file) return -1;  // Súbor sa nepodarilo otvoriť

    int count = 0;  // Počet načítaných položiek

    // Načítanie riadkov zo súboru
    while (count < HOF_SIZE) {
        char name[30];          // max 30 znakov (29+koniec)
        int score;              // skóre daného hrášča

        // Načítanie riadku
        if (fscanf(file, "%s %d", name, &score) != 2) {    // ak riadok neobsahuje 2 položky

            if (feof(file)){
               break;
            }
           // Ak sa nepodarilo načítať meno a skóre, skontrolujeme, či je riadok prázdny
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF) {   // kontrola na nový riadok a koniec súboru
                // Ak riadok obsahuje iné znaky ako medzery, je nesprávny
                if (ch != ' ' && ch != '\t') {
                    fclose(file);
                    return -1;  // Nesprávny formát riadku
              }
            }
            continue;  // Preskočiť prázdny riadok
        }

        // Uloženie načítaných údajov do poľa
        strncpy(list[count].name, name, 29);    // Naplníme meno
        list[count].name[29] = '\0';  // Zabezpečenie ukončenia reťazca
        list[count].score = score;      // Naplníme skóre
        count++;
    }

    fclose(file);       // uzatvorenie súboru


    // Zotriedenie zoznamu hráčov zostupne podľa skóre (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j].score < list[j + 1].score) {
                // Výmena hráčov
                struct player temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    return count;  // Vrátenie počtu načítaných položiek
}



bool save(const struct player list[], int size) {
    // Otvorenie súboru na zápis
    FILE *file = fopen(HOF_FILE, "w");
    if (!file) return false;  // Súbor sa nepodarilo otvoriť

    if ( size>10 || size<0 ) {
        fclose(file);
        return false;
    } 

    // Uloženie každého hráča do súboru
    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %d\n", list[i].name, list[i].score);
    }

    fclose(file);
    return true;  // Úspešné uloženie
}

bool add_player(struct player list[], int *size, const struct player player) {

   if (size==NULL) return NULL;


    // Ak je zoznam plný a skóre hráča je menšie ako posledné skóre v zozname, hráč sa nedostane do Hall of Fame
    if (*size == HOF_SIZE && player.score <= list[HOF_SIZE - 1].score) {
        return false;
    }

    // Nájdenie pozície, kam sa hráč zaradí
    int pos = *size;
    while (pos > 0 && list[pos - 1].score < player.score) {
        pos--;
    }

    // Ak je zoznam plný, posledný hráč bude vyradený
    if (*size == HOF_SIZE) {
        pos = HOF_SIZE - 1;
    }

    // Posunutie ostatných hráčov o jedno miesto dole
    for (int i = *size - 1; i >= pos; i--) {
        list[i + 1] = list[i];
    }

    // Zaradenie nového hráča na správne miesto
    list[pos] = player;

    // Aktualizácia veľkosti zoznamu
    if (*size < HOF_SIZE) {
        (*size)++;
    }

    return true;  // Hráč bol úspešne pridaný
}


