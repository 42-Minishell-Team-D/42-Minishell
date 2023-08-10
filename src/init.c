/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:38 by lpenelon          #+#    #+#             */
/*   Updated: 2023/08/10 18:02:58 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

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
	data->ms_id = getpid();
	data->n = 0;
	while (data->n < 10)
		data->childs_pid[data->n++] = -1;
	data->n = 0;
	data->fd_in[0] = -1;
	data->fd_in[1] = -1;
	data->tree = NULL;
	data->join = NULL;
	data->split = NULL;
	data->itoa = NULL;
	data->tmp = NULL;
	data->slash_r = 0;
	init_env(data, 0);
	init_export(data, 0);
	init_sa(data->sa, data->sb);
	reset_p_vars(&data->p);
	*prompt = (char *)1;
}

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

static int get_after_equal_sign(char *var)
{
	int	i;
	char *value;
	int ret;

	i = 0;
	ret = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	value = ft_substr(var, i + 1, 500);
	ret = ft_atoi(value);
	free(value);
	return (ret);
}

static void	increment_SHLVL(t_data *data)
{
	int	i;
	int	value;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			value = get_after_equal_sign(data->env[i]);
			if (data->env[i] != NULL)
				free(data->env[i]);
			data->env[i] = ft_strjoin("SHLVL=", ft_itoa(value + 1));
			break ;
		}
		i++;
	}
}

static void add_to_env(t_data *data)
{
	int size;

	size = array_size(data->env);
	data->env = ft_realloc(data->env, sizeof(char *) * \
	(size + 2));
	if (data->env == NULL)
		return ;
	data->env[size] = ft_strdup("SHLVL=0");
	data->env[size + 1] = NULL;
}

static void update_SHLVL(t_data *data)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (data->env[i] != NULL && b == 0)
	{
		// ft_printf_fd(1, "data->env[i] = %s\n", data->env[i]);
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
			b = 1;
		i++;
	}
	// ft_printf_fd(1, "b = %i\n", b);
	if (b == 0)	// SHLVL doesn't exist, create it to 0
		add_to_env(data);
	// increment SHLVL value by 1 or put to 1 if value is not numeric
	increment_SHLVL(data);
}

void	init_env(t_data *data, int i)
{
	extern char	**environ;

	data->env = NULL;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));	// maybe change that to be more precise
	if (!data->env)
		free_if_err(data->env, 1);
	while (i < array_size(environ) - 1)
	{
		data->env[i] = ft_strjoin(environ[i], "\0");
		i++;
	}
	update_SHLVL(data);
	data->env[i + 1] = NULL;
}
