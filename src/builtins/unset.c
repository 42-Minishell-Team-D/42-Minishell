#include "../../libs/minishell.h"

void	place_all_strings(char **s)
{
	int	i;

	i = 0;
	while (s[i + 1] != NULL)
	{
		s[i] = s[i + 1];
		i++;
	}
	s[i] = NULL;
}

void	remove_var_from_env(char *var, char **env)
{
	int		i;
	char	*var_before;
	char	*env_before;

	i = 0;
	var_before = get_before_equal_sign(var);
	while (env[i] != NULL)
	{
		env_before = get_before_equal_sign(env[i]);
		if (ft_strncmp(env_before, var_before, get_biggest_len(env_before, var_before)) == 0)
		{
			free(env[i]);
			place_all_strings(env + i);
			return ;
		}
		i++;
	}
}

void	remove_var_from_export(char *var, char **export)
{
	int		i;
	char	*var_before;
	char	*export_before;

	i = 0;
	var_before = get_before_equal_sign(var);
	while (export[i] != NULL)
	{
		export_before = get_before_equal_sign_export(export[i]);
		if (ft_strncmp(export_before, var_before, get_biggest_len(export_before, var_before)) == 0)
		{
			free(export[i]);
			place_all_strings(export + i);
			return ;
		}
		i++;
	}
}

int	exec_unset(char **split, t_data *data)
{
	int	i;

	i = 1;
	while (split[i] != NULL)
	{
		remove_var_from_env(split[i], data->env);
		remove_var_from_export(split[i], data->export);
		i++;
	}
	// exec_env(data);
	return (0);
}

// should accept any arguments
// should remove the variable from the environment and the export list
// should return 0
