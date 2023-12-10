#include "minishell.h"
#include "libft.h"

/*
	1. lexer
	2. parser
	3. expand
	4. exec
*/
char	process_prompt(char	*prompt)
{
	char	**tokens;
	char	**cmds_table;

	tokens = lexer(prompt);
	cmds_table = parser(tokens);
	ft_doublefree(tokens);
	//expand(*cmds_table);
	ft_doublefree(cmds_table);
	return (0);
}
