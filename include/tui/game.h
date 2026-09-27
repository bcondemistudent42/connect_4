#ifndef TUI_GAME_H
# define TUI_GAME_H

// INCLUDES
# include "connect4.h"

// STRUCTURES
typedef struct s_state	t_state;

typedef struct s_game_context
{
	t_state	*state;
	t_game	*game;
	int		cursor_col;
	int		winner;
}	t_game_ctx;

// PROTOTYPES
void	game_ctx_init(t_game_ctx *ctx, t_state *state);
void	game_reset(t_game_ctx *ctx);
void	game_handle_input(t_game_ctx *ctx, int ch);
void	game_render(t_game_ctx *ctx);

#endif
