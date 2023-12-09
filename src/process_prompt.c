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
	char	**cmds;

	tokens = lexer(prompt);
	//cmds = parser(tokens);
	//expand(*cmds);
	ft_doublefree(tokens);
	return (0);
}
