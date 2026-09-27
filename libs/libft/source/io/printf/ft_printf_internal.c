/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:01:58 by jureix-c          #+#    #+#             */
/*   Updated: 2025/10/07 21:28:23 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"

int	_ft_printf_internal(t_printf_data *data, va_list argv)
{
	int	write_count;

	data->output.error = PRINTF_OUTPUT_ERROR_NONE;
	data->nodes = NULL;
	write_count = lex_nodes(data, argv);
	if (write_count == 0)
		write_count = dump_nodes(data);
	if (data->output.mode == PRINTF_OUTPUT_BUFFER && data->output.buffer
		&& data->output.cursor < data->output.size)
		data->output.buffer[data->output.cursor] = '\0';
	if (data->output.mode == PRINTF_OUTPUT_BUFFERED_FD && data->output.buffer)
		free(data->output.buffer);
	printf_nodes_clean(data->nodes);
	if (data->output.error == PRINTF_OUTPUT_ERROR_IO)
		return (FAILURE);
	return (write_count);
}
