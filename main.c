/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:43:56 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/26 21:15:26 by bcondemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int make_player_move(int **grid, int line_nb, int column_nb, int player_index);
int get_height(int **grid, int column_index, int line_nb);

void *free_all(int **grid, int i)
{
	int k;

	k = 0;
	while (k < i){
		free(grid[k]);
		k++;
	}
	free(grid);
	return NULL;
}

int **create_grid(int line_nb, int column_nb)
{
	int i;
	int **columns;
	int *line;

	columns = malloc(sizeof(int *) * (column_nb));
	if (columns == NULL)
		return (NULL);

	i = 0;
	while (i < column_nb)
	{
		columns[i] = ft_memset(malloc(sizeof(int) * line_nb), 0, line_nb);
		if (columns[i] == NULL)
			return (free_all(columns, i));
		i++;
	}
	return columns;
}

int display_grid(int **grid, int line_nb, int column_nb)
{
	int i = 0;
	int j = 0;
	char *pawns;

	ft_putstr_fd("\n", 1);
	pawns = "   ";
	while (i < line_nb)
	{
		j = 0;
		while (j < column_nb)
		{
			ft_putstr_fd("|", 1);
			if (j == column_nb - 1)
			{
				if (grid[j][i] == PLAYER)
					pawns = " O ";
				else if (grid[j][i] == COMPUTER)
					pawns = " X ";
				else
					pawns = "   ";
				ft_putstr_fd(pawns, 1);
				ft_putstr_fd("|", 1);
				ft_putstr_fd("\n", 1);
				break;
			}
			pawns = "   ";
			if (grid[j][i] == PLAYER)
				pawns = " O ";
			else if (grid[j][i] == COMPUTER)
				pawns = " X ";
			ft_putstr_fd(pawns, 1);
			j++;
		}
		i++;
	}

	i = 0;
	ft_putstr_fd(" ", 1);
	while (i < column_nb)
	{
		ft_putstr_fd("‾‾‾‾", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);

	i = 0;
	while (i < column_nb)
	{
		ft_putstr_fd("  ", 1);
		ft_putstr_fd(ft_itoa(i), 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n", 1);

	return 0;
}


int launch_game(int **grid, int line_nb, int column_nb)
{
	int column_index;

	// to make correctly with nice condition
	while (1 == 1)
	{
		column_index = ft_atoi(get_next_line(0));
		if (make_player_move(grid, line_nb, column_nb, column_index) != 1);
		else
			return (1);
		display_grid(grid, line_nb, column_nb);
		// TODO choose if : depend on the first random
		// make bot play
		// make the player play
	}
}

int make_player_move(int **grid, int line_nb, int column_nb, int column_index)
{

	int height;

	height = get_height(grid, column_index, line_nb);

	if (height < 0)
		return (1);

	grid[column_index][height] = PLAYER;
	return (0);
}

int get_height(int **grid, int column_index, int line_nb)
{
	int i = 0;

	while (i < line_nb && grid[column_index][i] == 0)
		i++;
	return i - 1;
}

int main(int argc, char **argv)
{

	int line_nb;
	int column_nb;
	int **grid;

	if (argc != 3)
		return (1);
	line_nb = ft_atoi(argv[1]);
	column_nb = ft_atoi(argv[2]);
	if (line_nb < 6 || column_nb < 7)
		return (1);
	
	grid = create_grid(line_nb, column_nb);
	if (grid == NULL)
		return (1);

	launch_game(grid, line_nb, column_nb);

	free_all(grid, line_nb);
}