/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:08:27 by jureix-c          #+#    #+#             */
/*   Updated: 2026/03/05 00:56:58 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "errft.h"
#include "libft.h"

t_error_el	*error_stack_find(t_error err)
{
	t_error_stack	*stack;
	uint32_t		i;

	stack = error_stack();
	if (!stack)
		return (NULL);
	i = 0;
	while (i < stack->cursor)
	{
		if (stack->stack[i].error == err)
			return (stack->stack + i);
		i++;
	}
	return (NULL);
}

t_error_stack	*error_stack_dup(void)
{
	t_error_stack	*stack;
	t_error_stack	*dup;

	stack = error_stack();
	if (!stack)
		return (NULL);
	if (error_stack_find(MEMORY_FAILURE))
		return (NULL);
	dup = malloc(sizeof(t_error_stack));
	if (!dup)
		return (NULL);
	return (ft_memcpy(dup, stack, sizeof(t_error_stack)));
}

void	clean_error_stack(void)
{
	ft_bzero(error_stack(), sizeof(t_error_stack));
}
