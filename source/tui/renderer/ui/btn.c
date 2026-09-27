#include <ncurses.h>
#include <stdlib.h>
#include "libft.h"

#include "tui/renderer.h"

t_ui_element	*init_ui_btn(t_vec2 pos, char *str, t_vec2 size)
{
	t_ui_element	*btn = ft_calloc(1, sizeof(t_ui_element));
	
	if (!btn)
		return (NULL);
	btn->btn.str = ft_strdup(str);
	if (!btn->btn.str)
	{
		free(btn);
		return (NULL);
	}
	btn->type = UI_BTN;
	btn->should_update = true;
	btn->pos = pos;
	btn->prev_pos = pos;
	btn->btn.size = size;
	return (btn);
}

int	render_ui_btn(t_ui_element *btn)
{
	attron(COLOR_PAIR(PAIR_GUI));
	mvprintw(btn->pos.y, btn->pos.x, "%s", btn->btn.str);
	attroff(COLOR_PAIR(PAIR_GUI));
	return (0);
}

void	free_ui_btn(t_ui_element *btn)
{
	if (btn->btn.str)
		free(btn->btn.str);
}
