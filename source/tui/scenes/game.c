#include <ncurses.h>

#include "libft.h"
#include "constants.h"

#include "tui/game.h"
#include "tui/state.h"

void	game_ctx_init(t_game_ctx *ctx, t_state *state)
{
	ctx->state = state;
	ctx->game = state->game;
	ctx->cursor_col = 0;
	ctx->winner = EMPTY;
}

void	game_reset(t_game_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->game->h)
	{
		ft_bzero(ctx->game->grid[i], ctx->game->w);
		i++;
	}
	ctx->cursor_col = 0;
	ctx->winner = EMPTY;
}

void	game_handle_input(t_game_ctx *ctx, int ch)
{
	int	winner;

	if (ctx->winner != EMPTY)
		return ;
	if (ch == 27)
	{
		ctx->state->current_scene = SCENE_MENU;
		return ;
	}
	if (ch == KEY_LEFT && ctx->cursor_col > 0)
		ctx->cursor_col--;
	else if (ch == KEY_RIGHT && ctx->cursor_col < ctx->game->w - 1)
		ctx->cursor_col++;
	else if (ch == '\n' || ch == KEY_ENTER)
	{
		if (make_player_move(ctx->game, ctx->cursor_col))
			return ;
		winner = check_win(ctx->game);
		if (winner == EMPTY)
		{
			make_ai_move(ctx->game, true);
			winner = check_win(ctx->game);
		}
		if (winner != EMPTY)
		{
			ctx->winner = winner;
			ctx->state->game_over_ctx.winner = winner;
			ctx->state->current_scene = SCENE_GAME_OVER;
		}
	}
}

static void	game_render_cell(t_game *game, int row, int col, int y, int x)
{
	char	piece;

	piece = game->grid[row][col];
	if (piece == EMPTY)
		return ;
	if (piece == COMPUTER)
		attron(COLOR_PAIR(PAIR_COMPUTER));
	else
		attron(COLOR_PAIR(PAIR_PLAYER));
	if (piece == COMPUTER)
		mvaddch(y, x, COMPUTER_CHAR);
	else
		mvaddch(y, x, PLAYER_CHAR);
	if (piece == COMPUTER)
		attroff(COLOR_PAIR(PAIR_COMPUTER));
	else
		attroff(COLOR_PAIR(PAIR_PLAYER));
}

static void	game_render_cursor(t_game_ctx *ctx, int top, int left)
{
	int	x;

	x = left + 1 + ctx->cursor_col * CELL_WIDTH + (CELL_WIDTH - 1) / 2;
	attron(COLOR_PAIR(PAIR_CURSOR));
	mvaddch(top - 1, x, 'v');
	attroff(COLOR_PAIR(PAIR_CURSOR));
}

static void	game_render_borders(t_game *game, int top, int left)
{
	int	right;
	int	bottom;
	int	i;
	int	j;

	right = left + game->w * CELL_WIDTH;
	bottom = top + game->h * CELL_HEIGHT;
	mvaddch(top, left, ACS_ULCORNER);
	mvaddch(top, right, ACS_URCORNER);
	mvaddch(bottom, left, ACS_LLCORNER);
	mvaddch(bottom, right, ACS_LRCORNER);
	i = left + 1;
	while (i < right)
	{
		mvaddch(top, i, ACS_HLINE);
		mvaddch(bottom, i, ACS_HLINE);
		i++;
	}
	i = top + 1;
	while (i < bottom)
	{
		mvaddch(i, left, ACS_VLINE);
		mvaddch(i, right, ACS_VLINE);
		i++;
	}
	i = 1;
	while (i < game->w)
	{
		mvaddch(top, left + i * CELL_WIDTH, ACS_TTEE);
		mvaddch(bottom, left + i * CELL_WIDTH, ACS_BTEE);
		j = top + 1;
		while (j < bottom)
			mvaddch(j++, left + i * CELL_WIDTH, ACS_VLINE);
		i++;
	}
	i = 1;
	while (i < game->h)
	{
		mvaddch(top + i * CELL_HEIGHT, left, ACS_LTEE);
		mvaddch(top + i * CELL_HEIGHT, right, ACS_RTEE);
		j = left + 1;
		while (j < right)
			mvaddch(top + i * CELL_HEIGHT, j++, ACS_HLINE);
		i++;
	}
	i = 1;
	while (i < game->h)
	{
		j = 1;
		while (j < game->w)
		{
			mvaddch(top + i * CELL_HEIGHT, left + j * CELL_WIDTH, ACS_PLUS);
			j++;
		}
		i++;
	}
}

void	game_render(t_game_ctx *ctx)
{
	t_game	*game;
	int		top;
	int		left;
	int		row;
	int		col;

	game = ctx->game;
	left = (ctx->state->screen_size.x - game->w * CELL_WIDTH) / 2;
	top = (ctx->state->screen_size.y - (game->h * CELL_HEIGHT + 4)) / 2 + 1;
	game_render_cursor(ctx, top, left);
	row = 0;
	while (row < game->h)
	{
		col = 0;
		while (col < game->w)
		{
			game_render_cell(game, row, col,
				top + 1 + row * CELL_HEIGHT,
				left + 1 + col * CELL_WIDTH + (CELL_WIDTH - 1) / 2);
			col++;
		}
		row++;
	}
	game_render_borders(game, top, left);
	attron(COLOR_PAIR(PAIR_GUI));
	mvprintw(top + game->h * CELL_HEIGHT + 2, left,
		"Arrows: select column, enter: validate move");
	mvprintw(top + game->h * CELL_HEIGHT + 3, left,
		"Escape: access menu");
	attroff(COLOR_PAIR(PAIR_GUI));
}
