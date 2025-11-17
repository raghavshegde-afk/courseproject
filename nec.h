#ifndef NEC_H
#define NEC_H
enum Player {
    PLAYER_NONE, // Or empty
    PLAYER_RED,
    PLAYER_BLACK
};




// If game is over or not and who won
enum GameState {
    STATE_PLAYING,
    STATE_RED_WINS,
    STATE_BLACK_WINS
};

// Struct to hold all game data
 typedef struct Game {
    enum Player peg_board[24][24];
    enum Player Links[24][24][8]; //Link storage
    enum Player current_turn;
    enum GameState current_state;
} Game;

 extern char print[47][93];//To print the board with links included

//8 possible knight's move row motion because twixt connections are essentially made in a knight's move pattern
extern const int KNIGHT_MOVES_R[8];

//8 possible knight's move column motion
extern const int KNIGHT_MOVES_C[8];






void initialize_game(Game* game) ;
void print_board(Game* game) ;
void show_board(Game* game) ;
void change_turn(Game* game) ;
void print_player_prompt(enum Player player) ;
void print_winner(Game* game) ;
int find_win_path(Game* game, enum Player player, int r, int c, int visited[24][24]) ;
void check_gamestate(Game* game) ;

void place_peg(Game* game, int row, int col, enum Player player);
void remove_peg(Game* game, int row, int col);
void place_link(Game* game, int row1, int col1, int row2, int col2);
void remove_link(Game* game, int row1, int col1, int row2, int col2);


#endif