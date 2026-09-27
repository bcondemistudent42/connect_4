/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 10:07:39 by jureix-c          #+#    #+#             */
/*   Updated: 2026/09/27 10:09:11 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "connect4.h"
#include "constants.h"

// PROTOTYPES
static bool	check_line(t_game *game, int row, int col, int ver_dir, int hor_dir);
static int	count_dir(t_game *game, int row, int col, int ver_dir, int hor_dir);

bool	is_board_full(t_game *game)
{
	int	j;

	j = 0;
	while (j < game->w)
	{
		if (game->grid[0][j] == EMPTY)
			return (false);
		j++;
	}
	return (true);
}

// Check only last move, 8 dirs
bool	check_win_optimized(t_game *game, int row, int col)
{
	if (1 + count_dir(game, row, col, 0, 1) + count_dir(game, row, col, 0, -1) >= 4)
		return (true);
	if (1 + count_dir(game, row, col, 1, 0) + count_dir(game, row, col, -1, 0) >= 4)
		return (true);
	if (1 + count_dir(game, row, col, 1, 1) + count_dir(game, row, col, -1, -1) >= 4)
		return (true);
	if (1 + count_dir(game, row, col, 1, -1) + count_dir(game, row, col, -1, 1) >= 4)
		return (true);
	return (false);
}

int get_height(t_game *game, int column_index)
{
	int i = 0;

	while (i < game->h && game->grid[i][column_index] == EMPTY)
		i++;
	return (i - 1);
}

int	check_win(t_game *game)
{
	int	i;
	int	j;

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
	if (is_board_full(game))
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

// Count matching cells in dir
static int	count_dir(t_game *game, int row, int col, int ver_dir, int hor_dir)
{
	char	player;
	int		count;

	player = game->grid[row][col];
	count = 0;
	row += ver_dir;
	col += hor_dir;
	while (row >= 0 && row < game->h
			&& col >= 0 && col < game->w
			&& game->grid[row][col] == player)
	{
		count++;
		row += ver_dir;
		col += hor_dir;
	}
	return (count);
}
