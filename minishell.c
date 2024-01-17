#include "minishell.h"

void	sa_handler(int sig, siginfo_t *info, void *context)
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

static t_mini	init_ms(ac, av, env)
{
	t_mini				ms;
	struck sigaction	sa;

	ms = ft_bzero(&ms, sizeof (t_mini));
	if (ac > 1)
		exit_handler(&ms, "Error, use ./minishell" ,1);
	ft_bzero(&sa, sizeof (sa));
	sa.sa_flags = SA_SIGINFO;
}

int	main(int argc, char **argv, char **env)
{
	t_mini	ms;

	ms = init_ms(argc, argv, env);

}
