#include "../../libs/minishell.h"

static void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipes = (int **)ft_calloc(sizeof(int *), (get_number_of_processes(data->tree) - 1));
	while (i < get_number_of_processes(data->tree) - 1)
	{
		data->pipes[i] = (int *)ft_calloc(2, sizeof(int));
		data->pipes[i][0] = -1;
		data->pipes[i][1] = -1;
		i++;
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
