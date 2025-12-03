#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "nec.h"

char print[50][98];
const int KNIGHT_MOVES_C[8] = { -1,  1, -2,  2, -2,  2, -1,  1 };
const int KNIGHT_MOVES_R[8] = { -2, -2, -1, -1,  1,  1,  2,  2 };
int visited[24][24];

int main() {
    Game my_game;
    initialize_game(&my_game); // Set board to NONE, turn to RED, state to PLAYING
    memset(print, ' ', sizeof(print));
    while (my_game.current_state == STATE_PLAYING) {
        show_board(&my_game);
        print_move_prompt(my_game.current_turn);
        printf("Input coords to place peg:");
        int row, col;
        // scanf("%d %d", &row, &col);
        if (scanf("%d %d", &row, &col) != 2) {
        while (getchar() != '\n'); // Clear buffer manually if you don't use a helper func
        continue;
        }
        if(row < 0 || row >= 24 || col < 0 || col >= 24) {
            printf("Invalid position\n");
            continue;
        }
        if(my_game.peg_board[row][col] != PLAYER_NONE) {
            printf("Position already occupied\n");
            continue;
        }
        if(my_game.current_turn == PLAYER_RED){
            if(row<=0 || row>=23){
                printf("Red pegs must be placed in rows 1-22\n");
                continue;
            }
        }
        if(my_game.current_turn == PLAYER_BLACK){
            if(col<=0 || col>=23){
                printf("Black pegs must be placed in columns 1-22\n");
                continue;
            }
        }
        place_peg(&my_game, row, col, my_game.current_turn);
        while(1) {
            char action;
            printf("Enter action (R for Remove Peg, L for Place Link, S for Remove Link, E for End of Turn,Q to Quit,N for new game):");
            scanf(" %c", &action);
            if (action == 'R') {
                int row1, col1;
        
                printf("Enter coordinates (row col):");
                scanf("%d %d", &row1, &col1);
                if(row1 < 0 || row1 >= 24 || col1 < 0 || col1 >= 24) {
                    printf("Invalid position\n");
                    continue;
                }
                remove_peg(&my_game, row1, col1);
            } else if (action == 'L') {
                int row1, col1;
        
                printf("Enter coordinates (row col):");
                scanf("%d %d", &row1, &col1);
                int row2, col2;
                printf("Enter second coordinates for link placement (row col):");
                scanf("%d %d", &row2, &col2);
                if(row1 < 0 || row1 >= 24 || col1 < 0 || col1 >= 24 || row2 < 0 || row2 >= 24 || col2 < 0 || col2 >= 24) {
                    printf("Invalid position\n");
                    continue;
                }
                place_link(&my_game, row1, col1, row2, col2);
            } else if (action == 'S') {
                int row1, col1;
        
                printf("Enter coordinates (row col):");
                scanf("%d %d", &row1, &col1);
                int row2, col2;
                printf("Enter second coordinates for link removal (row col):");
                scanf("%d %d", &row2, &col2);
                if(row1 < 0 || row1 >= 24 || col1 < 0 || col1 >= 24 || row2 < 0 || row2 >= 24 || col2 < 0 || col2 >= 24) {
                    printf("Invalid position\n");
                    continue;
                }
                remove_link(&my_game, row1, col1, row2, col2);
            } 
            else if(action == 'E'){
                break;
            }
            else if(action =='N'){
                initialize_game(&my_game);
                change_turn(&my_game);
                break;
            }
            else if(action=='Q'){
                if (my_game.current_turn == PLAYER_RED) {
                    my_game.current_state = STATE_BLACK_WINS;
                }
                else{
                    my_game.current_state = STATE_RED_WINS;
                }
                break;
            }
            else {
                printf("Invalid action\n");
            }
        }
        check_gamestate(&my_game);
        change_turn(&my_game);
    }
    print_winner(&my_game);
    return 0;
}


