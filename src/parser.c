#include "minishell.h"
#include "libft.h"

// TODO delete includes
#include <stdio.h>

/*
NOTE: Rows counter start from 1.
*/
static unsigned int	get_table_rows(char **tokens)
{
	unsigned int	tokens_len;
	unsigned int	rows;

	rows = 1;
	tokens_len = 0;
	while (tokens[tokens_len])
	{
		if (tokens[tokens_len][0] == PIPE && tokens_len != 0)
			rows++;
		tokens_len++;
	}
	return (rows);
}

/* Get the row's token number until next pipe */
static unsigned int	get_rows_column(unsigned int actual_row, char **tokens)
{
	unsigned int	row;
	unsigned int	token_nbr;

	token_nbr = 0;
	while (tokens[token_nbr])
	{
		if (tokens[token_nbr][0] == PIPE)
			break;
		token_nbr++;
	}
	return (token_nbr);
}

static char	fill_table_cmds(char ***table, char **tokens, unsigned int tot_rows)
{
	unsigned int	row;
	unsigned int	column;
	unsigned int	token;

	row = 0;
	column = 0;
	token = 0;
	table[row] = ft_calloc(get_rows_column(row, &tokens[token]) + 1, sizeof(*table));
	while(tokens[token])
	{
		if (row >= tot_rows)
			return (1, printf("PARSER ERROR: Commands table rows exceeded.\n"));
		if (tokens[token][0] == PIPE)
		{
			token++;
			if (column != 0)
			{
				table[row][column] = NULL;
				row++;
				table[row] = ft_calloc(get_rows_column(row, &tokens[token]) + 1, sizeof(*table));
				column = 0;
			}
		}
		table[row][column] = ft_strdup(tokens[token]);
		token++;
		column++;
	}
	return (0);
}

/*
Take the tokens from lexer and return a structured table.

Return example:
+-------------+-------------+--------------+-------+-------+
| cmd_1       | -options    | arg_1        | arg_2 | NULL  |
+-------------+-------------+--------------+-------+-------+-------+
| cmd_2       | arg_1       | arg_2        | ...   | arg_n | NULL  |
+-------------+-------------+--------------+-------+-------+-------+
| cmd_n       | -options    | NULL         |
+-------------+-------------+--------------+-------+
| In: default | Out: file_1 | Err: default | NULL  |
+-------------+-------------+--------------+-------+
| NULL        |
+-------------+

TODO: Cases to define
 - If in the middle of pipeline is a redirection?? -> ls >file1 | grep o
 - where go "&&" on the table
*/
char	***parser(char **tokens)
{
	char			***table;
	unsigned int	rows;

	rows = get_table_rows(tokens);
	printf("PARSER cmds_table rows: %u\n", rows);
	table = ft_calloc(rows + 2, sizeof(*table));
	if (!table)
		return (NULL);
	fill_table_cmds(table, tokens, rows);
	//fill_table_io(table, tokens, rows);
	int	row = 0;
	int	column = 0;
	while (table[row])
	{
		while (table[row][column])
		{
			printf("PARSER table[%i][%i]: %s\n", row, column, table[row][column]);
			column++;
		}
		column = 0;
		row++;
	}
	return (table);
}
