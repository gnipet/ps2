#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>
#include "k.h"
#include "ui.h"


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



return 0;

}

