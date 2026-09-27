/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:43:56 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/27 07:44:39 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"

#include "connect4.h"
#include "constants.h"

int connect4(t_game *game)
{
	int		column_index;
	char	*buf;

	if (game->pfirst)
		ft_printf("You are the first to play, this time.\n");
	else
		make_ai_move(game);
	while (true)
	{
		display_grid(game);
		// Player move
		buf = get_next_line(0);
		if (!buf)
			return (1);
		column_index = ft_atoi(buf);
		free(buf);
		if (make_player_move(game, column_index))
			ft_printf(INVALID_MOVE_ERR);
		// AI move
		make_ai_move(game);
	}
}

int main(int argc, char **argv)
{
	t_game	*game;
	int		w, h;

	if (argc != 3)
		return (1);
	h = ft_atoi(argv[1]);
	w = ft_atoi(argv[2]);
	if (h < MIN_HEIGHT)
		ft_dprintf(STDERR_FILENO, HEIGHT_GAME_ERR, MIN_HEIGHT);
	if (w < MIN_WIDTH)
		ft_dprintf(STDERR_FILENO, WIDTH_GAME_ERR, MIN_WIDTH);
	if (h < MIN_HEIGHT || w < MIN_WIDTH)
		return (1);
	
	game = init_game(w, h);
	if (game == NULL)
	{
		ft_dprintf(STDERR_FILENO, INIT_GAME_ERR);
		return (1);
	}

	connect4(game);
	free_game(game);
	get_next_line_cleanup();
}
