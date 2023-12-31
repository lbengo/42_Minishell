#include "minishell.h"
#include "libft.h"

// TODO delete includes
#include <stdio.h>

static size_t	count_tokens(char *str)
{
	size_t			tokens;
	char			is_delimiter;
	unsigned int	i;

	tokens = 0;
	is_delimiter = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == SPACE || str[i] == TAB)
			is_delimiter = 1;
		else if (is_special_string(&str[i]))
		{
			tokens += 1;
			is_delimiter = 1;
			i++;
		}
		else if (is_special_char(str[i]))
		{
			tokens += 1;
			is_delimiter = 1;
		}
		else
		{
			tokens += is_delimiter;
			is_delimiter = 0;
		}
		i++;
	}
	if (!tokens && is_delimiter)
		return (0);
	if (!tokens)
		return (1);
	return (tokens);
}

static char	**get_tokens( \
			char **save_place, char *str, size_t tokens)
{
	size_t	saved_tokens;
	size_t	str_len;
	size_t	count;

	saved_tokens = 0;
	str_len = 0;
	count = 0;
	while (saved_tokens < tokens)
	{
		if (is_special_string(str + count))
		{
			if (str_len != 0)
				save_place[saved_tokens++] = \
					ft_substr(str, count - str_len, str_len);
			str_len = 0;
			save_place[saved_tokens++] = ft_strdup(\
				(char [3]){str[count], str[count + 1], '\0'});
			count++;
		}
		else if (is_special_char(str[count]))
		{
			if (str_len != 0)
				save_place[saved_tokens++] = \
					ft_substr(str, count - str_len, str_len);
			str_len = 0;
			save_place[saved_tokens++] = ft_strdup(\
				(char [2]){str[count], '\0'});
		}
		else if (str[count] == SPACE || str[count] == TAB \
		|| count >= ft_strlen(str))
		{
			if (str_len != 0)
				save_place[saved_tokens++] = \
					ft_substr(str, count - str_len, str_len);
			str_len = 0;
		}
		else
			str_len++;
		count++;
	}
	return (save_place);
}

/*
This function make 2 things:
	1. Tokenize the given prompt
	2. Identifies keywords, identifiers, and operators

RETURN:
	FAIL -> NULL
	SUCCESS -> An array of identified tokens
*/
char	**lexer(char *prompt)
{
	unsigned int	token_nbr;
	char			**tokens;

	if (!prompt)
		return (NULL);
	token_nbr = count_tokens(prompt);
	printf("LEXER tokens counter: %zu\n", count_tokens(prompt));

	tokens = ft_calloc(token_nbr + 1, sizeof(*tokens));
	if (!tokens)
		return (NULL);
	get_tokens(tokens, prompt, token_nbr);
	int	i = 0;
	while (tokens[i])
	{
		printf("LEXER token[%d]: %s\n", i, tokens[i]);
		i++;
	}
	return (tokens);
}
