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
	// printf("Number of processes: %d\n", count);
	return (count);
}

		// if (tree->right != NULL)
		// {
		// 	ft_printf_fd(1, "Close pipe %d\n", data->pipes[n][0]);
		// 	close(data->pipes[n][0]);
		// }
		// while (tree->right != NULL && n <= get_number_of_processes(data->tree) - 1)
		// {
		// 	if (close(data->pipes[n][1]) == 0)
		// 		ft_printf_fd(1, "1Close pipe %d\n", data->pipes[n][1]);
		// 	else
		// 		ft_printf_fd(1, "2Close failed pipe %d\n", data->pipes[n][1]);
				
		// 	if (close(data->pipes[n + 1][0]) == 0)
		// 		ft_printf_fd(1, "3Close pipe %d\n", data->pipes[n][0]);
		// 	else
		// 		ft_printf_fd(1, "4Close failed pipe %d\n", data->pipes[n][0]);
		// 	n++;
		// }

void	close_unused_pipes(int id, t_bt *tree, t_data *data)
{
	int	n;

	n = 0;
	if (id == 0)
	{
		if (tree->right != NULL)
			close (data->pipes[id][0]);
		while (++id < get_number_of_processes(data->tree) - 1)
		{
			close(data->pipes[id][0]);
			close(data->pipes[id][1]);
		}
	}
	else
	{
		/*while (n < id)
		{
			printf("Close pipe %d\n", data->pipes[n][1]);
			close(data->pipes[n++][1]);
			printf("Close pipe %d\n", data->pipes[n - 1][0]);
			close(data->pipes[n][0]);
		}*/
	}
}

void	close_free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < get_number_of_processes(data->tree) - 1)
	{
		if (data->pipes[i][0] != 0)
			if (close(data->pipes[i][0]) == -1)
				printf("Close failed pipe[%d][0]\n", i);
		if (data->pipes[i][1] != 0)
			if (close(data->pipes[i][1]) == -1)
				printf("Close failed pipe[%d][1]\n", i);
		if (data->pipes != NULL)
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
	int		rd;
	int		last_id;
	pid_t	child_pid;
	int		status;

	tree = data->tree;
	if (init_executor(data))
		return ;
	if (ft_strncmp(tree->args, "\0", 1) != 0)
		redirect_pipe(tree, data);
	else
		write(data->pipes[0][1], "\0", 1);
	rd = 0;
	last_id = tree->id;
	tree = tree->right;
	int anti_bomb = 0;
	while (tree != NULL)
	{
		last_id = tree->id;
		if (is_new_token(tree->args[0], tree->args[1]) == GREAT)
			tree = redirect_great(tree->left, data, GREAT);
		if (is_new_token(tree->args[0], tree->args[1]) == GREATGREAT)
			tree = redirect_great(tree->left, data, GREATGREAT);
		if (is_new_token(tree->args[0], tree->args[1]) == PIPE)
			redirect_pipe(tree->left, data);
		tree = tree->right;
		if (anti_bomb++ > 3) // Anti fork bomb mechanism
			exit(255);
	}
	child_pid = wait(&status);
	while (child_pid > 0)
		child_pid = wait(&status);
	data->rt = WEXITSTATUS(status);
	// ft_printf_fd(1, "parent reading from %d\n", data->pipes[last_id / 2][0]);
	close_free_pipes(data);
}
