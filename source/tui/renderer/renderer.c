#include "tui/renderer.h"

int	render_ui(t_ui_element **elements)
{
	for (int i = 0; elements[i]; i++)
	{
		if (!elements[i]->should_update)
			continue ;
		switch (elements[i]->type)
		{
			case UI_LABEL:
				render_ui_label(elements[i]);
				break ;
			case UI_BTN:
				render_ui_btn(elements[i]);
				break ;
		}
		elements[i]->should_update = false;
	}
	return (0);
}
