#include "minishell.h"
#include "libft.h"

/*
Take the tokens from lexer and return a structured table.

Return example:
+-------------+-------------+--------------+-------+-------+
| cmd_1       | -options    | arg_1        | arg_2 |       |
+-------------+-------------+--------------+-------+-------+
| cmd_2       | arg_1       | arg_2        | ...   | arg_n |
+-------------+-------------+--------------+-------+-------+
| cmd_n       | -options    |              |       |       |
+-------------+-------------+--------------+-------+-------+
| In: default | Out: file_1 | Err: default |       |       |
+-------------+-------------+--------------+-------+-------+
*/
char	**parser(char	**tokens)
{
	char			**cmds_table;
	unsigned int	tokens_len;
	unsigned int	pipes;

	pipes = 0;
	tokens_len = 0;
	while (tokens[tokens_len])
	{
		if (tokens[tokens_len] == PIPE)
			pipes++;
		tokens_len++;
	}
	cmds_table = malloc((pipes + 1) * sizeof(*cmds_table));
	if (!cmds_table)
		return (NULL);
	while(pipes)
	{
		while(tokens_len)
		{
			if (tokens[tokens_len][0] == PIPE)
				break;
			cmds_table = ft_strjoin(cmds_table, tokens[tokens_len]);
			tokens_len--
		}
		pipes--;
	}
	return (cmds_table);
}
