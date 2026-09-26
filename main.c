/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:43:56 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/26 15:03:12 by bcondemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void *free_all(int **grid, int i);
int **create_grid(int line, int column);
int display_grid(int **grid, int line_nb, int column_nb);


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

	display_grid(grid, line_nb, column_nb);
	// printf("%d\n",ft_atoi(get_next_line(0)));

	free_all(grid, line_nb);
}

// TODO:
// choose the first to play randomly
// display the grid and the pawns
// give a number to each column, then wait for input of the player and make the pawn spawn

// the top th index is the bottom of the column
// the 0 index for lines is the left


int **create_grid(int line_nb, int column_nb)
{
	int i;
	int **lines;

	lines = malloc(sizeof(int *) * line_nb);
	if (lines == NULL)
		return (NULL);

	i = 0;
	while (i < line_nb)
	{
		lines[i] = ft_memset(malloc(sizeof(int) * column_nb), 0, column_nb);
		if (lines[i] == NULL)
			return (free_all(lines, i));
		i++;
	}
	return lines;
}

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

int display_grid(int **grid, int line_nb, int column_nb)
{
	int i = 0;
	int j = 0;
	char *pawns;

	while (j < line_nb)
	{
		i = 0;
		while (i < column_nb + 1)
		{
			ft_putstr_fd("|", 1);
			if (i == column_nb)
			{
				ft_putstr_fd("\n", 1);
				break ;
			}
			// ft_putstr_fd(pawns, 1);
			if (grid[j][i] == COMPUTER)
				pawns = " X ";
			else if (grid[j][i] == PLAYER)
				pawns = " O ";
			else
				pawns = "   ";
			ft_putstr_fd(pawns, 1);
			// here to put depending on the pawns master
			i++;
		}
		j++;
	}
	return 0;
}
