#include <stdio.h>
#include <string.h>
#include "nec.h"

void initialize_game(Game* game) {
    memset(game->peg_board, PLAYER_NONE, sizeof(game->peg_board));//From what I understand memset sets memory to a specific value
    memset(game->Links, PLAYER_NONE, sizeof(game->Links));
    game->current_turn = PLAYER_RED;
    game->current_state = STATE_PLAYING;
}


void print_board(Game* game) {
    memset(print, ' ', sizeof(print));

    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            for(int k=0;k<8;k++){
                if(game->peg_board[i][j]==PLAYER_RED){
                    print[i*2][j*4]= 'R';
                    if(game->Links[i][j][k]==PLAYER_RED){
                        
                    
                        if(k==0){
                            print[i*2-1][j*4-1] = '\\';
                            print[i*2-2][j*4-2] = '\\';
                            print[i*2-3][j*4-3] = '\\';
                        }
                        else if(k==1){
                            print[i*2-1][j*4+1] = '/';
                            print[i*2-2][j*4+2] = '/';
                            print[i*2-3][j*4+3] = '/';

                        }
                        else if(k==2){
                            print[i*2-1][4*(j-1)] = '\\';
                            
                        }
                        else if(k==3){
                            print[i*2-1][(j+1)*4] = '/';
                        }
                        else if(k==4){
                            print[i*2+1][(j-1)*4] = '/';
                        }
                        else if(k==5){
                            print[i*2+1][(j+1)*4] = '\\';
                        }
                        else if(k==6){
                            print[i*2+1][j*4-1] = '/';
                            print[i*2+2][j*4-2] = '/';
                            print[i*2+3][j*4-3] = '/';
                            
                        }
                        else if(k==7){
                            print[i*2+1][j*4+1] = '\\';
                            print[i*2+2][j*4+2] = '\\';
                            print[i*2+3][j*4+3] = '\\';
                        }
                    }
                } else if(game->peg_board[i][j]==PLAYER_BLACK){
                    print[i*2][j*4]= 'B';
                    if(game->Links[i][j][k]==PLAYER_BLACK){

                        if(k==0){
                            print[i*2-1][j*(4-1)] = '\\';
                        }
                        else if(k==1){
                            print[i*2+1][j*(4-1)] = '/';
                        }
                        else if(k==2){
                            print[i*2-1][j*4-1] = '\\';
                            print[i*2-2][j*4-2] = '\\';
                            print[i*2-3][j*4-3] = '\\';
                        }
                        else if(k==3){
                            print[i*2-3][j*4+1] = '/';
                            print[i*2-2][j*4+2] = '/';
                            print[i*2-3][j*4+3] = '/';
                        }
                        else if(k==4){
                            print[i*2+1][j*4+1] = '\\';
                            print[i*2+2][j*4+2] = '\\';
                            print[i*2+3][j*4+3] = '\\';
                        }
                        else if(k==5){
                            print[i*2+1][j*4-1] = '/';
                            print[i*2+2][j*4-2] = '/';
                            print[i*2+3][j*4-3] = '/';
                        }
                        else if(k==6){
                            print[i*2+1][j*(4+1)] = '\\';
                        }
                        else if(k==7){
                            print[i*2-1][j*(4-1)] = '/';
                        }
                        
                    
                    
                    }
                    
                }
                else{
                    print[i*2][j*4]= '.';
                }
            }
        }
    }
}

void show_board(Game* game){
    print_board(game);
    for(int i=0;i<47;i++){
        for(int j=0;j<93;j++){
            printf("%c",print[i][j]);
        }
        printf("\n");
    }
}

void change_turn(Game* game) {
    if (game->current_turn == PLAYER_RED) {
        game->current_turn = PLAYER_BLACK;
    } else {
        game->current_turn = PLAYER_RED;
    }
}


int find_if_win(Game* game, enum Player player, int r, int c) {
    if (player == PLAYER_RED && c == 23) {
        return 1;
    }
    if (player == PLAYER_BLACK && r == 23) {
        return 1;
    }
    // Mark this peg as visited
    visited[r][c] = 1;
    for (int k = 0; k < 8; k++) {
        if (game->Links[r][c][k] == player) {
            int next_r = r + KNIGHT_MOVES_R[k];
            int next_c = c + KNIGHT_MOVES_C[k];
            if (!visited[next_r][next_c]) {
                if (find_if_win(game, player, next_r, next_c)) {
                    return 1; 
                }
            }
        }
    }
    return 0;
}

void check_gamestate(Game* game) {
    if (game->current_turn == PLAYER_RED) {
        for (int i = 1; i < 23; i++) {
            if (game->peg_board[i][0] == PLAYER_RED) {
                memset(visited, 0, sizeof(visited)); 
                if (find_if_win(game, PLAYER_RED, i, 0)) {
                    game->current_state = STATE_RED_WINS;
                    return;
                }
            }
        }
    } else { 
        for (int j = 1; j < 23; j++) {
            if (game->peg_board[0][j] == PLAYER_BLACK) {
                memset(visited, 0, sizeof(visited)); 
                if (find_if_win(game, PLAYER_BLACK, 0, j)) {
                    game->current_state = STATE_BLACK_WINS;
                    return;
                }
            }
        }
    }
}
void print_move_prompt(enum Player player) {
    if (player == PLAYER_RED) {
        printf("Red's turn. Enter your move:\n");
    } else if (player == PLAYER_BLACK) {
        printf("Black's turn. Enter your move:\n");
    }
}
void print_winner(Game* game) {
    if (game->current_state == STATE_RED_WINS) {
        printf("Red wins!\n");
    } else if (game->current_state == STATE_BLACK_WINS) {
        printf("Black wins!\n");
    } 
}