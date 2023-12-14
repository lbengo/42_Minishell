#include "minishell.h"
#include "libft.h"

char	add_io(t_cmd **cmd, char *new_io, char *io_opt)
{
	if (ft_strncmp(new_io, ">2", 2) == 0)
		(*cmd)->err = ft_strdup(new_io);
	else if (io_opt[0] == LESS)
	{
		if ((*cmd)->in)
		{
			(*cmd)->heredoc = 0;
			free((*cmd)->in);
		}
		if (is_heredoc(io_opt))
			(*cmd)->heredoc = 1;
		(*cmd)->in = ft_strdup(new_io);
	}
	else if (io_opt[0] == GREAT)
	{
		if ((*cmd)->out)
		{
			(*cmd)->append = 0;
			free((*cmd)->out);
		}
		if (is_append(io_opt))
			(*cmd)->append = 1;
		(*cmd)->out = ft_strdup(new_io);
	}
	else
		return (ft_putstr_fd("ERROR: Can not detect I/O file.\n", 2), 1);
	return (0);
}
