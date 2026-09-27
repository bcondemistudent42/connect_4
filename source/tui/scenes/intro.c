#include <ncurses.h>

#include "tui/intro.h"
#include "tui/state.h"

void	intro_ctx_init(t_intro_ctx *ctx, t_state *state)
{
	ctx->state = state;
	ctx->animation = INTRO_FLASH;
	ctx->step = 0;
}

static void	intro_render_title(t_state *state, short y_offset)
{
	int	x;

	x = state->screen_size.x / 2 - 8;
	mvprintw(y_offset, x, " ██████  ██  ██  ");
	mvprintw(y_offset + 1, x, "██       ██  ██  ");
	mvprintw(y_offset + 2, x, "██       ████████");
	mvprintw(y_offset + 3, x, "██           ██  ");
	mvprintw(y_offset + 4, x, " ██████      ██  ");
}

void	intro_render(t_intro_ctx *ctx)
{
	int	color;

	if (ctx->animation == INTRO_FLASH)
	{
		color = PAIR_GUI;
		if (ctx->step % 5 > 2)
			color = PAIR_GUI_HIGHLIGHT;
		attron(COLOR_PAIR(color));
		intro_render_title(ctx->state, 10);
		attroff(COLOR_PAIR(color));
		ctx->step++;
		if (ctx->step == 15)
		{
			ctx->animation = INTRO_UP;
			ctx->step = 10;
		}
	}
	else
	{
		attron(COLOR_PAIR(PAIR_GUI));
		intro_render_title(ctx->state, ctx->step--);
		attroff(COLOR_PAIR(PAIR_GUI));
		if (ctx->step <= 2)
			ctx->state->current_scene = SCENE_MENU;
	}
}
