#include "../../libs/minishell.h"

void	free_if_err(t_data *data)
{
	if (data->env)
		free(data->env);
}