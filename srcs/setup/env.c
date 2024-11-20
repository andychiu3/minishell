/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:05:44 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/10/18 09:48:34 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_name(char *env)
{
	char	*pos_eq;
	int		len;

	if (!env)
		return (NULL);
	len = 0;
	pos_eq = ft_strchr(env, '=');
	if (pos_eq)
		len = pos_eq - env;
	return (ft_substr(env, 0, len));
}

char	*get_env_value(t_sh *sh, char *target)
{
	int		i;
	size_t	len;

	len = ft_strlen(target);
	i = -1;
	while (sh->env && sh->env[++i])
		if (ft_strncmp(target, sh->env[i], len) == 0 && sh->env[i][len] == '=')
			return (ft_strchr(sh->env[i], '=') + 1);
	return (NULL);
}

void	shlvl_(t_sh *sh)
{
	char	*shlvl;
	char	*tmp;
	int		lvl;
	char	*lvl_str;

	lvl = 0;
	tmp = NULL;
	tmp = ft_strdup("SHLVL");
	shlvl = get_env_value(sh, "SHLVL");
	if (shlvl)
		lvl = ft_atoi(shlvl);
	lvl_str = ft_itoa(++lvl);
	ft_strjoin_with_sep(&tmp, lvl_str, "=");
	free(lvl_str);
	exec_export(tmp, sh);
	free(tmp);
}

void	env_without_envp(t_sh *sh)
{
	char		*pwd;
	char		*tmp;

	pwd = getcwd(NULL, 0);
	tmp = NULL;
	tmp = ft_strdup("PWD");
	ft_strjoin_with_sep(&tmp, pwd, "=");
	if (pwd)
		free(pwd);
	exec_export(tmp, sh);
	free(tmp);
	shlvl_(sh);
	exec_export("_=/usr/bin/env", sh);
}

// STRDUP needed if we r gonna change/use env
int	init_env(t_sh *sh, char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	sh->env = malloc(sizeof(char *) * (i + 1));
	if (!sh->env)
		return (0);
	i = -1;
	while (env[++i])
		sh->env[i] = ft_strdup(env[i]);
	sh->env[i] = NULL;
	env_without_envp(sh);
	return (1);
}
