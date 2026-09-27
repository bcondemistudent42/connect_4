#include <ncurses.h>

#include "libft.h"
#include "constants.h"

#include "tui/game_over.h"
#include "tui/state.h"

static void	game_over_quit(void *state_ptr)
{
	t_state	*state;

	state = state_ptr;
	state->running = false;
}

void	game_over_ctx_init(t_game_over_ctx *ctx, t_state *state)
{
	ctx->state = state;
	ctx->winner = EMPTY;
	ctx->buttons[0] = menu_button_init("QUIT", &game_over_quit);
	ctx->menu = menu_init(1, ctx->buttons);
}

void	game_over_handle_input(t_game_over_ctx *ctx, int ch)
{
	if (ch == 27)
		ctx->state->running = false;
	else if (ch == '\n' || ch == KEY_ENTER)
		menu_select(&ctx->menu, ctx->state);
}

void	game_over_render(t_game_over_ctx *ctx)
{
	char	*message;
	int		x;
	int		y;

	if (ctx->winner == PLAYER)
		message = WIN_LITERAL;
	else if (ctx->winner == COMPUTER)
		message = LOSE_LITERAL;
	else
		message = DRAW_LITERAL;
	y = ctx->state->screen_size.y / 2;
	x = ctx->state->screen_size.x / 2 - (int)ft_strlen(message) / 2;
	attron(COLOR_PAIR(PAIR_GUI));
	mvprintw(y, x, "%s", message);
	attroff(COLOR_PAIR(PAIR_GUI));
	attron(COLOR_PAIR(PAIR_GUI_HIGHLIGHT));
	mvprintw(y + 3, ctx->state->screen_size.x / 2 - 2, "QUIT");
	attroff(COLOR_PAIR(PAIR_GUI_HIGHLIGHT));
}
