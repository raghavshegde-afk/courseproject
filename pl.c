#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nec.h"

void place_peg(Game* game, int row, int col, enum Player player) {
    if (row < 0 || row >= 24 || col < 0 || col >= 24) {
        printf("Invalid position\n");
        return;
    }
    if (game->peg_board[row][col] != PLAYER_NONE) {
        printf("Position already occupied\n");
        return;
    }
    game->peg_board[row][col] = player;
}

void remove_peg(Game* game, int row, int col) {
    if (game->peg_board[row][col] == PLAYER_NONE) {
        printf("No peg to remove at this position\n");
        return;
    }
    for(int k=0; k<8; k++) {
        if(game->Links[row][col][k] != PLAYER_NONE) {
            printf("Cannot remove peg with existing links\n");
            return;
        }
    }
    if(game->current_turn == PLAYER_RED && game->peg_board[row][col] != PLAYER_RED) {
        printf("You can only remove your own pegs\n");
        return;
    }
    if(game->current_turn == PLAYER_BLACK && game->peg_board[row][col] != PLAYER_BLACK) {
        printf("You can only remove your own pegs\n");
        return;
    }
    game->peg_board[row][col] = PLAYER_NONE;
}

void place_link(Game* game, int row1, int col1, int row2, int col2) {
    int nr = abs(row1 - row2);
    int r=row1-row2;
    int c=col1-col2;
    int nc = abs(col1 - col2);
    if (!((nr == 2 && nc == 1) || (nr == 1 && nc == 2))) {
        printf("Links can only be placed in a knight's move pattern\n");
        return;
    }
    //Ensure that link doesn't intersect another one
    if(r==2&&c==1){
        if(game->Links[row1-1][col1-1][3]!=PLAYER_NONE||game->Links[row1-1][col1-1][5]!=PLAYER_NONE||game->Links[row1-2][col1][4]!=PLAYER_NONE||game->Links[row1][col1-1][3]!=PLAYER_NONE||game->Links[row1][col1-1][1]!=PLAYER_NONE||game->Links[row1-1][col1][6]!=PLAYER_NONE||game->Links[row1-1][col1][4]!=PLAYER_NONE||game->Links[row1-1][col1][2]!=PLAYER_NONE||game->Links[row1-2][col1][6]!=PLAYER_NONE||game->Links[row1-1][col1-1][1]!=PLAYER_NONE){
            printf("Link intersects another link\n");
            return;
        }
    }
    if(r==2&&c==-1){
        if(game->Links[row1-1][col1+1][2]!=PLAYER_NONE||game->Links[row1-1][col1+1][4]!=PLAYER_NONE||game->Links[row1-1][col1+1][0]!=PLAYER_NONE||game->Links[row1][col1+1][2]!=PLAYER_NONE||game->Links[row1][col1+1][0]!=PLAYER_NONE||game->Links[row1-1][col1][7]!=PLAYER_NONE||game->Links[row1-1][col1][5]!=PLAYER_NONE||game->Links[row1-1][col1][3]!=PLAYER_NONE||game->Links[row1-2][col1][5]!=PLAYER_NONE){
            printf("Link intersects another link\n");
            return;
        }
    }
    if(r==1&&c==2){
        if(game->Links[row1-1][col1-1][6]!=PLAYER_NONE||game->Links[row1-1][col1-1][7]!=PLAYER_NONE||game->Links[row1-1][col1-1][4]!=PLAYER_NONE||game->Links[row1-1][col1][4]!=PLAYER_NONE||game->Links[row1-1][col1][6]!=PLAYER_NONE||game->Links[row1][col1-1][3]!=PLAYER_NONE||game->Links[row1][col1-1][1]!=PLAYER_NONE||game->Links[row1][col1-1][0]!=PLAYER_NONE||game->Links[row1][col1-2][3]!=PLAYER_NONE||game->Links[row1][col1-2][1]!=PLAYER_NONE){
            printf("Link intersects another link\n");
            return;
        }
    }
    if(r==1&&c==-2){
        if(game->Links[row1-1][col1+1][5]!=PLAYER_NONE||game->Links[row1-1][col1+1][6]!=PLAYER_NONE||game->Links[row1-1][col1+1][7]!=PLAYER_NONE||game->Links[row1-1][col1][7]!=PLAYER_NONE||game->Links[row1-1][col1][5]!=PLAYER_NONE||game->Links[row1][col1+1][0]!=PLAYER_NONE||game->Links[row1][col1+1][1]!=PLAYER_NONE||game->Links[row1][col1+1][2]!=PLAYER_NONE||game->Links[row1][col1+2][0]!=PLAYER_NONE||game->Links[row1][col1+2][2]!=PLAYER_NONE){
            printf("Link intersects another link\n");
            return;
        }
    }
    if(r<0){
        place_link(game, row2, col2, row1, col1);
        return;
    }
    if (game->peg_board[row1][col1] == PLAYER_NONE || game->peg_board[row2][col2] == PLAYER_NONE) {
        printf("Both positions must have pegs to place link\n");
        return;
    }
    if (game->peg_board[row1][col1] != game->current_turn || game->peg_board[row2][col2] != game->current_turn) {
        printf("You can only link your own pegs\n");
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (KNIGHT_MOVES_R[i] == row2 - row1 && KNIGHT_MOVES_C[i] == col2 - col1) {
            game->Links[row1][col1][i] = game->current_turn;
            game->Links[row2][col2][7-i] = game->current_turn; 
            return;
        }
    }
}

void remove_link(Game* game, int row1, int col1, int row2, int col2) {
    int nr = abs(row1 - row2);
    int nc = abs(col1 - col2);
    if (!((nr == 2 && nc == 1) || (nr == 1 && nc == 2))) {
        printf("Links can only be removed in a knight's move pattern\n");
        return;
    }
    int link_exists = 0;
    for (int i = 0; i < 8; i++) {
        if (KNIGHT_MOVES_R[i] == row2 - row1 && KNIGHT_MOVES_C[i] == col2 - col1) {
            if (game->Links[row1][col1][i] != PLAYER_NONE) {
                link_exists = 1;
                break;
            }
        }
    }
    if (!link_exists) {
        printf("No link exists between specified positions\n");
        return;
    }
    if (game->peg_board[row1][col1] != game->current_turn || game->peg_board[row2][col2] != game->current_turn) {
        printf("You can only remove links from your own pegs\n");
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (KNIGHT_MOVES_R[i] == row2 - row1 && KNIGHT_MOVES_C[i] == col2 - col1) {
            game->Links[row1][col1][i] = PLAYER_NONE;
            game->Links[row2][col2][7-i] = PLAYER_NONE; 
            return;
        }
    }
}