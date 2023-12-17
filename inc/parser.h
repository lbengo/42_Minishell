#ifndef PARSER_H
# define PARSER_H

/* ---------- Functions ---------- */

char	add_opt(char **cmd_opts, char *new_opt);
char	add_io(t_cmd **cmd, char *new_io, char *io_opt);
char	add_arg(char **cmd_args, char *new_arg);
char	is_append(char *str);
char	is_heredoc(char *str);
t_cmd	**parser(char **tokens);

#endif
