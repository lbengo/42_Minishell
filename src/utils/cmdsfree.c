#include "minishell.h"
#include <stdlib.h>

void	cmdsfree(t_cmd **cmds)
{
	unsigned int	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
}
