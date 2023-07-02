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
	// ft_printf_fd(1, "Number of processes: %d\n", count);
	return (count);
}

void	close_unused_pipes(int id, t_bt *tree, t_data *data)
{
	int		n;
	// t_bt	*left_tree;
	int		reading;
	int		writing;

	n = 0;
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
	{
		reading = data->pipes[id - 1][0];
		if (tree->parent->right != NULL)
		{
			writing = data->pipes[id][1];
			// ft_printf_fd(1, "id %d read_check %d | write_check %d\n", id, data->pipes[id - 1][0], data->pipes[id][1]);
		}
		else
		{
			// ft_printf_fd(1, "id %d read_check %d\n", id, data->pipes[id - 1][0]);
			writing = -1;
		}
		while (n < id)
		{
			if (reading != data->pipes[n][0])
			{
				// ft_printf_fd(1, "id: %d 1Close pipe %d\n", id, data->pipes[n][0]);
				close(data->pipes[n][0]);
			}
			if (writing != data->pipes[n][1])
			{
				// ft_printf_fd(1, "id: %d 2Close pipe %d\n", id, data->pipes[n][1]);
				close(data->pipes[n][1]);
			}
			n++;
		}
	}
}

			// ft_printf_fd(1, "id: %d 1Close pipe %d\n", id, data->pipes[n][1]);
			// if (close(data->pipes[n++][1]) == -1)
				// ft_printf_fd(1, "id: %d Close failed pipe[%d][1]\n", id, n);
			/*if (n < id)
			{
				left_tree = left_tree->parent->left;
				if (left_tree->right != NULL)
				{
					ft_printf_fd(1, "id: %d 2Close pipe %d\n", id, data->pipes[n][0]);
					if (close(data->pipes[n][0]) == -1)
						ft_printf_fd(1, "id: %d Close failed pipe[%d][0]\n", id, n);
				}
			}*/

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

void	executor(t_data *data)
{
	t_bt	*tree;
	pid_t	fork_id = 0;
	int		status;

	tree = data->tree;
	if (init_executor(data))
		return ;
	if (ft_strncmp(tree->args, "\0", 1) != 0)
		redirect_pipe(&fork_id, tree, data);
	else
		write(data->pipes[0][1], "\0", 1);
	if (data->fd_in[0] > 0)
		close(data->fd_in[0]);
	tree = tree->right;
	while (tree != NULL)
	{
		if (is_new_token(tree->args[0], tree->args[1]) == GREAT)
			tree = redirect_great(tree->left, data, GREAT);
		if (is_new_token(tree->args[0], tree->args[1]) == GREATGREAT)
			tree = redirect_great(tree->left, data, GREATGREAT);
		if (is_new_token(tree->args[0], tree->args[1]) == PIPE)
			redirect_pipe(&fork_id, tree->left, data);
		tree = tree->right;
	}
	waitpid(fork_id, &status, 0);
	// while (child_pid > 0)
	// 	child_pid = waitpid(fork_id, &status, 0);
	data->rt = WEXITSTATUS(status);
	close_free_pipes(data);
}
