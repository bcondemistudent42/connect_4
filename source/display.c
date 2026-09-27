#include "ft_printf/ft_printf.h"

#include "connect4.h"
#include "constants.h"

int display_grid(t_game *game)
{
	int i = 0;
	int j = 0;

	while (i < game->h)
	{
		j = 0;
		ft_printf("\n|");
		while (j < game->w)
		{
			if (game->grid[i][j] == PLAYER)
				ft_printf(" \033[33m%c\033[0m ", PLAYER_CHAR);
			else if (game->grid[i][j] == COMPUTER)
				ft_printf(" \033[31m%c\033[0m ", COMPUTER_CHAR);
			else
				ft_printf("   ");
			ft_printf("|");
			j++;
		}
		i++;
	}

	ft_printf("\n");
	i = 0;
	while (i < game->w)
	{
		ft_printf("‾‾‾‾");
		i++;
	}

	ft_printf("\n");
	i = 0;
	while (i < game->w)
	{
		ft_printf("%3d ", i);
		i++;
	}
	ft_printf("\n\n", 1);

	return (0);
}
