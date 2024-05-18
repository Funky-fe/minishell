/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:17 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/05/17 15:17:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **cmd, char ***envp)
{
	int	i;

	if (!cmd[1])
	{
		i = 0;
		while (envp && ft_strncmp(envp[0][i], "PWD=", 4))
			i++;
		if (envp && envp[0][i])
			ft_printf("%s", envp[i] + 4);
	}
	else
	{
		ft_putstr_fd("Bad usage, burro.", 2);
		return (69);
	}
	return (0);
}
