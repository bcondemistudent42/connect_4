#ifndef CONSTANTS_H
# define CONSTANTS_H

// CONSTANTS
# define MIN_WIDTH 7
# define MIN_HEIGHT 6

# define PLAYER_CHAR 'O'
# define COMPUTER_CHAR 'X'

// AI
# define AI_DEPTH 5
# define CENTER_BONUS 2
# define WIN_BONUS 1000000

// LITERALS
# define WIN_LITERAL "GGWP :)\n"
# define LOSE_LITERAL "You suck!\n"

// ERRORS
# define INIT_GAME_ERR "Error: cannot init game\n"
# define HEIGHT_GAME_ERR "Error: height cannot be under %d\n"
# define WIDTH_GAME_ERR "Error: width cannot be under %d\n"

# define INVALID_MOVE_ERR "Error: move invalid\n"

#endif
