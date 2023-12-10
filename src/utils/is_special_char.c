#include "minishell.h"

char	is_special_char(char c)
{
	if (c == SINGLE_QUOTE \
	|| c == DOUBLE_QUOTE \
	|| c == GREAT \
	|| c == LESS \
	|| c == PIPE \
	|| c == OPEN_BRACKET \
	|| c == CLOSE_BRACKET)
		return (1);
	return (0);
}
