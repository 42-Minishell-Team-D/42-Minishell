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

void free_array(char ***array) {
    int i = 0;
    while ((*array)[i] != NULL) {
        if ((*array)[i] != NULL) {
            ft_bzero((*array)[i], ft_strlen((*array)[i]));
            free((*array)[i]);
        }
        (*array)[i++] = NULL;
    }
    free(*array);
    *array = NULL;
}

static void update_env(char *var, t_data *data) {
    int i = 0;
    char **ret = NULL;
    ret = malloc(sizeof(char *) * (array_size(data->env) + 2));
    if (!ret) {
        // Handle allocation failure
        // free any previously allocated memory
        // and return an appropriate error value or exit the program
    }
    while (data->env[i] != NULL) {
        ret[i] = ft_strdup(data->env[i]);
        i++;
    }
    ret[i] = ft_strdup(var);
    ret[i + 1] = NULL;
    free_array(&data->env);
    data->env = ret;  // Assign ret to data->env
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
					update_env(split[i], data);
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