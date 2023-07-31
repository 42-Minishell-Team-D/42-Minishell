/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:28:46 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 18:27:00 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	get_number_of_processes(t_bt *tree)
{
	int		count;
	t_bt	*left_tree;

	count = 0;
	count++;
	while (tree != NULL)
	{
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			while (left_tree != NULL)
			{
				count++;
				left_tree = left_tree->right;
			}
		}
		left_tree = tree->left;
		tree = tree->right;
	}
	return (count);
}

void	close_free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < get_number_of_processes(data->tree) - 1)
	{
		if (data->pipes[i][0] != 0 && data->pipes[i][0] != -1)
			close(data->pipes[i][0]);
		if (data->pipes[i][1] != 0 && data->pipes[i][1] != -1)
			close(data->pipes[i][1]);
		if (data->pipes[i] != NULL)
			free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	if (data->pipes != NULL)
		free(data->pipes);
	data->pipes = NULL;
}

static void	finish_executor(t_data *data)
{
	int	status;

	status = 0;
	while (data->childs_pid[data->n] >= 0)
		waitpid(data->childs_pid[data->n++], &status, 0);
	data->rt = WEXITSTATUS(status);
	init_sa(data->sa, data->sb);
	close_free_pipes(data);
}

void	executor(t_data *data)
{
	t_bt	*tree;

	tree = data->tree;
	if (init_executor(data))
		return ;
	if (ft_strncmp(tree->args, "\0", 1) != 0)
		redirect_pipe(tree, data);
	else
		write(data->pipes[0][1], "\0", 1);
	if (data->fd_in[0] > 0)
		close(data->fd_in[0]);
	tree = tree->right;
	while (tree != NULL)
	{
		if (is_new_token(tree->args[0], tree->args[1]) == GREAT)
			tree = redirect_great(tree->left, data, GREAT, 0);
		if (is_new_token(tree->args[0], tree->args[1]) == GREATGREAT)
			tree = redirect_great(tree->left, data, GREATGREAT, 0);
		if (is_new_token(tree->args[0], tree->args[1]) == PIPE)
			redirect_pipe(tree->left, data);
		tree = tree->right;
	}
	finish_executor(data);
}
