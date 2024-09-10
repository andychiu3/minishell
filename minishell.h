/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:07 by achiu             #+#    #+#             */
/*   Updated: 2024/09/10 18:41:48 by fiftyblue        ###   ########.fr       */
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
# include <malloc/malloc.h>

# define PROMPT "\x1b[1;30mminishell $ \x1b[0m"

int	g_last_exit_code;

enum e_token
{
	ARG,
	CMD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	APPEND,
	HEREDOC,
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

// env 2
int			init_env(t_sh *sh, char **env);
char		*get_env_value(t_sh *sh, char *target);

// free malloc 5
void		ft_out(t_list *token, t_ast *node);
void		free_token(void *content);
void		free_ast(t_ast *node);
void		free_cmd(t_cmd *cmd);
void		free_redir(t_redirect *redir);

// signal 4
void		sig_init(void);
void		sig_int(int sig);
void		sig_quit(int sig);
void		disable_ctrl_echo(void);

// token 4
void		tokenize(char *array, t_list **token_list, t_sh *sh);
int			is_cmd(char **str, t_sh *sh);
int			is_trunc(char *str);
int			is_append(char *str);

// executable cmd 1
char		*is_executable(char *str, t_sh *sh);

// lexer 7
void		scanning(t_sh *sh, char *line);
void		lexer(char *line, t_list **token, t_sh *sh);
int			if_quote(char c, int quote);
// char		*extract(char *str, int *start, int *i, t_sh *sh);
char		*remove_quote(char *str);
int			quote_case(char *line);
char		*extract(char *str, int *i, t_sh *sh, int *quote);

// parse 3
t_ast		*parser(t_list **tokens);
int			is_redirect(int type);
int			is_op(int type);
// t_ast		*add_redirect(t_list **token);

// node cmd 3
t_ast		*create_cmd_node(t_list **tokens);
void		cmd_node_has_arg(t_ast *cmd_node, t_list **token);
int			arg_count(t_list *token);

// node pipe 2
t_ast		*handle_pipe(t_ast *node, t_list **token);
t_ast		*create_pipe_node(t_list **tokens);

// node redir 2
t_ast		*handle_redirect(t_ast *node, t_list **token, int call, t_ast *tmp);
t_redirect	*create_redir(t_list **token);

// visualize 4
void		prnt_token(t_list *token);
void		prnt_ast(t_ast *node, int level);
void		node_prnter(t_ast *node);
void		prnt_strs(char **strs);

// exec 4
void		exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		exec_pipe(t_ast *root, int in_fd, int out_fd, t_sh *sh);
// void		process_redir(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		process_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh);

// exec_redir 4
void		process_redir(t_ast *root, int *in_fd, int *out_fd, t_sh *sh);
void		exec_input(t_redirect *redir, int *in_fd);
void		exec_trunc(t_redirect *redir, int *out_fd);
void		exec_append(t_redirect *redir, int *out_fd);

// exec cmd 5
void		exec_cmd(t_ast *root, int in_fd, int out_fd, t_sh *sh);
void		exec_echo(t_cmd *cmd, int in_fd, int out_fd);
void		exec_pwd(t_cmd *cmd, int in_fd, int out_fd);
void		exec_env(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh);
void		exec_exit(t_cmd *cmd);

// exec export 5
// void		exec_export(t_cmd *cmd, t_sh *sh);
void		process_export(t_cmd *cmd, t_sh *sh);
void		exec_export(char *arg, t_sh *sh);
int			is_valid_identifier(char *str);
int			compare_env_var(char *env, char *arg);
void		update_env(char *arg, t_sh *sh);

// exec unset 3
void		process_unset(t_cmd *cmd, t_sh *sh);
void		exec_unset(char *arg, t_sh *sh);
void		rm_env_var(char *arg, t_sh *sh);

// exec cd 5
void		process_cd(t_cmd *cmd, t_sh *sh);
int			valid_arg_amount(t_cmd *cmd);
char		*wd_cases(t_cmd *cmd, t_sh *sh);
char		*expand_path(t_cmd *cmd, t_sh *sh);
void		updateoldpwd_chdir(char *target_path, t_sh *sh);

// exec others? 2
void		exec_with_execve(t_cmd *cmd, t_sh *sh);
char		**combine_cmd_arg_with_path(t_cmd *cmd, char *path);

// splits by var 5
char		**split_by_var(char *str);
int			split_count(char *str);
void		normal_word_ends(char *str, int *quote, int *i, int *count);
int			var_(char *str, int quote, int i);
void		var_ends(char *str, int *i, int *count);

// var 2
char		*var_situation(char *str, t_sh *sh);
void		replace_var(char **strs, t_sh *sh);

// error 1
char		*errormsg_exitcode(char *why, int exit_code, char *str);

#endif
