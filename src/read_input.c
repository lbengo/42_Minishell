#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	end(void)
{
	printf("exit\n");
	exit (0);
}

char	*read_input(void)
{
	char	*prompt;

	prompt = (char *) NULL;
	if (prompt)
	{
		free (prompt);
		prompt = (char *) NULL;
	}
	prompt = readline("minishell> ");
	if (!prompt)
		end();
	if (!prompt[0])
		return (NULL);
	add_history (prompt);
	if (ft_strcmp(prompt, "exit") == 0)
	{
		free(prompt);
		end();
	}
	return (prompt);
}
