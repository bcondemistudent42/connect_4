/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 18:06:02 by jureix-c          #+#    #+#             */
/*   Updated: 2025/09/28 19:44:18 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_string_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
