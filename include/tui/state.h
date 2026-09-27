#ifndef TUI_STATE_H
# define TUI_STATE_H

// INCLUDES
# include <stdbool.h>

# include "connect4.h"
# include "maths.h"
# include "tui/intro.h"
# include "tui/main_menu.h"
# include "tui/game.h"
# include "tui/game_over.h"

// ENUMS
typedef enum e_scene
{
	SCENE_INTRO = 0,
	SCENE_MENU,
	SCENE_GAME,
	SCENE_GAME_OVER,
}	t_scene;

// STRUCTURES
typedef struct s_state
{
	bool			running;
	bool			error;
	t_scene			current_scene;
	t_game			*game;
	t_intro_ctx		intro_ctx;
	t_main_menu_ctx	menu_ctx;
	t_game_ctx		game_ctx;
	t_game_over_ctx	game_over_ctx;
	t_vec2			screen_size;
}	t_state;

#endif
