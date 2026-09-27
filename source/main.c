/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 10:43:56 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/27 10:45:07 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"

#include "connect4.h"
#include "constants.h"

int connect4(t_game *game)
{
	int		winner;

	if (game->pfirst)
		ft_printf(FIRST_TO_PLAY_LITERAL);
	else
		make_ai_move(game, true);
	while (true)
	{
		display_grid(game);
		// Player move
		if (get_player_move(game) == -1)
			return (1);
		// AI move if not won
		winner = check_win(game);
		if (winner == EMPTY)
		{
			make_ai_move(game, true);
			// Win check
			winner = check_win(game);
		}
		if (winner != EMPTY)
			break ;
	}
	display_grid(game);
	if (winner == PLAYER)
		ft_printf(WIN_LITERAL);
	else if (winner == COMPUTER)
		ft_printf(LOSE_LITERAL);
	else
		ft_printf(DRAW_LITERAL);
	return (0);
}

int main(int argc, char **argv)
{
	t_game	*game;
	int		w, h;

	if (argc != 3 && argc != 4)
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

	if (argc == 4 && ft_strcmp(argv[3], "selfplay") == 0)
		connect4_selfplay(game);
	else if (argc == 4 && ft_strcmp(argv[3], "tui") == 0)
	{
		game->display_mode = true;
		connect4_tui(game);
	}
	else
		connect4(game);
	free_game(game);
	get_next_line_cleanup();
}
