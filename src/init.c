#include "../libs/minishell.h"

void	handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
	return ;
}

void	init_data(t_data *data)
{
	data->rt = 0;
	data->pid = 0;
}

void	init_sa(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_stuff(t_data *data, char **prompt)
{
	init_data(data);
	init_sa(data->sa);
	*prompt = (char *)1;
}