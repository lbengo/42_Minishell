#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*
This function make 2 things:
	1. Tokenize the given prompt
	2. Identifies keywords, identifiers, and operators
*/
char	**lexer(char *prompt)
{
	char	**tokens;

	tokens = ft_split(prompt, ' ');

	int i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i++]);
	}
	return (tokens);
}
