#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/* char	*in;
	char	heredoc;
	char	*out;
	char	append;
	char	*err;
	char	*exec;
	char	*opts;
	char	*args; */

static char	*get_line(int fd)
{
	char	*line;
	char	*read_c;
	char	*temp;

	read_c = ft_calloc(sizeof(char), 2);
	if (!read_c)
		printf("Error: Function 'read' failed\n"); // SALIDA ERROR
	line = NULL;
	while (read_c[0] != '\n')
	{
		if (read(fd, read_c, 1) < 0)
		{
			free(read_c);
			printf("Error: Function 'read_c' failed\n"); // SALIDA ERROR
		}
		read_c[1] = '\0';
		temp = ft_strdup(line);
		free(line);
		line = ft_strjoin(temp, read_c);
		free(temp);
	}
	free(read_c);
	return (line);
}

void	file_in(char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		printf("Error: Function 'open' failed\n"); // SALIDA ERROR
	if (dup2(fd, STDIN_FILENO) == -1)
		printf("Error: Function 'dup2' failed\n"); // SALIDA ERROR
	close(fd);
}

static void	here_doc(char *exit_name)
{
	int		fd;
	char	*line;

	fd = open(".new_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		printf("Error: Function 'open' failed\n"); // SALIDA ERROR
    printf("holaaaaa \n");
	while (1)
	{
		printf("pipe heredoc> ");
		line = get_line(0);
		if (ft_cmpsame(exit_name, line) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	file_in(".new_file.txt");
	close(fd);
	if (unlink(".new_file.txt") < 0)
		printf("Error: Function 'unlink' failed\n"); // SALIDA ERROR
}

static void select_file_in(t_cmd *cmd)
{
    printf("cmd->heredoc = %s\n", cmd->heredoc);
    if (cmd->heredoc)
        here_doc(cmd->heredoc);
}

void exec(t_cmd	**cmds)
{
    int	index;
    
    index = 0;
	while (cmds[index])
	{
		printf("EXEC cmds[%i]\n", index);
		printf("\tin  : %s\n", cmds[index]->in);
        //cmds[index]->heredoc = (NULL);
        cmds[index]->heredoc = "patata";
		printf("\theredoc : %s\n", cmds[index]->heredoc);
		printf("\tout : %s\n", cmds[index]->out);
		printf("\tappend : %i\n", cmds[index]->append);
		printf("\terr : %s\n", cmds[index]->err);
		printf("\texec: %s\n", cmds[index]->exec);
		printf("\topt : %s\n", cmds[index]->opts);
		printf("\targs: %s\n", cmds[index]->args);
		index++;
	}

    index = 0;
    while (cmds[index])
    {
        select_file_in(cmds[index]);
        index++;
    }


}