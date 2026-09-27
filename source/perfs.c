#include "libft.h"

#include "connect4.h"

int	connect4_selfplay(t_game *game)
{
	int	i;

	while (true)
	{
		while (check_win(game) == EMPTY)
		{
			make_ai_move(game, true);
			if (check_win(game) == EMPTY)
				make_ai_move(game, false);
		}
		i = 0;
		while (i < game->h)
			ft_bzero(game->grid[i++], game->w);
	}
	return (0);
}
