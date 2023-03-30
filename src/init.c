#include "../libs/minishell.h"

void	handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);	// Replace the contents of rl_line_buffer with text.
		rl_on_new_line();		// Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
		rl_redisplay();			// Change what’s displayed on the screen to reflect the current contents of rl_line_buffer
	}
	return ;
}

void	init_data(t_data *data, int i)
{
	extern char	**environ;

	data->rt = 0;
	data->pid = 0;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));
	if (data->env == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	while (i < array_size(environ) - 2)				// -2 because the last two elements of the environ export are reserved for the lines and columns
	{
		data->env[i] = ft_strdup(environ[i]);
		i++;
	}
	data->env[i] = NULL;
}

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

static void init_parser(t_data *data)
{
	int i;

	i = 10;
	data->tokens = (char **)malloc(i * sizeof(char*));
	if (data->tokens == NULL)
	{
		free(data->env);
		exit(write(1, "Error: malloc failed\n", 21));
	}
	while (i-- > 0)
	{
		data->tokens[i] = (char *)malloc(250 * sizeof(char));
		if(data->tokens[i] == NULL)
		{
			free(data->env);
			free(data->tokens);
			while (i++ < 0)
				free(data->tokens[i]);
			exit(write(1, "Error: malloc failed\n", 21));
		}
		ft_bzero(data->tokens[i], 250);
	}
}

void	init_stuff(t_data *data, char **prompt)
{
	init_data(data, 10);
	init_sa(data->sa, data->sb);
	init_parser(data);
	*prompt = (char *)1;
}
