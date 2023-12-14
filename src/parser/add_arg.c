#include "minishell.h"
#include "libft.h"

char	add_arg(char **cmd_args, char *new_arg)
{
	char	*temp_str;
	char	*temp_space;

	if (!*cmd_args)
		*cmd_args = ft_strdup(new_arg);
	else
	{
		temp_str = ft_strdup(*cmd_args);
		free(*cmd_args);
		temp_space = ft_strjoin(temp_str, " ");
		free(temp_str);
		*cmd_args = ft_strjoin(temp_space, new_arg);
		free(temp_space);
	}
	return (0);
}
