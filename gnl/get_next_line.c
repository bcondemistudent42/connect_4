/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcondemi <bcondemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:30:20 by bcondemi          #+#    #+#             */
/*   Updated: 2026/09/26 14:27:35 by bcondemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*get_next_line(int fd)
{
	char			*output_line;
	static char		stock[BUFFER_SIZE + 1];
	long			temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	output_line = malloc(1);
	if (!output_line)
		return (NULL);
	output_line[0] = 0;
	output_line = ft_strjoin(output_line, stock);
	if (!output_line)
		return (NULL);
	stock[0] = '\0';
	output_line = ft_fill_line(fd, output_line, stock);
	if (!output_line)
		return (NULL);
	temp = ft_get_index(output_line);
	if (temp != -1)
		ft_copy_short(output_line, stock, temp);
	output_line = ft_strjoin(output_line, "");
	if (!output_line)
		return (NULL);
	return ((char *)ft_check_null(output_line));
}

void	*ft_check_null(char *str)
{
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}
