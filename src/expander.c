#include "minishell.h"
#include "libft.h"

// TODO delete includes
#include <stdio.h>

/*
TODO:
$?
$PWD-??
$?-?
*/
static char	expand_dollar(char **str, int dollar_pos)
{
	char			**split;
	unsigned int	dollars;
	char			*expanded;
	char			*prefix;

	dollars = 0;
	split = ft_split(*str, DOLLAR);
	free(*str);
	if (!dollar_pos)
	{
		ft_find_char(split[dollars], QUESTION_MARK);
		expanded = getenv(split[dollars]);
		if (expanded)
			*str = ft_strdup(expanded);
		dollars++;
	}
	else
		*str = ft_strdup(split[dollars++]);
	while (split[dollars])
	{
		expanded = getenv(split[dollars++]);
		if (!expanded)
			continue;
		prefix = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(prefix, expanded);
		free(prefix);
	}
	return (0);
}

char	expander(char ***parser_table)
{
	int	row;
	int	column;
	int	dollar_pos;

	row = 0;
	column = 0;
	while (parser_table[row])
	{
		while (parser_table[row][column])
		{
			printf("EXPANDER parser_table[%i][%i]: %s\n", row, column, parser_table[row][column]);
			dollar_pos = ft_find_char(parser_table[row][column], DOLLAR);
			if (dollar_pos >= 0)
			{
				expand_dollar(&parser_table[row][column], dollar_pos);
				printf("\tDollar expanded = %s\n", parser_table[row][column]);
			}
			column++;
		}
		column = 0;
		row++;
	}
	return (0);
}
