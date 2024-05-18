/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:13 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/05/11 22:33:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_handler(const char *msg, int code)
{
	if (code && code != 127)
		ft_putstr_fd("ERROR\n", 2);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	if (!code && !msg)
		ft_putendl_fd("See you soon, human!", 1);
	rl_clear_history();
	exit (code);
}

int	is_only_zeros(char	*nbr)
{
	int	i;

	i = -1;
	while (nbr[++i])
	{
		if (nbr[i] != '0')
			return (0);
	}
	return (1);
}

int	is_valid(char *nbr)
{
	int	i;

	i = 0;
	if (nbr[0] == '+')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **cmd)
{
	int	code;

	//ft_printf("INSIDE EXIT:\n");
	code = 0;
	if (!cmd[1])
		cmd = free_db_str(cmd);
	if (is_only_zeros(cmd[1]))
	{
		cmd = free_db_str(cmd);
		return (0);
	}
	if (!cmd[2] && is_valid(cmd[1]))
	{
		code = ft_atoi(cmd[1]);
		cmd = free_db_str(cmd);
		ft_printf("exited with code: %d\n", code);
		return (code);
	}
	cmd = free_db_str(cmd);
	ft_printf("%s : exit: too many arguments", NPROMPT);
	return (2);
}
