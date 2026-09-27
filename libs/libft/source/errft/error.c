/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jureix-c <jureix-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:52:30 by jureix-c          #+#    #+#             */
/*   Updated: 2026/03/05 00:55:05 by jureix-c         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "errft.h"

t_error	ret(t_error current, char *fl, int ln)
{
	return (reto(current, fl, ln, NULL));
}

t_error	reto(t_error current, char *fl, int ln, void *optional)
{
	t_error_el	*el;

	el = error_stack_get_next_slot();
	if (!el)
		return (current);
	el->error = current;
	el->file = fl;
	el->line_number = ln;
	el->optional = optional;
	return (current);
}
