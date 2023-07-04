/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:21:38 by lpenelon          #+#    #+#             */
/*   Updated: 2023/07/04 13:39:29 by lpenelon         ###   ########.fr       */
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
	data->fd_in[0] = -1;
	data->fd_in[1] = -1;
	data->tree = NULL;
	data->join = NULL;
	data->split = NULL;
	data->tmp = NULL;
	data->slash_r = 0;
	init_env(data, 0);
	init_export(data, 0);
	init_sa(data->sa, data->sb);
	reset_p_vars(&data->p);
	*prompt = (char *)1;
}
