/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:38 by lpenelon          #+#    #+#             */
/*   Updated: 2023/07/04 18:55:07 by ddantas-         ###   ########.fr       */
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

void	init_env(t_data *data, int i)
{
	extern char	**environ;

	data->env = NULL;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));
	if (!data->env)
		free_if_err(data->env, 1);
	while (i < array_size(environ) - 2)
	{
		data->env[i] = ft_strjoin(environ[i], "\0");
		i++;
	}
	data->env[i] = NULL;
}
