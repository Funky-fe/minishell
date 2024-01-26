/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:14:43 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/01/26 11:30:25 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char	*get_input(t_mini *ms, const char *prompt)
{
	char	*input;
	
	input = readline(prompt);
	if (input && input[0])
		//command history function
	else if (!input)
		exit_handler(ms, EXIT_MSG, 0);
	return (input);
}

void	ft_sa_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	ft_printf("sig: %d\n", sig);
	if (sig == SIGINT && info->si_pid != 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static t_mini	ft_init(int argc, char *argv[], char **envp)
{
	t_mini				ms;
	struct sigaction	sa;

	(void) argv;
	ft_bzero (&ms, sizeof (t_mini));
	if (argc > 1)
		exit_handler (&ms, "Usage: ./minishell", 1);
	ft_bzero (&sa, sizeof (sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_sa_handler;
	sigaction (SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	ms.envp = ft_matdup (envp);
	if (!envp)
		exit_handler (&ms, "Error allocating memory to environment", 1);
	ms.prompt = ft_strdup("minishell > ");
	if (!ms.prompt)
		exit_handler (&ms, "Error allocating memory to prompt", 1);
	return (ms);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	ms;

	ms = ft_init(argc, argv, env);
	while (1)
	{
		ms.input = get_input(&ms, ms.prompt);
		if (ms.input && *ms.input)
	}
}
