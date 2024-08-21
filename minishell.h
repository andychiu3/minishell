/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:07 by achiu             #+#    #+#             */
/*   Updated: 2024/08/21 12:10:59 by fiftyblue        ###   ########.fr       */
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
	PIPE,
	VAR,
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

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	char	*option;
}	t_cmd;

typedef struct s_ast
{
	void			*content;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_sh
{
	t_list	*token;
	char	**env;
	int		ret;
	// bool	cmd;
}	t_sh;

int		init_env(t_sh *sh, char **env);

// signal
void	sig_init(void);
void	sig_int(int sig);
void	sig_quit(int sig);
void	disable_ctrl_echo(void);

// check
// void	lexical(char *line);
// int		quote_case(char *line);
// void	tokenize(char *line, t_list **token);
// char	*extract_quote(char **line, char c);
// char	*remove_quote(char *str);
// char	*extract_(char **line, char c);

// token
int		is_cmd(char *str);
t_token	*tokenize(char *array);

// lexer
// void	lexer(char *line);
void	scanning(char *line);
void	lexer(char *line, t_list **token);
int		if_quote(char c, int quote);
char	*extract(char *str, int *start, int *i);
char	*remove_quote(char *str);

// void	parser();

#endif
