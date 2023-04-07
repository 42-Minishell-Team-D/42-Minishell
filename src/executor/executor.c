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
	printf("Number of processes: %d\n", count);
	return (count);
}

void	executor(t_data *data)
{
	t_bt	*tree ;
	t_bt	*left_tree;
	int		pipes[get_number_of_processes(data->tree)][2];

	data->pipes = (int **)pipes;
	// data->pipes = malloc(sizeof(int) * (get_number_of_processes(data->tree) + 1));
	// data->pipes = malloc(sizeof(int) * (get_number_of_processes(data->tree) + 1));
	// printf("%i\n", data->pipes[0][0]);
	
	tree = data->tree;
	while (tree != NULL)
	{
		redirect(tree, data);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			redirect(left_tree, data);
		}
		tree = tree->right;
	}
}
