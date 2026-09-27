#include "libft.h"

#include "connect4.h"
#include "constants.h"

int	connect4_selfplay(t_game *game)
{
	int	i;
	int	g;

	g = 0;
	while (g < SELFPLAY_GAMES_COUNT)
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
		g++;
	}
	return (0);
}
