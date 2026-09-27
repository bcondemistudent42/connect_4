#include <ncurses.h>
#include <stdlib.h>

#include "libft.h"
#include "constants.h"

#include "tui/game.h"
#include "tui/state.h"

#define DROP_FRAME_MS 60
#define BLINK_FRAMES 10
#define BLINK_FRAME_MS 200

typedef struct s_cell
{
	int	row;
	int	col;
}	t_cell;

// PROTOTYPES
static void	game_board_offsets(t_game_ctx *ctx, int *top, int *left);
static void	game_render_cell(char piece, int y, int x);
static void	game_animate_drop(t_game_ctx *ctx, int col, int landing_row);
static void	game_ai_move(t_game_ctx *ctx, int *out_row, int *out_col);
static void	game_blink_winner(t_game_ctx *ctx, int row, int col);

void	game_ctx_init(t_game_ctx *ctx, t_state *state)
{
	ctx->state = state;
	ctx->game = state->game;
	ctx->cursor_col = 0;
	ctx->winner = EMPTY;
	ctx->game->pfirst = rand() % 2;
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
	ctx->game->pfirst = rand() % 2;
}

void	game_handle_input(t_game_ctx *ctx, int ch)
{
	int	row;
	int	col;
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
		col = ctx->cursor_col;
		row = get_height(ctx->game, col);
		if (row < 0 || make_player_move(ctx->game, col))
			return ;
		game_animate_drop(ctx, col, row);
		winner = check_win(ctx->game);
		if (winner != EMPTY)
			game_blink_winner(ctx, row, col);
		if (winner == EMPTY)
		{
			game_ai_move(ctx, &row, &col);
			winner = check_win(ctx->game);
			if (winner != EMPTY)
				game_blink_winner(ctx, row, col);
		}
		if (winner != EMPTY)
		{
			ctx->winner = winner;
			ctx->state->game_over_ctx.winner = winner;
			ctx->state->current_scene = SCENE_GAME_OVER;
		}
	}
}

static void	game_board_offsets(t_game_ctx *ctx, int *top, int *left)
{
	*left = (ctx->state->screen_size.x - ctx->game->w * CELL_WIDTH) / 2;
	*top = (ctx->state->screen_size.y
			- (ctx->game->h * CELL_HEIGHT + 4)) / 2 + 1;
}

static void	game_render_cell(char piece, int y, int x)
{
	if (piece == COMPUTER)
		attron(COLOR_PAIR(PAIR_COMPUTER));
	else
		attron(COLOR_PAIR(PAIR_PLAYER));
	if (piece == COMPUTER)
		mvaddch(y, x, COMPUTER_CHAR);
	else if (piece == PLAYER)
		mvaddch(y, x, PLAYER_CHAR);
	else
		mvaddch(y, x, ' ');
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
	game_board_offsets(ctx, &top, &left);
	game_render_cursor(ctx, top, left);
	row = 0;
	while (row < game->h)
	{
		col = 0;
		while (col < game->w)
		{
			game_render_cell(game->grid[row][col],
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
	if (!ctx->game->pfirst)
	{
		ctx->game->pfirst = true;
		game_ai_move(ctx, &row, &col);
	}
}

static void	game_animate_drop(t_game_ctx *ctx, int col, int landing_row)
{
	int		top;
	int		left;
	char	piece;
	int		row;

	game_board_offsets(ctx, &top, &left);
	piece = ctx->game->grid[landing_row][col];
	ctx->game->grid[landing_row][col] = EMPTY;
	row = 0;
	while (row <= landing_row)
	{
		game_render(ctx);
		game_render_cell(piece, top + 1 + row * CELL_HEIGHT,
			left + 1 + col * CELL_WIDTH + (CELL_WIDTH - 1) / 2);
		refresh();
		game_render_cell(EMPTY, top + 1 + row * CELL_HEIGHT,
			left + 1 + col * CELL_WIDTH + (CELL_WIDTH - 1) / 2);
		napms(DROP_FRAME_MS);
		row++;
	}
	ctx->game->grid[landing_row][col] = piece;
}

static int	find_changed_col(t_game *game, int *before)
{
	int	col;

	col = 0;
	while (col < game->w)
	{
		if (get_height(game, col) != before[col])
			return (col);
		col++;
	}
	return (-1);
}

static void	game_ai_move(t_game_ctx *ctx, int *out_row, int *out_col)
{
	int	*before;
	int	j;

	before = malloc(sizeof(int) * ctx->game->w);
	if (!before)
	{
		make_ai_move(ctx->game, true);
		*out_row = -1;
		*out_col = -1;
		return ;
	}
	j = 0;
	while (j < ctx->game->w)
	{
		before[j] = get_height(ctx->game, j);
		j++;
	}
	make_ai_move(ctx->game, true);
	*out_col = find_changed_col(ctx->game, before);
	*out_row = before[*out_col];
	free(before);
	game_animate_drop(ctx, *out_col, *out_row);
}

static void	check_dir(t_game *game, int row, int col, int dr, int dc,
	char who, t_cell *out, int *count)
{
	row += dr;
	col += dc;
	while (*count < 4 && row >= 0 && row < game->h
		&& col >= 0 && col < game->w && game->grid[row][col] == who)
	{
		out[*count].row = row;
		out[*count].col = col;
		(*count)++;
		row += dr;
		col += dc;
	}
}

static bool	find_winning_line(t_game *game, int row, int col, t_cell *out)
{
	static const int	dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	char				player;
	int					axis;
	int					count;

	player = game->grid[row][col];
	axis = 0;
	while (axis < 4)
	{
		count = 1;
		out[0].row = row;
		out[0].col = col;
		check_dir(game, row, col, dirs[axis][0], dirs[axis][1],
			player, out, &count);
		check_dir(game, row, col, -dirs[axis][0], -dirs[axis][1],
			player, out, &count);
		if (count >= 4)
			return (true);
		axis++;
	}
	return (false);
}

static void	game_blink_winner(t_game_ctx *ctx, int row, int col)
{
	t_cell	cells[4];
	int		top;
	int		left;
	int		frame;
	int		i;
	int		color;

	if (!find_winning_line(ctx->game, row, col, cells))
		return ;
	game_board_offsets(ctx, &top, &left);
	frame = 0;
	while (frame < BLINK_FRAMES)
	{
		game_render(ctx);
		if (frame % 2 == 0)
			color = PAIR_GUI_HIGHLIGHT;
		else
			color = PAIR_CURSOR;
		i = 0;
		while (i < 4)
		{
			attron(COLOR_PAIR(color));
			mvaddch(top + 1 + cells[i].row * CELL_HEIGHT,
				left + 1 + cells[i].col * CELL_WIDTH + (CELL_WIDTH - 1) / 2,
				ctx->game->grid[cells[i].row][cells[i].col] == COMPUTER ? COMPUTER_CHAR : PLAYER_CHAR);
			attroff(COLOR_PAIR(color));
			i++;
		}
		refresh();
		napms(BLINK_FRAME_MS);
		frame++;
	}
}
