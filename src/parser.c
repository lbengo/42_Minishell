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
	unsigned int	index;

	pipes = 0;
	tokens_len = 0;
	while (tokens[tokens_len])
	{
		if (tokens[tokens_len][0] == PIPE)
			pipes++;
		tokens_len++;
	}
	cmds_table = malloc((pipes + 1) * sizeof(*cmds_table));
	if (!cmds_table)
		return (NULL);
	index = 0;
	cmds_table[index] = ft_strdup(tokens[tokens_len]);
	while(index <= pipes)
	{
		while(tokens_len)
		{
			if (tokens[tokens_len][0] == PIPE)
				break;
			cmds_table[index] = ft_strjoin(cmds_table[index], tokens[tokens_len]);
			tokens_len--;
		}
		index++;
	}
	return (cmds_table);
}
