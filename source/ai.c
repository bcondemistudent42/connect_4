#include <limits.h>
#include "ft_printf/ft_printf.h"

#include "connect4.h"
#include "constants.h"

// PROTOTYPES
static int	minimax(t_game *game, int depth, bool max);
static int	heuristic(t_game *game);
static int	near_win_heuristic(t_game *game, char player);
static int	process_line(t_game *game, int row, int col, int ver_dir, int hor_dir);
static int	center_bonus(t_game *game, int col);

int	make_ai_move(t_game *game)
{
	int	col;
	int	row;
	int	score;
	int	best_score;
	int	best_col;

	col = 0;
	best_score = INT_MIN;
	best_col = -1;
	while (col < game->w)
	{
		row = get_height(game, col);
		score = 0;
		if (row >= 0)
		{
			game->grid[row][col] = COMPUTER;
			score = minimax(game, AI_DEPTH - 1, false);
			game->grid[row][col] = EMPTY;
			if (score > best_score)
			{
				best_score = score;
				best_col = col;
			}
		}
#ifdef DEBUG
		ft_printf("| %d ", score);
#endif
		col++;
	}
	if (best_col == -1)
		return (1);
	row = get_height(game, best_col);
	game->grid[row][best_col] = COMPUTER;
	return (0);
}

static int	minimax(t_game *game, int depth, bool max)
{
	int	col;
	int	row;
	int	score;
	int	best;
	int	winner;

	// Chcek win, heuristic if hit max depth
	winner = check_win(game);
	if (winner == COMPUTER)
		return (WIN_BONUS);
	if (winner == PLAYER)
		return (-WIN_BONUS);
	if (depth == 0)
		return (heuristic(game));
	// Max = computer turn
	col = 0;
	if (max)
		best = INT_MIN;
	else
		best = INT_MAX;
	// Evaluate each move
	while (col < game->w)
	{
		row = get_height(game, col);
		if (row >= 0)
		{
			if (max)
				game->grid[row][col] = COMPUTER;
			else
				game->grid[row][col] = PLAYER;
			score = minimax(game, depth - 1, !max);
			game->grid[row][col] = EMPTY;
			if (max && score > best)
				best = score;
			if (!max && score < best)
				best = score;
		}
		col++;
	}
	return (best);
}

static int	heuristic(t_game *game)
{
	int	i;
	int	j;
	int	score;

	i = 0;
	score = 0;
	while (i < game->h)
	{
		j = 0;
		while (j < game->w)
		{
			if (game->grid[i][j] == COMPUTER)
				score += center_bonus(game, j);
			else if (game->grid[i][j] == PLAYER)
				score -= center_bonus(game, j);
			j++;
		}
		i++;
	}
	score += near_win_heuristic(game, COMPUTER);
	score -= near_win_heuristic(game, PLAYER);
	return (score);
}

// Near win/lose scoring
static int	near_win_heuristic(t_game *game, char player)
{
	int i, j;
	int	score;

	score = 0;
	i = 0;
	while (i < game->h)
	{
		j = 0;
		while (j < game->w)
		{
			if (game->grid[i][j] == player)
			{
				score += process_line(game, i, j, 1, 0)
					+ process_line(game, i, j, 0, 1)
					+ process_line(game, i, j, 1, 1)
					+ process_line(game, i, j, 1, -1);
			}
			j++;
		}
		i++;
	}
	return (score);
}

static int	process_line(t_game *game, int row, int col, int ver_dir, int hor_dir)
{
	char	player;
	int		i;
	int		score;

	player = game->grid[row][col];
	row += ver_dir * 3;
	col += hor_dir * 3;
	i = 0;
	score = 100;
	while (i < 4)
	{
		if (row < 0 || row >= game->h || col < 0 || col >= game->w)
			return (0);
		if (game->grid[row][col] != player && game->grid[row][col] != EMPTY)
			return (0);
		if (game->grid[row][col] == EMPTY)
			score /= 10;
		row -= ver_dir;
		col -= hor_dir;
		i++;
	}
	return (score);
}

// Bonus the more it's horizontally centered, starting from 4 away each side
static int	center_bonus(t_game *game, int col)
{
	int	dist = col;
	if (game->w - 1 - col < dist)
		dist = game->w - 1 - col;
	if (dist < 3)
		return (0);
	return (CENTER_BONUS * (dist - 2));
}
