#include "minishell.h"
#include "libft.h"

char	is_special_string(char *str)
{
	if (ft_strncmp(str, GREATGREAT, 2) == 0 \
		|| ft_strncmp(str, LESSLESS, 2) == 0 \
		|| ft_strncmp(str, OR, 2) == 0 \
		|| ft_strncmp(str, AND, 2) == 0)
		return (1);
	return (0);
}
