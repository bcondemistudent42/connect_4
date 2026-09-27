#include <ncurses.h>

#include "connect4.h"
#include "tui/state.h"
#include "tui/renderer.h"

static void	state_init(t_state *state, t_game *game)
{
	*state = (t_state){0};
	state->running = true;
	state->game = game;
	intro_ctx_init(&state->intro_ctx, state);
	main_menu_ctx_init(&state->menu_ctx, state);
	game_ctx_init(&state->game_ctx, state);
	game_over_ctx_init(&state->game_over_ctx, state);
}

static void	handle_input(t_state *state)
{
	int	ch;

	ch = getch();
	if (ch == ERR)
		return ;
	if (state->current_scene == SCENE_MENU)
		main_menu_handle_input(&state->menu_ctx, ch);
	else if (state->current_scene == SCENE_GAME)
		game_handle_input(&state->game_ctx, ch);
	else if (state->current_scene == SCENE_GAME_OVER)
		game_over_handle_input(&state->game_over_ctx, ch);
}

static void	render(t_state *state)
{
	clear();
	getmaxyx(stdscr, state->screen_size.y, state->screen_size.x);
	if (state->screen_size.y < MIN_TERM_HEIGHT
		|| state->screen_size.x < MIN_TERM_WIDTH)
	{
		mvprintw(state->screen_size.y / 2, 0, "Screen too small!");
		refresh();
		return ;
	}
	if (state->current_scene == SCENE_INTRO)
		intro_render(&state->intro_ctx);
	else if (state->current_scene == SCENE_MENU)
		main_menu_render(&state->menu_ctx);
	else if (state->current_scene == SCENE_GAME)
		game_render(&state->game_ctx);
	else if (state->current_scene == SCENE_GAME_OVER)
		game_over_render(&state->game_over_ctx);
	refresh();
}

int	connect4_tui(t_game *game)
{
	t_state	state;

	if (init_ncurses())
	{
		free_ncurses();
		return (1);
	}
	state_init(&state, game);
	while (state.running && !state.error)
	{
		handle_input(&state);
		if (!state.running || state.error)
			break ;
		render(&state);
		timeout(100);
	}
	free_ncurses();
	return (state.error);
}
