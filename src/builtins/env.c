#include "../../libs/minishell.h"

int	exec_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)
    	ft_printf_fd(1, "%s\n", data->env[i++]);
	return (0);
}
