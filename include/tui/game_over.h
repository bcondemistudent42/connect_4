#ifndef TUI_GAME_OVER_H
# define TUI_GAME_OVER_H

// INCLUDES
# include "tui/menu.h"

// STRUCTURES
typedef struct s_state	t_state;

typedef struct s_game_over_context
{
	t_state			*state;
	t_menu			menu;
	t_menu_button	buttons[1];
	int				winner;
}	t_game_over_ctx;

// PROTOTYPES
void	game_over_ctx_init(t_game_over_ctx *ctx, t_state *state);
void	game_over_handle_input(t_game_over_ctx *ctx, int ch);
void	game_over_render(t_game_over_ctx *ctx);

#endif
