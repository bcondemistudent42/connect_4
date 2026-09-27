#include "connect4.h"

int	make_player_move(t_game *game, int column_index)
{
	int	height;

	if (column_index >= game->w)
		return (1);
	height = get_height(game, column_index);
	if (height < 0)
		return (1);
	game->grid[height][column_index] = PLAYER;
	return (0);
}
