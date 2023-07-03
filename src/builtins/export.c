#include "../../libs/minishell.h"

static void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->export[i] != NULL && data->export[i][0] != '\0')
		ft_printf_fd(1, "%s\n", data->export[i++]);
}

static int	check_variable_name(char *var)
{
	int	i;

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

static int	is_equal_sign(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	if (var[i] == '\0')
		return (0);
	return (1);
}

static void	update_env(char *var, t_data *data)
{
	int		i;
	char	*tmp;
	char	*join;

	i = 0;
	data->env = ft_realloc(data->env, sizeof(char *) * \
	(array_size(data->env) + 2));
	if (data->env == NULL)
		return ;
	data->env[array_size(data->env) + 1] = NULL;
	while (data->env[i] != NULL)
	{
		tmp = get_before_equal_sign(data->env[i]);
		join = get_before_equal_sign(var);
		if (ft_strncmp(tmp, join, get_biggest_len(tmp, join)) == 0)
		{
			free(tmp);
			free(join);
			free(data->env[i]);
			data->env[i] = ft_strdup(var);
			return ;
		}
		free(tmp);
		free(join);
		i++;
	}
	join = ft_strjoin(var, "\0");
	free(data->env[i]);
	data->env[i] = ft_strjoin(join, "\0");
	free(join);
}

static void update_export(char *var, t_data *data)
{
	int		i;
	char	*tmp;
	char	*join;

	i = 0;
	data->export = ft_realloc(data->export, sizeof(char *) * (array_size(data->export) + 2));
	if (data->export == NULL)
		return ;
	data->export[array_size(data->export) + 1] = NULL;
	while (data->export[i] != NULL)
	{
		tmp = get_before_equal_sign_export(data->export[i]);
		join = get_before_equal_sign(var);
		if (ft_strncmp(tmp, join, get_biggest_len(tmp, join)) == 0)
		{
			free(tmp);
			free(join);
			free(data->export[i]);
			break ;
		}
		free(tmp);
		free(join);
		i++;
	}
	data->export[i] = ft_strdup(var);
	join = ft_strjoin("declare -x ", data->export[i]);
	free(data->export[i]);
	data->export[i] = ft_strjoin(join, "\0");
	free(join);
	if (is_equal_sign(var) == 0)
		return ;
	join = quote(data->export[i], 0, 0);
	free(data->export[i]);
	data->export[i] = ft_strjoin(join, "\0");
	free(join);
}

int	exec_export(char **split, t_data *data)
{
	int	i;

	i = 1;
	if (split[1] == NULL)
		print_export(data);
	else
	{
		while (split[i] != NULL)
		{
			if (check_variable_name(split[i]) == 0)
				printf("minishell: export: `%s': not a valid identifier\n", \
				split[i]);
			else
			{
				if (is_equal_sign(split[i]) == 1)
					update_env(split[i], data);
				update_export(split[i], data);
			}
			i++;
		}
	}
    return (0);
}
