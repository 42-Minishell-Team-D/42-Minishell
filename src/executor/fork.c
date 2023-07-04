/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:28:55 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 13:17:24 by ddantas-         ###   ########.fr       */
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	(void)tree;
	(void)data;
	(void)id;
}

static void	exec_loop_2(char **split, char *tmp, int i, t_data *data)
{
	char	**paths;
	char	**paths2;

	paths = ft_split(tmp, ':');
	free(tmp);
	paths2 = (char **)ft_calloc(array_size(paths) + 1, sizeof(char *));
	while (paths[i] != NULL)
	{
		paths2[i] = ft_strjoin(paths[i], "/");
		free(paths[i++]);
	}
	free(paths);
	i = 0;
	while (paths2[i] != NULL)
	{
		data->join = ft_strjoin(paths2[i], split[0]);
		free(paths2[i++]);
		execve(data->join, split, data->env);
		free(data->join);
	}
	free(paths2);
}

static void	exec_loop(char **split, t_data *data)
{
	char	*tmp;

	tmp = ft_getenv("PATH", data->env);
	if (tmp != NULL)
		exec_loop_2(split, tmp, 0, data);
}

void	pipe_child(char **split, t_bt *tree, t_data *data)
{
	int		id;

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
	exec_loop(split, data);
	execve(split[0], split, data->env);
	write(1, "\0", 1);
	ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", \
	split[0]);
}
