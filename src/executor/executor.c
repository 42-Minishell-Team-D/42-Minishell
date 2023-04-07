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

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < get_number_of_processes(data->tree) + 1)
	{
		if (data->pipes[i][0] != 0)
			close(data->pipes[i][0]);
		if (data->pipes[i][1] != 0)
			close(data->pipes[i][1]);
		if (data->pipes != NULL)
			free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	if (data->pipes != NULL)
		free(data->pipes);
}

static void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = (int **)ft_calloc(sizeof(int *), (get_number_of_processes(data->tree) + 1));
	while (i < get_number_of_processes(data->tree) + 1)
	{
		data->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		data->pipes[i][0] = 0;
		data->pipes[i][1] = 0;
		i++;
	}
}

void	executor(t_data *data)
{
	// t_bt	*tree ;
	// t_bt	*left_tree;
	int		i = 0;
	// int		pid;

	init_pipes(data);	

	while (i < get_number_of_processes(data->tree) + 1)
		if (pipe(data->pipes[i++]) < 0)
			close_pipes(data);

	/*tree = data->tree;
	while (tree != NULL)
	{
		redirect(tree, data);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			redirect(left_tree, data);
		}
		tree = tree->right;
	}*/
	close_pipes(data);
}
