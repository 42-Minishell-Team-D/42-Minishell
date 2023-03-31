#include "../../libs/minishell.h"

int	exec_unset(t_data *data, char *p)
{
	char **arg;
	int i;
	
	arg = ft_split(p + 6, ' ');
	i = 0;
	if (p[5] == '\0')
		return (0);
	if (p[5] != ' ')
		printf("minishell: %s command not found :\n", p);
	while (arg[i] != NULL)
	{
		data->env[array_size(data->env) + 1] = NULL;
		data->env[search_var(data->env)] = arg[i];
		i++;
	}

    return (0);
}
