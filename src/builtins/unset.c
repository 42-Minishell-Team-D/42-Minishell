/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:10:40 by loris             #+#    #+#             */
/*   Updated: 2023/07/03 22:10:41 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_strncmp(env_before, var_before,
				get_biggest_len(env_before, var_before)) == 0)
		{
			free(env[i]);
			place_all_strings(env + i);
			free(env_before);
			free(var_before);
			return ;
		}
		free(env_before);
		i++;
	}
	free(var_before);
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
		if (ft_strncmp(export_before, var_before,
				get_biggest_len(export_before, var_before)) == 0)
		{
			free(export[i]);
			free(var_before);
			var_before = NULL;
			free(export_before);
			place_all_strings(export + i);
			return ;
		}
		free(export_before);
		i++;
	}
	if (var_before != NULL)
		free(var_before);
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
	return (0);
}
