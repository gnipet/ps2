#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main(){

// game is won
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};
printf("is won: %d\n", is_game_won(game));
// stdout: 1
// game is not won
struct game game0 = {
    .board = {
        {'A', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'A'},
        {'B', ' ', ' ', ' '}
    },
    .score = 0
};

printf("is won: %d\n", is_game_won(game0));
// stdout: 0


// another move is possible
struct game game1 = {
    .board = {
        {'A', 'A', 'C', 'D'},
        {'A', 'F', 'G', 'H'},
        {'I', 'J', 'J', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is move possible: %d\n", is_move_possible(game1));
// stdout: 1
// another move is not possible
struct game game2 = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is move possible: %d\n", is_move_possible(game2));
// stdout: 0


// wrong call
printf("result: %d\n", update(&game, 1, 1));     // Výstup: 0 (false)
// result = false
// move right
struct game game3 = {
    .board = {
        {'A', ' ', ' ', ' '},
        {'B', ' ', ' ', 'B'},
        {'C', 'C', 'C', ' '},
        {'D', 'D', 'D', 'D'}
    },
    .score = 0
};

printf("result: %d\n", update(&game3, 0, 1));
render(&game3);
/*
game = {
    .board = {
        {' ', ' ', ' ', 'A'},
        {' ', ' ', ' ', 'C'},
        {' ', ' ', 'C', 'D'},
        {' ', ' ', 'E', 'E'}
    },
    .score = 88
};
result = true;
*/
// can't move left
struct game game4 = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'}
    },
    .score = 1234
};

printf("result: %d\n", update(&game4, 0, -1));
render(&game4);
/*
game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'},
        {'A', 'B', 'C', 'D'}
    },
    .score = 1234
};
result = false;
*/


printf("Test funkcie Load.\n");
 // Pole štruktúr pre Hall of Fame
//printf("Test1.\n");
 struct player hof[10] = {0};
//printf("Test2.\n");
    // Načítanie Hall of Fame zo súboru "score"
    int count = load(hof);
//printf("Test3.\n");
    if (count == -1) {
printf("Chyba: Súbor sa nepodarilo načítať alebo má nesprávny formát.\n");
    } else {
        // Výpis načítaných hodnôt
        printf("result: %d\n", count);
    }

printf("Test funkcie Save.\n");
struct player hof2[10] = {
        {"Jozef", 600},
        {"Miroslav", 550},
        {"Ivan", 500},
        {"Katarina", 450},
        {"Marek", 400}
    };

    // Uloženie Hall of Fame do súboru
    bool result = save(hof2, 5);

    if (result) {
        printf("Hall of Fame bola úspešne uložená.\n");
    } else {
        printf("Chyba: Hall of Fame sa nepodarilo uložiť.\n");
    }

printf("Test funkcie Add_player.\n");
struct player list[10];
struct player player = {
    .name = "peter",
    .score = 300
};
int size = load(list);
printf("%d",size);
bool result2 = add_player(list, &size, player);
if (result2) {
        printf("Hráč sa dostal do Hall of Fame.\n");
    } else {
        printf("Málo bodov na Hall of Fam.\n");
    }

bool result3 = save(list, size);

    if (result3) {
        printf("Hall of Fame bola úspešne uložená.\n");
    } else {
        printf("Chyba: Hall of Fame sa nepodarilo uložiť.\n");
    }




return 0;

}

