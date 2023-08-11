/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:38 by lpenelon          #+#    #+#             */
/*   Updated: 2023/08/11 10:09:42 by lpenelon         ###   ########.fr       */
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
