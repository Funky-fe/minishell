/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:06:04 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/05/17 15:09:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoine(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	i;

	i = 0;
	s1_len = ft_strlen(s1);
	str = (char *) ft_calloc(s1_len + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[s1_len + i] = s2[i];
		i++;
	}
	return (str);
}

int	go_to_dir(char *dir, char ***env, t_execlist *execl)
{
	char	**exp;
	char	*temp;

	temp = NULL;
	exp = ft_calloc(3, sizeof(char *));
	exp[0] = ft_strdup("export");
	temp = getcwd(temp, PATH_MAX);
	if (chdir(dir))
	{
		ft_putstr_fd(NPROMPT": cd: No such file or directory", 2);
		return (69);
	}
	else
	{
		exp[1] = ft_strjoine ("OLDPWD=", temp);
		ft_export (exp, env, execl);
		temp = free_str(temp);
		exp[1] = free_str(exp[1]);
		temp = getcwd(temp, PATH_MAX);
		exp[1] = ft_strjoine("PWD=", temp);
		ft_export (exp, env, execl);
		return (0);
	}
	temp = free_str(temp);
	exp = free_db_str(exp);
}

char	*home_dir(char **env)
{
	char	*home;

	ft_printf("FETCHING HOME DIRECTORY:\n");
	while(env && ft_strncmp(env[0], "HOME=", 5))
		env++;
	home = *env + 5;
	return (home);
}

int	ft_cd(char **cmd, char ***env, t_execlist *execl)
{
	int	i;
	ft_printf("INSIDE CD:\n");

	i = 0;
	ft_printf("cmd[1] = %s\n", cmd[1]);
	if (!cmd[1])
		i = go_to_dir(home_dir(*env), env, execl);
	else if (cmd[1] && !cmd[2])
		i = go_to_dir(cmd[1], env, execl);
	else
	{
		ft_putstr_fd ("-" NPROMPT ": cd:  invalid usage\n", 2);
		return (i);
	}
	return (i);
}
