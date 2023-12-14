#include "minishell.h"
#include "libft.h"

char	add_opt(char **cmd_opts, char *new_opt)
{
	char	*temp_str;

	if (!*cmd_opts)
		*cmd_opts = ft_strdup(new_opt);
	else
	{
		temp_str = ft_strdup(*cmd_opts);
		free(*cmd_opts);
		*cmd_opts = ft_strjoin(temp_str, ++new_opt);
		free(temp_str);
	}
	return (0);
}
