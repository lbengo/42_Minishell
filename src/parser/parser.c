#include "minishell.h"
#include "parser.h"
#include "libft.h"

// TODO delete includes
#include <stdio.h>

/*
NOTE: Rows counter start from 1.
*/
static unsigned int	count_total_cmds(char **tokens)
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

static char	is_io(char *token)
{
	if (token[0] == GREAT || token[0] == LESS)
		return (1);
	return (0);
}

/*
The function does not take into account options with double '-'.
For example "--help". These go to the arguments section.
*/
static char	is_option(char *token)
{
	if (token[0] == '-' && token[1] && token[1] != '-')
		return (1);
	return (0);
}

static t_cmd	*get_cmd(char **tokens, unsigned int *actual_token)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	while (tokens[*actual_token] && tokens[*actual_token][0] != PIPE)
	{
		if (is_io(tokens[*actual_token]))
		{
			(*actual_token)++;
			if (!tokens[*actual_token])
				return (ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2), NULL);
			if (is_io(tokens[*actual_token]))
				return (ft_putstr_fd("minishell: syntax error near unexpected token\n", 2), NULL);
			if (tokens[*actual_token][0] == PIPE)
				return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), NULL);
			add_io(&cmd, tokens[*actual_token], tokens[*actual_token - 1]);
			printf("PARSER cmd io: %s\n", tokens[*actual_token]);
		}
		else if (!cmd->exec && !cmd->opts && !cmd->args)
		{
			cmd->exec = ft_strdup(tokens[*actual_token]);
			printf("PARSER cmd exec: %s\n", tokens[*actual_token]);
		}
		else if (is_option(tokens[*actual_token]))
		{
			add_opt(&cmd->opts, tokens[*actual_token]);
			printf("PARSER cmd opt: %s\n", tokens[*actual_token]);
		}
		else
		{
			add_arg(&cmd->args, tokens[*actual_token]);
			printf("PARSER cmd arg: %s\n", tokens[*actual_token]);
		}
		(*actual_token)++;
	}
	if (tokens[*actual_token] && tokens[*actual_token][0] == PIPE)
		(*actual_token)++;
	return (cmd);
}

/*
Take the tokens from lexer and return a structured table.

Return example:

   Input     Output    Error
     ↓         ↓         ↓
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| default | <pipe>  | default | cmd_1 | -options | arg_1 | arg_2 | NULL  |     |
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| <pipe>  | default | file_21 | cmd_2 | arg_1    | arg_2 | ...   | arg_n | NULL|
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| file_31 | file_32 | default | cmd_3 | -options | NULL  |       |       |     |
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| ...     | ...     | ...     | ...   | ...      | ...   | ...   | ...   | ... |
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| <pipe>  | default | default | cmd_n | NULL     |       |       |       |     |
+---------+---------+---------+-------+----------+-------+-------+-------+-----+
| NULL    |         |         |       |          |       |       |       |     |
+---------+---------+---------+-------+----------+-------+-------+-------+-----+

TODO
 - discretize between < and << (Override or append)
*/
t_cmd	**parser(char **tokens)
{
	t_cmd			**cmds;
	unsigned int	cmds_nbr;
	unsigned int	i;
	unsigned int	j;

	cmds_nbr = count_total_cmds(tokens);
	printf("PARSER total cmds: %u\n", cmds_nbr);
	cmds = ft_calloc(cmds_nbr + 1, sizeof(*cmds));
	if (!cmds)
		return (NULL);
	i = 0;
	j = 0;
	while(tokens[i])
	{
		cmds[j] = get_cmd(tokens, &i);
		if (!cmds[j])
			return (cmdsfree(cmds), NULL);
		j++;
	}



	int	index = 0;
	while (cmds[index])
	{
		printf("PARSER cmds[%i]\n", index);
		printf("\tin  : %s\n", cmds[index]->in);
		printf("\theredoc : %i\n", cmds[index]->heredoc);
		printf("\tout : %s\n", cmds[index]->out);
		printf("\tappend : %i\n", cmds[index]->append);
		printf("\terr : %s\n", cmds[index]->err);
		printf("\texec: %s\n", cmds[index]->exec);
		printf("\topt : %s\n", cmds[index]->opts);
		printf("\targs: %s\n", cmds[index]->args);
		index++;
	}
	return (cmds);
}
