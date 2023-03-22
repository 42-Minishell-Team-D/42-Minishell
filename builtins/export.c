#include "../libs/minishell.h"

static void quote(char *export, int i, int j)
{
	char temp[ft_strlen(export) + 2];

	while (export[i] && export[i] != '=')
		temp[j++] = export[i++];
	if (export[i])
	{
		temp[j++] = export[i++];
		temp[j++] = '"';
		while (export[i])
			temp[j++] = export[i++];
		temp[j++] = '"';
		temp[j++] = '\0';
		free(export);
		export = ft_strdup(temp);
	}
}

static void sort_export_ASCII(char **export, int size, int i, int j)
{
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

	i = 0;
	while (i < size)
	{
		export[i] = ft_strjoin("declare -x ", export[i]);
		quote(export[i++], 0, 0);
	}
}

static void print_export(t_data *data)
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
