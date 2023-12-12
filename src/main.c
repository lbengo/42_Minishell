#include "minishell.h"
#include "libft.h"


/*
	1. read terminal
	2. lexer
	3. parser
	4. expander
	5. exec
*/
int	main(int argc, char const *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*prompt;
	char	**tokens;
	char	***cmds_table;

	while (1)
	{
		prompt = read_input();
		if (!prompt)
			continue;
		tokens = lexer(prompt);
		free(prompt);
		cmds_table = parser(tokens);
		ft_doublefree(tokens);
		expander(cmds_table);
		//exec();
		ft_triplefree(cmds_table);
	}
	return (0);
}
