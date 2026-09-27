/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 21:36:45 by jureix-c          #+#    #+#             */
/*   Updated: 2026/03/04 21:36:46 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/nodes.h"
#include "ft_printf/utils.h"

void	init_double_node(va_list av, t_printf_node *node)
{
	printf_node_extract_flags(av, node);
	node->type = NODE_TYPE_DOUBLE;
	node->data.f = va_arg(av, double);
	if (node->precision == VALUE_UNSET)
		node->precision = 6;
}

int	get_double_node_len(t_printf_node *node)
{
	int	total;

	get_double_node_lens(node, NULL, &total);
	node->string_len = int_max(node->width, total);
	return (node->string_len);
}

static int	dump_double_lpad(t_printf_output *out, t_printf_node *node,
		int p_len, char s)
{
	if (node->flag_zero)
	{
		if (s != 0 && ft_printf_write(out, &s, 1) == FAILURE)
			return (FAILURE);
		if (ft_printf_pad(out, '0', p_len) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (ft_printf_pad(out, ' ', p_len) == FAILURE)
			return (FAILURE);
		if (s != 0 && ft_printf_write(out, &s, 1) == FAILURE)
			return (FAILURE);
	}
	return (0);
}

static int	dump_double_digits(t_printf_output *out, t_printf_node *node)
{
	uint64_t	i_part;
	uint64_t	f_part;
	int			i_len;

	get_double_parts(node, &i_part, &f_part);
	i_len = uint_strlen(i_part, 10);
	if (ft_printf_write_llu(out, i_part, i_len - 1) == FAILURE)
		return (FAILURE);
	if (node->precision > 0)
	{
		if (ft_printf_write(out, ".", 1) == FAILURE)
			return (FAILURE);
		if (ft_printf_write_llu(out, f_part, node->precision - 1) == FAILURE)
			return (FAILURE);
	}
	return (0);
}

int	dump_double_node(t_printf_output *out, t_printf_node *node)
{
	int		total_len;
	int		pad_len;
	char	sign;

	get_double_node_lens(node, NULL, &total_len);
	sign = get_double_sign(node);
	pad_len = 0;
	if (node->width > total_len)
		pad_len = node->width - total_len;
	if (!node->flag_minus)
	{
		if (dump_double_lpad(out, node, pad_len, sign) == FAILURE)
			return (FAILURE);
	}
	else if (sign != 0 && ft_printf_write(out, &sign, 1) == FAILURE)
		return (FAILURE);
	if (dump_double_digits(out, node) == FAILURE)
		return (FAILURE);
	if (node->flag_minus && ft_printf_pad(out, ' ', pad_len) == FAILURE)
		return (FAILURE);
	return (0);
}
