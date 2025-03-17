#include <stdlib.h>

#include "k.h"

void add_random_tile(struct game *game){
    if (game==NULL) exit(1); // ukonči ak je chyba
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;	// náhodný riadok (modulo zabezpečí rozsah)
        col = rand() % SIZE;	// náhodný stľpec
    }while(game->board[row][col] != ' ');	// opakuj pokiaľ nenájdeš prázdne pole

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){	// modulo 2 zabezpečí 0 a 1 , ak je 0 umiestni A inak umiestni B
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}


bool is_game_won(const struct game game) { 	
    // Prechádzame hernou plochou
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Ak nájdeme písmeno 'K', hráč vyhral
            if (game.board[i][j] == 'K') {
                return true;
            }
        }
    }
    // Ak sme nenašli 'K', hra pokračuje
    return false;
}

bool is_move_possible(const struct game game) {
    // Kontrola, či existuje voľné miesto
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game.board[i][j] == ' ') {
                return true;
            }
        }
    }

    // Kontrola, či existujú dve rovnaké písmená vedľa seba
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j < SIZE - 1 && game.board[i][j] == game.board[i][j + 1]) { 	// ak nie sme na konci a 2 susedné v riadku sú rovnaké 
                return true;
            }
            if (i < SIZE - 1 && game.board[i][j] == game.board[i + 1][j]) {	// ak nie sme na konci a 2 susedné v stľpci sú rovnaké
                return true;
            }
        }
    }

    return false;
}


bool update(struct game *game, int dy, int dx) {
    if (game==NULL) return NULL; 
    // Kontrola platnosti smeru
    if ((dy == 0 && dx == 0) || (dy != 0 && dx != 0)) {		// ak sú to nulové hodnoty, koniec
        return false;  // Nesprávny smer
    }

    bool changed = false;  // Indikátor, či sa stav hry zmenil

    // Posúvanie dlaždíc
    if (dy == -1) {  // Smer hore
        for (int j = 0; j < SIZE; j++) {
            for (int i = 1; i < SIZE; i++) {
                if (game->board[i][j] != ' ') { 	// ak je to prázdny znak nemáme čo posúvať
                    int k = i;		// nemôžeme meniť i (ak posúvam hore dole mením riadok) tak si zavedieme pomocnú premennú 
                    while (k > 0 && game->board[k - 1][j] == ' ') { 	// ak k je aspon 1 (som an existujucom riadku a viem sa posúvať hore k-1 a znak kde chcem ísť musí byť prázdny) 
                        game->board[k - 1][j] = game->board[k][j];	// posuň sa
                        game->board[k][j] = ' ';			// na znak z ktorého som sa posunul označ ako voľný
                        k--;						// potrebujeme kontrolovať či aj znak vedľa je rovnaký
                        changed = true;					// indikácia že som posúval
                    }
                    if (k > 0 && game->board[k - 1][j] == game->board[k][j]) {		// kontrola, či znak na ktorý som predtým posunul bol rovnaký ako ten čo som posúval
                        game->board[k - 1][j]++;					// ak bol rovnaký potom zmaň znak an ďalší v poradí
                        game->score += (1 << (game->board[k - 1][j] - 'A')) * 2;	// Aktualizácia skóre = bitový posun doľava (1 << x) znamená 2^x
                        game->board[k][j] = ' ';					// ok si posunul daj prázdny znak
                        changed = true;							// indikácia že som posúval
                    }
                }
            }
        }
    } else if (dy == 1) {  // Smer dole
        for (int j = 0; j < SIZE; j++) {
            for (int i = SIZE - 2; i >= 0; i--) {
                if (game->board[i][j] != ' ') {
                    int k = i;
                    while (k < SIZE - 1 && game->board[k + 1][j] == ' ') {
                        game->board[k + 1][j] = game->board[k][j];
                        game->board[k][j] = ' ';
                        k++;
                        changed = true;
                    }
                    if (k < SIZE - 1 && game->board[k + 1][j] == game->board[k][j]) {
                        game->board[k + 1][j]++;
                        game->score += (1 << (game->board[k + 1][j] - 'A')) * 2;  // Aktualizácia skóre
                        game->board[k][j] = ' ';
                        changed = true;
                    }
                }
            }
        }
    } else if (dx == -1) {  // Smer vľavo
        for (int i = 0; i < SIZE; i++) {
            for (int j = 1; j < SIZE; j++) {
                if (game->board[i][j] != ' ') {
                    int k = j;
                    while (k > 0 && game->board[i][k - 1] == ' ') {
                        game->board[i][k - 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                        k--;
                        changed = true;
                    }
                    if (k > 0 && game->board[i][k - 1] == game->board[i][k]) {
                        game->board[i][k - 1]++;
                        game->score += (1 << (game->board[i][k - 1] - 'A')) * 2;  // Aktualizácia skóre
                        game->board[i][k] = ' ';
                        changed = true;
                    }
                }
            }
        }
    } else if (dx == 1) {  // Smer vpravo
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE - 2; j >= 0; j--) {
                if (game->board[i][j] != ' ') {
                    int k = j;
                    while (k < SIZE - 1 && game->board[i][k + 1] == ' ') {
                        game->board[i][k + 1] = game->board[i][k];
                        game->board[i][k] = ' ';
                        k++;
                        changed = true;
                    }
                    if (k < SIZE - 1 && game->board[i][k + 1] == game->board[i][k]) {
                        game->board[i][k + 1]++;
                        game->score += (1 << (game->board[i][k + 1] - 'A')) * 2;  // Aktualizácia skóre
                        game->board[i][k] = ' ';
                        changed = true;
                    }
                }
            }
        }
    }

    return changed;
}

