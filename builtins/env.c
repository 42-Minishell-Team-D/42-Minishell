#include "../libs/minishell.h"

int	exec_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)		// +2 because the last two elements of the environ export
    	printf("%s\n", data->env[i++]);		// are reserved for the lines and columns
	return (0);
}