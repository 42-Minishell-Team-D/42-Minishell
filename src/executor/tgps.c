/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:33:20 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/03 22:33:31 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = NULL;
	if (get_number_of_processes(data->tree) > 1)
	{
		data->pipes = (int **)ft_calloc(sizeof(int *),
				(get_number_of_processes(data->tree) - 1));
	}
	while (i < get_number_of_processes(data->tree) - 1)
	{
		data->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		data->pipes[i][0] = -1;
		data->pipes[i][1] = -1;
		i++;
	}
}

static void	close_unused_pipes_2(int id, t_bt *tree, t_data *data)
{
	int		reading;
	int		writing;
	int		n;

	n = 0;
	reading = data->pipes[id - 1][0];
	if (tree->parent->right != NULL)
		writing = data->pipes[id][1];
	else
		writing = -1;
	while (n < id)
	{
		if (reading != data->pipes[n][0])
			close(data->pipes[n][0]);
		if (writing != data->pipes[n][1])
			close(data->pipes[n][1]);
		n++;
	}
}

void	close_unused_pipes(int id, t_bt *tree, t_data *data)
{
	if (id == 0)
	{
		if (tree->right != NULL)
			close(data->pipes[id][0]);
		while (++id < get_number_of_processes(data->tree) - 1)
		{
			close(data->pipes[id][0]);
			close(data->pipes[id][1]);
		}
	}
	else
		close_unused_pipes_2(id, tree, data);
}

int	init_executor(t_data *data)
{
	int	i;

	i = 0;
	init_pipes(data);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < get_number_of_processes(data->tree) - 1)
	{
		if (pipe(data->pipes[i++]) < 0)
		{
			close_free_pipes(data);
			return (1);
		}
	}
	return (0);
}
