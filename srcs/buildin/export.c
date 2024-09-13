/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:12:45 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/09/13 07:45:12 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 1 if name exists
// return -1 if name exists then you have to change the *str
// return 0 if name doesn't exist then 
int	compare_env_var(char *env, char *arg)
{
	int		i;
	char	*pos_eq;

	if (!env || !arg)
		return (0);
	pos_eq = ft_strchr(env, '=');
	i = 0;
	if (pos_eq)
		i = pos_eq - env;
	if (ft_strcmp(env, arg) == 0)
		return (1);
	else if (ft_strncmp(env, arg, i) == 0)
		return (-1);
	return (0);
}

// return -1 if not valid
// return 0 if there is no =
// return 1 if valid
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
	{
		i++;
		while (str[i] && str[i] != '=')
		{
			if ((str[i] != '_' && !ft_isalnum(str[i])))
				return (-1);
			i++;
		}
	}
	else
		return (-1);
	return (str[i] == '=');
}

// void	update_env(char *arg, t_sh *sh)
// {
// 	int		i;
// 	char	**tmp;

// 	if (!sh || !arg)
// 		return ;
// 	tmp = malloc(sizeof(char *) * (ft_strs_count(sh->env) + 2));
// 	if (!tmp)
// 		return ;
// 	i = -1;
// 	while (sh->env[++i])
// 		tmp[i] = ft_strdup(sh->env[i]);
// 	// printf("update_env: arg: %s\n", arg);
// 	tmp[i++] = ft_strdup(arg);
// 	tmp[i] = NULL;
// 	ft_freematrix(sh->env);
// 	sh->env = tmp;
// }

// only be used if arg n sh valid cuz too many lines
void	exec_export(char *arg, t_sh *sh)
{
	int		i;

	i = -1;
	if (is_valid_identifier(arg) == 1)
	{
		while (sh->env[++i])
		{
			if (compare_env_var(sh->env[i], arg) == -1)
			{
				free(sh->env[i]);
				sh->env[i] = ft_strdup(arg);
				return ;
			}
			else if (compare_env_var(sh->env[i], arg) == 1)
				return ;
		}
		if (!sh->env[i])
			add_str_to_strs(&(sh->env), arg);
	}
	else if (is_valid_identifier(arg) == -1)
		errormsg_exitcode("id", 1, arg);
}

void	process_export(t_cmd *cmd, t_sh *sh)
{
	int	i;

	if (!cmd || !sh)
		return ;
	i = -1;
	while (cmd->arg[++i])
		exec_export(cmd->arg[i], sh);
}
