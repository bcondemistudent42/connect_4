#include <stdlib.h>
#include "libft.h"

#include "tui/renderer.h"

t_ui_element	*init_ui_label(t_vec2 pos, char *str)
{
	t_ui_element	*label = ft_calloc(1, sizeof(t_ui_element));
	
	if (!label)
		return (NULL);
	label->label.str = ft_strdup(str);
	if (!label->label.str)
	{
		free(label);
		return (NULL);
	}
	label->type = UI_LABEL;
	label->should_update = true;
	label->pos = pos;
	label->prev_pos = pos;
	return (label);
}

int	render_ui_label(t_ui_element *label)
{
	attron(COLOR_PAIR(label->label.color));
	mvprintw(label->pos.y, label->pos.x, "%s", label->label.str);
	attroff(COLOR_PAIR(label->label.color));
	return (0);
}

void	free_ui_label(t_ui_element *btn)
{
	if (btn->btn.str)
		free(btn->btn.str);
}
