/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achiu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:44:07 by achiu             #+#    #+#             */
/*   Updated: 2024/07/30 10:44:09 by achiu            ###   ########.fr       */
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

# define PROMPT "minishell $ "

enum e_token
{
	WORD,
	CMD,
	PIPE,
	VAR,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
};

typedef struct s_token
{
	int		type;
	void	*content;
}	t_token;

typedef struct s_cmd
{
	char	*cmd;
	char	*arg;
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
	// bool	exit;
}	t_sh;

int	init_(t_sh *sh, char **env);

#endif
