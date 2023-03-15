#include "../libs/minishell.h"

int	exec_env(t_data *data)
{
	int i;

	i = 0;
	while (data->env[i] != NULL)		// +2 because the last two elements of the environ export
    	printf("%s\n", data->env[i++]);		// are reserved for the lines and columns
	return (0);
}

char **sort_export_ASCII(char **export, int size, int i, int j)
{
	// need to change functions for libft funcs
	// fixing the logic. need to allocated memory with malloc for both env and export
	char temp[nb_char_max(export)];

	while(i < size)
	{
    	while(j < size - 1 - i)
		{
     		if(strcmp(export[j], export[j+1]) > 0)
			{
				//swap export[j] and export[j+1]
				strcpy(temp, export[j]);
				strcpy(export[j], export[j + 1]);
				strcpy(export[j + 1], temp);
    		}
			j++;
    	}
		i++;
	}
	// append "declare -x"
	// i = 0;
	// while (i < size)
	// 	strcat("declare -x", export[i++]);

	return (export);
}

void print_export(char **env)
{
	int i;
	char *export[array_size(env)];
	char **export2;

	i = 0;
	// clone env into export
	while (env[i] != NULL)
	{
		export[i] = env[i];
		i++;
	}
	export[i] = NULL;
	export2 = sort_export_ASCII(export, array_size(export), 0, 0);

	i = 0;
	while (export2[i] != NULL)	
    	printf("%s\n", export2[i++]);
}

int	exec_export(t_data *data, char *p)
{
	char **arg;
	int i;
	
	arg = ft_split(p + 7, ' ');
	i = 0;
	if (p[6] == '\0')	// "export    " should still work
		print_export(data->env);
	else if (p[6] != ' ')
		printf("minishell: %s command not found :\n", p);
	else
		while (arg[i] != NULL)
		{
			data->env[array_size(data->env) + 1] = NULL;
			data->env[array_size(data->env)] = arg[i];
			i++;
		}
    return (0);
}

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