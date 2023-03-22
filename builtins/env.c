#include "../libs/minishell.h"

int	exec_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)
    	printf("%s\n", data->env[i++]);
	return (0);
}