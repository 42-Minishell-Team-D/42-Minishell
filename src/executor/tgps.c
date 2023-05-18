#include "../../libs/minishell.h"

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

int	init_executor(t_data *data)
{
	int	i;

	i = 0;
	data->pids = malloc(sizeof(int) * (get_number_of_processes(data->tree)));
	init_pipes(data);
	while (i < get_number_of_processes(data->tree) + 1)
		if (pipe(data->pipes[i++]) < 0)
		{
			close_free_pipes_pids(data);
			return (1);
		}
	return (0);
}
