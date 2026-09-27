#include <stdlib.h>

#include "tui/renderer.h"

void	free_ui_element(t_ui_element *element)
{
	switch (element->type)
	{
		case UI_LABEL:
			free_ui_label(element);
			break ;
		case UI_BTN:
			free_ui_btn(element);
			break ;
	}
	free(element);
}
