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
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	return (quotes);
}
