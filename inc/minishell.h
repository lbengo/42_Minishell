#ifndef MINISHELL_H
# define MINISHELL_H

/* ---------- Includes ---------- */

# include <unistd.h> // Librería que gestiona la función close
# include <fcntl.h> // Librería que gestiona la función open

/* ---------- Constants ---------- */

// Special shell chars

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
# define DOLLAR '$'
# define QUESTION_MARK '?'
# define OR "||"
# define AND "&&"
# define OPEN_BRACKET '('
# define CLOSE_BRACKET ')'

/* ---------- Structure of values ---------- */

typedef struct s_cmd {
	char	*in; // ruta de un fichero / | / file descriptor en número (hay que pasarlo de array a número)
	char	heredoc; // 1 si hay heredoc y borrar fichero / 0 si no hay
	char	*out; // crar archivo si no existe, borrar y escribir / si append es 1 sumar / |
	char	append; // 1 si hay append / 0 si no
	char	*err; // el error me lo rediriges al fichero escrito en err
	char	*exec;
	char	*opts;
	char	*args;
}	t_cmd;

/* ---------- Functions ---------- */

// read_input.c

char	*read_input(void);

// process_prompt.c

char	process_prompt(char *prompt);

// lexer.c

char	**lexer(char *prompt);

// expander.c

char	expander(char ***parser_table);

// utils

char	is_special_string(char *str);
char	is_special_char(char c);
void	cmdsfree(t_cmd **cmds);

// exec

void exec(t_cmd	**cmds);

#endif
