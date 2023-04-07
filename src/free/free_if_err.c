#include "../../libs/minishell.h"

void	free_if_err(t_data *data, int exit_code)
{
	if (data->env)
		free(data->env);
	ft_printf_fd(2, "minishell: Error, exit code :%d\n", exit_code);
	exit(exit_code);
}
