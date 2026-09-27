#include "connect4.h"

int get_height(t_game *game, int column_index)
{
	int i = 0;

	while (i < game->h && game->grid[i][column_index] == EMPTY)
		i++;
	return (i - 1);
}
