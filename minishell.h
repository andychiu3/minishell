/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:07 by achiu             #+#    #+#             */
/*   Updated: 2024/08/30 09:34:40 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <curses.h>
# include <term.h>
# include <termios.h>

# define PROMPT "minishell $ "

enum e_token
{
	ARG,
	CMD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
};

enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
};

typedef struct s_token
{
	int		type;
	void	*content;
}	t_token;

typedef struct s_redirect
{
	char	*redir;
	char	*file;
}	t_redirect;

typedef struct s_cmd
{
	char		*cmd;
	char		**arg;
}	t_cmd;

typedef struct s_ast
{
	int				type;
	void			*content;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_sh
{
	t_list	*token;
	char	**env;
	int		ret;
}	t_sh;

// env
int			init_env(t_sh *sh, char **env);
char		*get_env_value(t_sh *sh, char *target);

// free malloc
void		ft_out(t_list *token, t_ast *node);
void		free_token(void *content);
void		free_ast(t_ast *node);
void		free_cmd(t_cmd *cmd);
void		free_redir(t_redirect *redir);

// signal
void		sig_init(void);
void		sig_int(int sig);
void		sig_quit(int sig);
void		disable_ctrl_echo(void);

// check
// void	lexical(char *line);
// int		quote_case(char *line);
// void	tokenize(char *line, t_list **token);
// char	*extract_quote(char **line, char c);
// char	*remove_quote(char *str);
// char	*extract_(char **line, char c);

// token
t_token		*tokenize(char *array);
int			is_cmd(char *str);
int			is_trunc(char *str);
int			is_append(char *str);

// lexer
// void	lexer(char *line);
void		scanning(t_sh *sh, char *line);
void		lexer(char *line, t_list **token);
int			if_quote(char c, int quote);
char		*extract(char *str, int *start, int *i);
char		*remove_quote(char *str);
int			quote_case(char *line);

// parse
t_ast		*parser(t_list **tokens);
int			is_redirect(int type);
int			is_op(int type);
// t_ast		*add_redirect(t_list **token);

// node cmd
t_ast		*create_cmd_node(t_list **tokens);
void		cmd_node_has_arg(t_ast *cmd_node, t_list **token);
int			arg_count(t_list *token);

// node pipe
t_ast		*handle_pipe(t_ast *node, t_list **token);
t_ast		*create_pipe_node(t_list **tokens);

// node redir
t_ast		*handle_redirect(t_ast *node, t_list **token, int is_first_call);
t_redirect	*create_redir(t_list **token);

// visualize
void		prnt_token(t_list *token);
void		prnt_ast(t_ast *node, int level);
void		node_prnter(t_ast *node);

// exec
void		exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		exec_pipe(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		process_redir(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		process_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh);

// exec cmd
void		exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		exec_echo(t_cmd *cmd, int in_fd, int out_fd);
void		exec_pwd(t_cmd *cmd, int in_fd, int out_fd);

// exec export
// void		exec_export(t_cmd *cmd, t_sh *sh);
void		process_export(t_cmd *cmd, t_sh *sh);
void		exec_export(char *arg, t_sh *sh);
int			is_valid_identifier(char *str);
int			compare_env_var(char *env, char *arg);
void		update_env(char *arg, t_sh *sh);

// exec unset
void		process_unset(t_cmd *cmd, t_sh *sh);
void		exec_unset(char *arg, t_sh *sh);
void		rm_env_var(char *arg, t_sh *sh);

#endif
