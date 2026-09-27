#ifndef TUI_MAIN_MENU_H
# define TUI_MAIN_MENU_H

// INCLUDES
# include <stdbool.h>

# include "tui/menu.h"

// DEFINES
# define FLYBY_AMOUNT 24
# define FLYBY_MIN_Y 6
# define FLYBY_MAX_SPEED 2
# define SPAWN_FREQUENCY 8
# define FLYBY_CHARS "XO4"

// STRUCTURES
typedef struct s_flyby
{
	int		x;
	int		y;
	int		velocity_x;
	char	c;
	bool	alive;
}	t_flyby;

typedef struct s_state	t_state;

typedef struct s_main_menu_context
{
	t_state			*state;
	t_menu			menu;
	t_menu_button	buttons[2];
	t_flyby			flyby[FLYBY_AMOUNT];
	long			flyby_frequency;
}	t_main_menu_ctx;

// PROTOTYPES
void	main_menu_ctx_init(t_main_menu_ctx *ctx, void *state);
void	main_menu_handle_input(t_main_menu_ctx *ctx, int ch);
void	main_menu_render(t_main_menu_ctx *ctx);

#endif
