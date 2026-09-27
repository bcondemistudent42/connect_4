#include <stdlib.h>
#include <time.h>
#include "libft.h"

#include "connect4.h"

t_game	*init_game(int w, int h)
{
	t_game	*game;
	int		i;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->w = w;
	game->h = h;
	game->grid = ft_calloc(h, sizeof(char *));
	if (!game->grid)
	{
		free_game(game);
		return (NULL);
	}
	i = 0;
	while (i < h)
	{
		game->grid[i] = ft_calloc(w, sizeof(char));
		if (game->grid[i] == NULL)
		{
			free_game(game);
			return (NULL);
		}
		i++;
	}
	srand(time(NULL));
	game->pfirst = rand() % 2;
	return (game);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->grid)
	{
		int	i = 0;
		while (i < game->h && game->grid[i])
			free(game->grid[i++]);
		free(game->grid);
	}
	free(game);
}
