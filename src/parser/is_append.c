#include "libft.h"

char	is_append(char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		return (1);
	return (0);
}
