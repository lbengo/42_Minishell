#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static char	end(void)
{
	printf("exit\n");
	exit (0);
}

int	main(int argc, char const *argv[], char *envp[])
{
	char	*prompt;

	prompt = (char *) NULL;
	while (1)
	{
		if (prompt)
		{
			free (prompt);
			prompt = (char *) NULL;
		}
		prompt = readline("minishell> ");
		if (!prompt)
			end();
		if (!prompt[0])
			continue ;
		add_history (prompt);
		// if (strcmp(prompt, "clear") == 0)
		// 	rl_clear_history();
		if (strcmp(prompt, "exit") == 0)
		{
			free(prompt);
			end();
		}
		process_prompt(prompt);
	}
	return (0);
}
