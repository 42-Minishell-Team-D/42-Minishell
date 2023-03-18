#include "../libs/minishell.h"

void sort_export_ASCII(char **export, int size, int i, int j)
{
	// need to change functions for libft funcs
	char *temp;

	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(export[j], export[j + 1], nb_char_max(export)) > 0)
			{
				temp = export[j];
				export[j] = export[j+1];
				export[j+1] = temp;
			}
			j++;
		}
		i++;
	}

	// append "declare -x"
	// i = 0;
	// while (i < size)
	// {
	// 	ft_strlcat("declare -x", export[i++], nb_char_max(export));
	// 	printf("ok\n");
	// }
}

void print_export(t_data *data)
{
	int i;

	i = 0;
	data->export = malloc(sizeof(char *) * (array_size(data->env) + 1));
	while (i < array_size(data->env))
	{
		data->export[i] = ft_strdup(data->env[i]);
		i++;
	}
	data->export[i] = NULL;
	sort_export_ASCII(data->export, array_size(data->export), 0, 0);
	i = 0;
	while (data->export[i] != NULL)	
    	printf("%s\n", data->export[i++]);
	free(data->export);
}

int	exec_export(t_data *data, char *p)
{
	char **arg;
	int i;
	
	arg = ft_split(p + 7, ' ');
	i = 0;
	if (p[6] == '\0')	// "export    " should still work
		print_export(data);
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
