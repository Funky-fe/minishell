/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:15 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/05/17 15:15:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_var_pos(char *var, char **envp)
{
	char	*temp_var;
	int		var_len;
	int		var_pos;

	var_len = ft_strchr(var, '=') - var;
	temp_var = ft_calloc(var_len + 2, sizeof(char));
	ft_strlcpy (temp_var, var, var_len + 2);
	temp_var[var_len] = '=';
	temp_var[var_len + 1] = '\0';
	var_pos = 0;
	while (envp[var_pos] && ft_strncmp(temp_var, envp[var_pos], var_len + 1))
		var_pos++;
	temp_var = free_str(temp_var);
	return (var_pos);
}

void	update_var(char *var, int var_pos, char ***envp, t_execlist *execl)
{
	char	**temp_envp;

	if (!envp[var_pos])
	{
		temp_envp = ft_calloc(var_pos + 2, sizeof(char *));
		temp_envp[var_pos] = var;
		while (var_pos--)
			temp_envp[var_pos] = envp[0][var_pos];
		envp[0] = free_db_str(envp[0]);
		execl->my_envp = temp_envp;
	}
	else
	{
		envp[0][var_pos] = free_str(envp[0][var_pos]);
		envp[0][var_pos] = ft_strdup(var);
	}
}

int	valid_var(char *var)
{
	int	i;
	int	res;

	res = 1;
	i = 0;
	if (!var || var[0] == '=')
		res = 0;
	if (isdigit(var[0]))
		res = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && !ft_isalnum(var[i]))
			res = 0;
		i++;
	}
	return (res);
}

int	ft_export(char **cmd, char ***envp, t_execlist *execl)
{
	int	i;
	int	var_pos;

	ft_printf("INSIDE EXPORT:\n");
	if (!cmd[1])
		ft_env(cmd, envp);
	i = 1;
	while (cmd[++i])
	{
		if (valid_var(cmd[i]) && ft_strchr(cmd[i], '='))
		{
			var_pos = get_var_pos(cmd[i], *envp);
			update_var(cmd[i], var_pos, envp, execl);
		}
		else if (!valid_var(cmd[i]))
		{
			ft_printf("%s: export: %s: not a valid identifier\n", NPROMPT, cmd[i]);
			return (69);
		}
	}
	return (0);
}
