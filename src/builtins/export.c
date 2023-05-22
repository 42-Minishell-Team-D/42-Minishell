#include "../../libs/minishell.h"

static void print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->export[i] != NULL)	
    	ft_printf_fd(2, "%s\n", data->export[i++]);
}

static int check_variable_name(char *var)
{
	int i;

	i = 0;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (0);
	while (var[i] != '\0' && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char *get_after_equal_sign(char *var)
{
	int i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	if (var[i] == '\0')
		return (NULL);
	return (var + i + 1);
}

static char **update_env(char *var, t_data *data)
{
	int		i;
	char	**ret;

	i = 0;
	ret = NULL;
	ret = malloc(sizeof(char *) * (array_size(data->env) + 1));
	if (!ret)
		free_if_err(ret, 1);
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0)	// if variable already exists in env
		{
			data->env = realloc(data->env, sizeof(char *) * (array_size(data->env) + 1));
			data->env[i] = ft_strdup(var);
			return data->env;
		}
		i++;
	}
	printf("%i\n", array_size(data->env));
	printf("i = %i\n", i);
	data->env = ft_realloc(data->env, sizeof(char *) * (i + 2));
	data->env[i] = ft_strdup(var);
	printf("data->env[i] = %s\n", data->env[i]);
	data->env[i + 1] = NULL;
	exec_env(data);
	return (data->env);
}

// static void update_export(char *var, t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (data->export[i] != NULL)
// 	{
// 		if (ft_strncmp(data->export[i], var, ft_strlen(var)) == 0)
// 		{
// 			data->export[i] = var;
// 			return ;
// 		}
// 		i++;
// 	}
// 	data->export[i] = var;
// 	data->export[i + 1] = NULL;
// }


int	exec_export(char **split, t_data *data)
{
	int i;
	
	i = 1;
	if (split[1] == NULL)
		print_export(data);
	else
	{
		while (split[i] != NULL)
		{
			if (check_variable_name(split[i]) == 0)
				printf("minishell: export: `%s': not a valid identifier\n", split[i]);
			else
				// add variable(s) to the export and env
				// if (variable already exists in env) --> update it
				// else --> add it
				if (get_after_equal_sign(split[i]) != NULL)
				{
					printf("%s\n", get_after_equal_sign(split[i]));
					data->env = update_env(split[i], data);
					// update_export(split[i], data);
				}
				// else
					// update_export(split[i], data);
			i++;
		}
	}
    return (0);
}

// Bash variable names can contain latin letters, digits and underscores (_). Hyphens (-) are not allowed
// can be any lowercase or uppercase letter, digit, or the underscore character
// can't start with a digit

// export ok															--> initialise 'ok' without a value		--> ok
// export ok =1 --> "minishell: export: `=1': not a valid identifier"	--> initialise 'ok' without a value		--> ok
// export ok= 1 --> "minishell: export: `1': not a valid identifier"	--> initialise 'ok' with a value NULL	--> ok=
// export ok=1  														--> initialise 'ok' with a value		--> ok="1"
// export ok==  														--> initialise 'ok' with a value		--> ok="="

// two cases:
// intialise <var> without a value --> only add to export
// intialise <var> with a value --> add to export and env

// unset <variable name> etc... --> remove variable from env