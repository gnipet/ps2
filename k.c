#include <stdlib.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
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
            if (j < SIZE - 1 && game.board[i][j] == game.board[i][j + 1]) {
                return true;
            }
            if (i < SIZE - 1 && game.board[i][j] == game.board[i + 1][j]) {
                return true;
            }
        }
    }

    return false;
}


bool update(struct game *game, int dy, int dx) {
    // Kontrola platnosti smeru
    if ((dy == 0 && dx == 0) || (dy != 0 && dx != 0)) {
        return false;  // Nesprávny smer
    }

    bool changed = false;  // Indikátor, či sa stav hry zmenil

    // Posúvanie dlaždíc
    if (dy == -1) {  // Smer hore
        for (int j = 0; j < SIZE; j++) {
            for (int i = 1; i < SIZE; i++) {
                if (game->board[i][j] != ' ') {
                    int k = i;
                    while (k > 0 && game->board[k - 1][j] == ' ') {
                        game->board[k - 1][j] = game->board[k][j];
                        game->board[k][j] = ' ';
                        k--;
                        changed = true;
                    }
                    if (k > 0 && game->board[k - 1][j] == game->board[k][j]) {
                        game->board[k - 1][j]++;
                        game->score += (1 << (game->board[k - 1][j] - 'A')) * 2;  // Aktualizácia skóre
                        game->board[k][j] = ' ';
                        changed = true;
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

