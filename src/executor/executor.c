#include "../../libs/minishell.h"

int		get_number_of_processes(t_bt *tree)
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

void	close_unused_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < get_number_of_processes(data->tree) + 1)
	{
		if (j != i)
		{
			if (data->pipes[j][0] != 0)
				if (close(data->pipes[j][0]) == -1)
					printf("Close failed pipe[%d][0]\n", j);
			if (data->pipes[j][1] != 0)
				if (close(data->pipes[j][1]) == -1)
					printf("Close failed pipe[%d][1]\n", j);
		}
		j++;
	}
}

void	close_free_pipes_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < get_number_of_processes(data->tree) + 1)
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
	if (data->pids != NULL)
		free(data->pids);
	data->pipes = NULL;
	data->pids = NULL;
}

void	executor(t_data *data)
{
	t_bt	*tree;
	int		rd;
	int		last_id;
	char	buf[1024];

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
			exit(99999);
	}
	wait(NULL);
	data->rt = WEXITSTATUS(data->rt);
	// ft_printf_fd(1, "parent reading from %d\n", data->pipes[last_id / 2][0]);
	write(data->pipes[last_id / 2][1], "\0", 1);
	rd = read(data->pipes[last_id / 2][0], buf, sizeof(buf));
	// ft_printf_fd(1, "rd: %d\n", rd);	
	while (rd > 0)
	{
		buf[rd] = '\0';
		write(1, buf, rd);
		if (rd < 1024)
			break ;
		rd = read(data->pipes[last_id / 2][0], buf, sizeof(buf));
	}
	close_free_pipes_pids(data);
}
