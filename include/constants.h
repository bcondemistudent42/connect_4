#ifndef CONSTANTS_H
# define CONSTANTS_H

// CONSTANTS
# define MIN_WIDTH 7
# define MIN_HEIGHT 6

# define PLAYER_CHAR 'O'
# define COMPUTER_CHAR 'X'

// AI
// Budget
# define MIN_AI_DEPTH 2
# define MAX_AI_DEPTH 8
# define CELLS_PER_DEPTH 100
// Heuristics
# define CENTER_BONUS 1
# define WIN_BONUS 1000000

// LITERALS
# define WIN_LITERAL "GGWP :)\n"
# define LOSE_LITERAL "You suck!\n"
# define DRAW_LITERAL "Both the computer and you suck equally.\n"

# define FIRST_TO_PLAY_LITERAL "You are the first to play, this time.\n"

// ERRORS
# define INIT_GAME_ERR "Error: cannot init game\n"
# define HEIGHT_GAME_ERR "Error: height cannot be under %d\n"
# define WIDTH_GAME_ERR "Error: width cannot be under %d\n"

# define INVALID_MOVE_ERR "Error: move invalid\n"

#endif
