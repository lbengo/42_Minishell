#include "libft.h"

char	is_heredoc(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	return (0);
}
