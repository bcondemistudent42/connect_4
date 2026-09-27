#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"

#include "connect4.h"
#include "constants.h"

int	get_player_move(t_game *game)
{
	int		column_index;
	char	*buf;

	while (true)
	{
		buf = get_next_line(0);
		if (!buf)
			return (-1);
		column_index = ft_atoi(buf);
		free(buf);
		if (make_player_move(game, column_index))
			ft_printf(INVALID_MOVE_ERR);
		else
			break ;
	}
	return (column_index);
}

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
