#include "../libs/minishell.h"

void	handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

// rl_replace_line("", 0);	// Replace the contents of rl_line_buffer with text.
// rl_on_new_line();
// Tell the update functions that we have moved onto a new (empty) line,
// usually after outputting a newline.
// rl_redisplay();
// Change what’s displayed on the screen
// to reflect the current contents of rl_line_buffer		

void	init_data(t_data *data, int i)
{
	extern char	**environ;

	data->rt = 0;
	data->env = NULL;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));
	if (!data->env)
		free_if_err(data, 1);
	while (i < array_size(environ) - 2)
	{
		data->env[i] = ft_strdup(environ[i]);
		i++;
	}
	data->env[i] = NULL;
}

// while (i < array_size(environ) - 2)
// -2 because the last two elements of the environ export
// are reserved for the lines and columns

void	init_sa(struct sigaction sa, struct sigaction sb)
{
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sb.sa_mask);
	sb.sa_handler = SIG_IGN;
	sb.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
}

void	init_stuff(t_data *data, char **prompt)
{
	init_data(data, 10);
	init_sa(data->sa, data->sb);
	*prompt = (char *)1;
}
