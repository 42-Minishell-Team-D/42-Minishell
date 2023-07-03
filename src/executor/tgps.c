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

void	close_unused_pipes(int id, t_bt *tree, t_data *data)
{
	int		n;
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
}

int	init_executor(t_data *data)
{
	int	i;

	i = 0;
	init_pipes(data);
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
