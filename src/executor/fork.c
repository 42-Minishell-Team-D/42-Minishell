/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:28:55 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 09:04:52 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static int	builtin_executor_child(char **split, t_data *data, t_bt *tree)
{
	data->rt = 1;
	if (ft_strncmp(split[0], "pwd\0", 4) == 0)
		data->rt = exec_pwd();
	else if (ft_strncmp(split[0], "echo\0", 5) == 0)
		data->rt = exec_echo(split);
	else if (ft_strncmp(split[0], "export\0", 7) == 0 && split[1] == NULL)
		data->rt = exec_export(split, data, tree);
	else if (ft_strncmp(split[0], "env\0", 4) == 0)
		data->rt = exec_env(data);
	return (data->rt);
}

void	init_child(int id, t_bt *tree, t_data *data)
{
	// close_unused_pipes(id, tree, data);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	(void)tree;
	(void)data;
	(void)id;
}

void	pipe_child(char *join, char **split, t_bt *tree, t_data *data)
{
	int	id;

	id = tree->id / 2;
	if (id == 0)
	{
		if (data->fd_in[0] > 0)
			dup2(data->fd_in[0], 0);
		if (tree->right != NULL)
			dup2(data->pipes[id][1], 1);
	}
	else
	{
		dup2(data->pipes[id - 1][0], 0);
		if (tree->parent->right != NULL)
			dup2(data->pipes[id][1], 1);
	}
	if (builtin_executor_child(split, data, tree) == 0)
		return ;
	execve(join, split, data->env);
	execve(split[0], split, data->env);
	write(1, "\0", 1);
	ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", \
	split[0]);
}
