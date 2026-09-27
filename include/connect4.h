/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect4.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 12:18:10 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/27 09:36:55 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONNECT4_H
# define CONNECT4_H

// INCLUDES
#include <stdbool.h>

// ENUMS
enum OWNER {
	EMPTY = 0,
	COMPUTER = 1,
	PLAYER = 2,
}; 

// STRUCTS
typedef struct s_game {
	bool	display_mode;
	// Board
	int		w, h;
	char	**grid;
	// AI
	int		ai_depth;
	// Other
	bool	pfirst;
}	t_game;

// PROTOTYPES
// Game
int		connect4(t_game *game);
t_game	*init_game(int w, int h);
void	free_game(t_game *game);

// Player
int		get_player_move(t_game *game);
int		make_player_move(t_game *game, int column_index);

// AI
int		make_ai_move(t_game *game);

// Display
int		display_grid(t_game *game);

// Utils
int		get_height(t_game *game, int column_index);
int		check_win(t_game *game);
int		get_ai_depth(t_game *game);

#endif
