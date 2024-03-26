/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:01:51 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/01/29 17:04:59 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_handler(t_mini *ms, const char *msg, int code)
{
	int	i;

	i = 0;
	if (code && code != 127)
		ft_putstr_fd(ERROR_MSG, 2);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	if (!code && !msg)
		ft_putendl_fd(EXIT_MSG, 1);
	ms->input = free_ptr(ms->input);
	ms->prompt = free_ptr(ms->prompt);
	ms->envp = free_mat(ms->envp);
	ms->token = free_token(ms->token);
	rl_clear_history();
	exit (code);
}

int	check_quotes(char c, int quotes)
{
	if (c == '\"')
	{
		if (!quotes)
			return (1);
		else if (quotes == 1)
			return (0);
	}
	else if (c == '\'')
	{
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	}	
	return (quotes);
}

char	**ft_matdup(char **mat)
{
	int		i;
	char	**temp;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	temp = ft_calloc(i + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		temp[i] = ft_strdup(mat[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
