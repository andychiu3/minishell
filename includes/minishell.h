/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:07 by achiu             #+#    #+#             */
/*   Updated: 2024/10/21 18:36:52 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

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
# include <sys/stat.h>

# define PROMPT "\x1b[1;30mminishell $ \x1b[0m"

enum e_token
{
	ARG,
	CMD,
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

enum e_sig_case
{
	INTERACTIVE,
	PARSE,
	NON_INTERACTIVE,
	IN_CHILD,
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
	int		heredoc_fd;
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

int	g_sig_num;

typedef struct s_sh
{
	char	**env;
	int		signaled;
	int		*ret;
	int		pipe_in;
	int		pipe_out;
}	t_sh;

void		minishell(t_sh *sh, int ac, char **av);
char		*get_line(char *prompt, int ac, char **av, t_sh *sh);
void		scanning(t_sh *sh, char *line);
void		exec_ast(t_ast *root, int in_fd, int out_fd, t_sh *sh);

/* ================================ SETUP ================================ */
// env 3
int			init_env(t_sh *sh, char **env);
char		*get_env_value(t_sh *sh, char *target);
char		*env_name(char *env);

// init_flags 1
void		init_flags(t_sh *sh);

/* ================================ LEXER ================================ */
// lexer 3
void		lexer(char *line, t_list **token);
char		*extract(char *str, int *i, int *quote);
char		*extract_op(char *str, int *start, int *i);

// quote utils 4
int			quote_case(char *line);
int			quote_valid(char *line, t_sh *sh);
int			if_quote(char c, int quote);
char		*remove_quote(char *str);

// token 3
void		tokenize(char **array, t_list **token_list);
int			is_trunc(char *str);
int			is_append(char *str);

/* ================================= AST ================================= */
// parse 5
t_ast		*parser(t_list **tokens, int *syntax_err, t_sh *sh);
int			is_redirect(int type);
int			is_op(int type);
void		*syntax_error(int *syntax_err, int err_type);
void		syntax_err_case(int syntax_err, t_list *token, t_sh *sh);

// node cmd 3
t_ast		*create_cmd_node(t_list **tokens);
void		cmd_node_has_arg(t_ast *cmd_node, t_list **token);
int			arg_count(t_list *token);

// node pipe 2
t_ast		*handle_pipe(t_ast *node, t_list **token,
				int *syntax_err, t_sh *sh);
t_ast		*create_pipe_node(t_list **tokens);

// node redir 5
t_ast		*handle_init_redir(t_ast *node,
				t_list **token, int *syntax_err, t_sh *sh);
t_ast		*handle_recur_redir(t_ast **node_r,
				t_list **token, int *syntax_err, t_sh *sh);
t_ast		*create_node_redir(t_list **token, int *syntax_err);
t_redirect	*create_redir(t_list **token, int *syntax_err);
void		append_cmd_args(t_ast **node, t_list **token);

// heredoc input 5
void		fork_for_heredoc(t_redirect *redir, t_sh *sh);
void		setup_heredoc(t_redirect *redir, int pipe_o, t_sh *sh);
int			parse_dlmtr(t_redirect *redir, char **delimiter, t_sh *sh);
void		heredoc_input(char *dlmtr, t_sh *sh, int quote_case, char **input);
void		heredoc_result(t_redirect *redir,
				t_sh *sh, int status, int *pipe_fd);

/* ================================ EXEC ================================ */

// exec_redir 3
void		redir(t_ast *root, int *in_fd, int *out_fd, t_sh *sh);
int			process_redir(t_ast **root, int *in_fd, int *out_fd, t_sh *sh);
int			redir_err(char *file, int ambiguous, t_sh *sh);

// input heredoc 2
int			exec_input(t_redirect *redir, int *in_fd, t_sh *sh);
int			exec_heredoc(t_redirect *redir, int *in_fd);

// trunc append 2
int			exec_trunc(t_redirect *redir, int *out_fd, t_sh *sh);
int			exec_append(t_redirect *redir, int *out_fd, t_sh *sh);

// pipe 1
void		exec_pipe(t_ast *root, int in_fd, int out_fd, t_sh *sh);

// refresh cmd 5
void		refresh_cmd(t_cmd *cmd, t_sh *sh);
char		**store_in_tmp(t_cmd *cmd, t_sh *sh);
void		clean_cmd_ptr(t_cmd *cmd);
void		update_cmd(t_cmd *cmd, char **cmd_in_matrix);
void		process_cmd_element(char **element, char ***tmp, t_sh *sh);

// exec cmd 4
void		exec_cmd(t_ast *root, int *in_fd, int *out_fd, t_sh *sh);
void		redir_n_backup_std_io(int *in_fd, int *out_fd, int *saved_fd);
void		restore_std_io(int in_fd, int out_fd, int *saved_fd);
void		close_unuse_fd(int *in_fd, int *out_fd);

// execve 3
void		fork_for_execve(t_ast *root, int *in_fd, int *out_fd, t_sh *sh);
void		exec_with_execve(t_cmd *cmd, t_sh *sh);
char		**get_arg_for_execve(t_cmd *cmd, char *path);

// executable cmd 3
char		*not_executable(char *str, t_sh *sh);
char		*does_path_exist(char *str, t_sh *sh);
char		*execve_case(char *why, char *str, int exit_code, t_sh *sh);

// builtin 5
void		setup_builtin(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh);
int			is_builtin(char *cmd);
void		builtin(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh);
void		exec_pwd(t_cmd *cmd, t_sh *sh);
void		exec_env(t_cmd *cmd, int in_fd, int out_fd, t_sh *sh);

// echo 2
void		exec_echo(t_cmd *cmd, t_sh *sh);
int			echo_option(char *arg);

// exit 2
void		exec_exit(t_cmd *cmd, t_sh *sh);
void		exit_nbr_err_case(t_cmd *cmd, t_sh *sh);

// export 5
void		process_export(t_cmd *cmd, t_sh *sh);
void		exec_export(char *arg, t_sh *sh);
void		var_value_adding(char *arg, t_sh *sh);
void		var_value_changing(char *arg, t_sh *sh);
void		update_env_(char *arg, t_sh *sh);

// export utils 5
int			is_valid_identifier(char *str);
int			pos_of_env_var(char *arg, t_sh *sh);
int			compare_env_var(char *env, char *arg);
char		*new_value(char *arg);
char		*new_name(char *arg);

// unset 4
void		process_unset(t_cmd *cmd, t_sh *sh);
void		exec_unset(char *arg, t_sh *sh);
void		rm_env_var(char *arg, t_sh *sh);
int			compare_var(char *env, char *arg);

// cd 4
void		process_cd(t_cmd *cmd, t_sh *sh);
void		exec_cd(char *path, t_sh *sh);
char		*wd_cases(t_cmd *cmd, t_sh *sh);
void		updateoldpwd_chdir(char *target_path, t_sh *sh);

/* ================================ UTILS ================================ */

// signal 5
void		sig_mode(int mode);
void		disable_ctrl_echo(void);
void		sig_int(int sig);
void		sig_parse_heredoc(int sig);
void		sig_non_interactive(int sig);

// var 2
char		*var_situation(char *str, t_sh *sh);
void		replace_var(char ***strs, t_sh *sh);

// splits by var 5
char		**split_by_var(char *str);
int			split_count(char *str);
void		normal_word_ends(char *str, int *quote, int *i, int *count);
int			var_(char *str, int quote, int i);
void		var_ends(char *str, int *i, int *count);

// split if var has space 2
char		**lexer_for_var(char *line);
char		*extract_in_var(char *str, int *i, int *quote);

// check_var_rm_quote 3
int			check_var_rm_quote(char **str, t_sh *sh);
int			check_var(char **str, t_sh *sh);
void		rm_strs_quote(char **strs);

// expand_path
void		expand_path(char **str);

// free address 5
void		ft_out(t_list *token, t_ast *node);
void		free_token(void *content);
void		free_ast(t_ast *node);
void		free_cmd(t_cmd *cmd);
void		free_redir(t_redirect *redir);

// visualize 5
void		prnt_token(t_list *token);
void		prnt_ast(t_ast *node, int level);
void		node_prnter(t_ast *node);
void		prnt_strs(char **strs);
void		prnt_lst_node(t_list *lst_node);

// waitpid_status 1
int			waitpid_status(int *status, t_sh *sh);

// comsume_stdin
void		consume_stdin(void);

// option
int			validate_option(char *arg, char c);

// error 1
char		*errormsg_exitcode(char *why, int exit_code, char *str, t_sh *sh);
char		*builtin_err_cases(char *why, int exit_code, char *str, t_sh *sh);

// function_err_exit
void		function_err_exit(char *str);
void		free_n_exit(char *input, char *dlmtr, int exit_code);
void		end_of_file(int ac, t_sh *sh);

#endif
