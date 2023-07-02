#include "../libs/minishell.h"

void	handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
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

void	init_env(t_data *data, int i)
{
	extern char	**environ;

	data->env = NULL;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));
	if (!data->env)
		free_if_err(data->env, 1);
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

void	quote(char *export, int i, int j)
{
	char	temp[ft_strlen(export) + 2];

	while (export[i] && export[i] != '=')
		temp[j++] = export[i++];
	if (export[i])
	{
		temp[j++] = export[i++];
		temp[j++] = '"';
		while (export[i])
			temp[j++] = export[i++];
		temp[j++] = '"';
		temp[j++] = '\0';
		export = ft_strdup(temp);
	}
}

static void	sort_export_ascii(char **export, int size, int i, int j)
{
	char	*temp;

	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(export[j], export[j + 1], nb_char_max(export)) > 0)
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		export[i] = ft_strjoin("declare -x ", export[i]);
		quote(export[i++], 0, 0);
	}
}

void	init_export(t_data *data, int i)
{
	extern char	**environ;

	data->export = NULL;
	data->export = malloc(sizeof(char *) * (array_size(data->env) + 1));
	if (!data->export)
		free_if_err(data->export, 1);
	while (i < array_size(data->env))
	{
		data->export[i] = ft_strdup(data->env[i]);
		i++;
	}
	data->export[i] = NULL;
	sort_export_ascii(data->export, array_size(data->export), 0, 0);
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

void	init_stuff(t_data *data, char **prompt)
{
	data->rt = 0;
	data->slash_r = 0;
	data->fd_in[0] = -1;
	data->fd_in[1] = -1;
	data->tree = NULL;
	init_env(data, 0);
	init_export(data, 0);
	init_sa(data->sa, data->sb);
	reset_p_vars(&data->p);
	*prompt = (char *)1;
}
