#include <ncurses.h>
#include <stdlib.h>

#include "tui/main_menu.h"
#include "tui/state.h"

static void	main_menu_play(void *state_ptr)
{
	t_state	*state;

	state = state_ptr;
	game_reset(&state->game_ctx);
	state->current_scene = SCENE_GAME;
}

static void	main_menu_exit(void *state_ptr)
{
	t_state	*state;

	state = state_ptr;
	state->running = false;
}

void	main_menu_ctx_init(t_main_menu_ctx *ctx, void *state)
{
	ctx->state = state;
	ctx->buttons[0] = menu_button_init("PLAY", &main_menu_play);
	ctx->buttons[1] = menu_button_init("EXIT", &main_menu_exit);
	ctx->menu = menu_init(2, ctx->buttons);
}

void	main_menu_handle_input(t_main_menu_ctx *ctx, int ch)
{
	if (ch == 27)
		ctx->state->running = false;
	else if (ch == KEY_UP)
		menu_up_index(&ctx->menu);
	else if (ch == KEY_DOWN)
		menu_down_index(&ctx->menu);
	else if (ch == '\n' || ch == KEY_ENTER)
		menu_select(&ctx->menu, ctx->state);
}

static void	main_menu_render_title(t_state *state)
{
	int	x;

	x = state->screen_size.x / 2 - 8;
	attron(COLOR_PAIR(PAIR_GUI));
	mvprintw(2, x, " ██████  ██  ██  ");
	mvprintw(3, x, "██       ██  ██  ");
	mvprintw(4, x, "██       ████████");
	mvprintw(5, x, "██           ██  ");
	mvprintw(6, x, " ██████      ██  ");
	attroff(COLOR_PAIR(PAIR_GUI));
}

static void	main_menu_render_flyby(t_main_menu_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < FLYBY_AMOUNT)
	{
		if (ctx->flyby[i].alive)
		{
			ctx->flyby[i].x += ctx->flyby[i].velocity_x;
			attron(COLOR_PAIR(PAIR_GUI));
			mvprintw(ctx->flyby[i].y, ctx->flyby[i].x, "%c", ctx->flyby[i].c);
			attroff(COLOR_PAIR(PAIR_GUI));
		}
		else if (ctx->flyby_frequency > SPAWN_FREQUENCY)
		{
			ctx->flyby[i].x = 0;
			ctx->flyby[i].y = FLYBY_MIN_Y
				+ rand() % (ctx->state->screen_size.y - FLYBY_MIN_Y);
			ctx->flyby[i].velocity_x = 1 + rand() % FLYBY_MAX_SPEED;
			ctx->flyby[i].c = FLYBY_CHARS[rand() % (sizeof(FLYBY_CHARS) - 1)];
			ctx->flyby[i].alive = true;
			ctx->flyby_frequency = 0;
		}
		if (ctx->flyby[i].x > ctx->state->screen_size.x)
			ctx->flyby[i].alive = false;
		i++;
	}
}

void	main_menu_render(t_main_menu_ctx *ctx)
{
	t_custom_pair	color_pair;
	size_t			i;
	int				menu_x;
	int				menu_y;

	main_menu_render_flyby(ctx);
	ctx->flyby_frequency++;
	main_menu_render_title(ctx->state);
	menu_x = ctx->state->screen_size.x / 2 - 7;
	menu_y = ctx->state->screen_size.y / 2;
	i = 0;
	while (i < ctx->menu.button_count)
	{
		color_pair = PAIR_GUI;
		if (i == ctx->menu.selected_index)
			color_pair = PAIR_GUI_HIGHLIGHT;
		attron(COLOR_PAIR(color_pair));
		mvprintw(menu_y + (int)i, menu_x, "%-14s", ctx->menu.buttons[i].str);
		attroff(COLOR_PAIR(color_pair));
		i++;
	}
}
