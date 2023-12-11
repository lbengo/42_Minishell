#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------- Includes ---------- */
#include <stdlib.h>

/* ---------- Constants ---------- */
# define NEW_LINE '\n'
# define TAB '\t'
# define SPACE ' '
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define GREAT '>'
# define LESS '<'
# define GREATGREAT ">>"
# define LESSLESS "<<"
# define PIPE '|'
# define OR "||"
# define AND "&&"
# define OPEN_BRACKET '('
# define CLOSE_BRACKET ')'

/* ---------- Structure of values ---------- */
typedef struct s_cmd {
	char	*cmd;
}	t_cmd;

/* ---------- Functions ---------- */

// process_prompt.c

char	process_prompt(char	*prompt);

// lexer.c

char	**lexer(char	*prompt);

// parser.c

char	**parser(char	**tokens);

// utils

char	is_special_string(char *str);
char	is_special_char(char c);

#endif