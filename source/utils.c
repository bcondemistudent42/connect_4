#include <stdbool.h>

#include "connect4.h"
#include "constants.h"

// PROTOTYPES
static bool	check_line(t_game *game, int row, int col, int ver_dir, int hor_dir);

int get_height(t_game *game, int column_index)
{
	int i = 0;

	while (i < game->h && game->grid[i][column_index] == EMPTY)
		i++;
	return (i - 1);
}

int	check_win(t_game *game)
{
	int		i, j;
	bool	draw;

	i = 0;
	while (i < game->h)
	{
		j = 0;
		while (j < game->w)
		{
			if (game->grid[i][j] != EMPTY
				&& (check_line(game, i, j, 0, 1)
					|| check_line(game, i, j, 1, 0)
					|| check_line(game, i, j, 1, 1)
					|| check_line(game, i, j, 1, -1)
					)
				)
				return (game->grid[i][j]);
			j++;
		}
		i++;
	}
	// Draw check
	draw = true;
	j = 0;
	while (j < game->w)
		if (get_height(game, j++) >= 0)
			draw = false;
	if (draw)
		return (-1);
	return (EMPTY);
}

// fewer cells = can afford to search deeper
int	get_ai_depth(t_game *game)
{
	int	depth;

	depth = MAX_AI_DEPTH - (game->w * game->h) / CELLS_PER_DEPTH;
	if (depth < MIN_AI_DEPTH)
		depth = MIN_AI_DEPTH;
	if (depth > MAX_AI_DEPTH)
		depth = MAX_AI_DEPTH;
	return (depth);
}

static bool	check_line(t_game *game, int row, int col, int ver_dir, int hor_dir)
{
	char	winner;
	int		i;

	winner = game->grid[row][col];
	i = 0;
	while (i < 4)
	{
		if (row < 0 || row >= game->h || col < 0 || col >= game->w)
			return (false);
		if (game->grid[row][col] != winner)
			return (false);
		row += ver_dir;
		col += hor_dir;
		i++;
	}
	return (true);
}
