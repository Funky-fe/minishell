/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:19 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/05/17 15:18:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_var(char *var, char ***envp)
{
	int		i;
	char	*temp_var;

	if (!var || !envp)
		return ;
	temp_var = ft_strjoin(var, "=");
	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], temp_var, ft_strlen(temp_var)))
		i++;
	if (*envp && envp[0][i])
	{
		envp[0][i] = free_str(envp[0][i]);
		envp[0][i] = envp[0][i + 1];
		i++;
		while (envp[0][i])
		{
			envp[0][i] = envp[0][i + 1];
			i++;
		}
		envp[0][i] = NULL;
	}
	else
		ft_printf("unset: %s: invalid parameter name", var);
	temp_var = free_str(temp_var);
}

int	ft_unset(char **cmd, char ***envp, t_execlist *execl)
{
	while (*(++cmd))
		remove_var(*cmd, envp);
	execl->my_envp = envp[0];
	free_db_str(envp[0]);
	return (0);
}
