/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:11:11 by loris             #+#    #+#             */
/*   Updated: 2023/07/03 22:35:53 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static void	update_env(char *var, t_data *data, char *join, int i)
{
	data->env = ft_realloc(data->env, sizeof(char *) * \
	(array_size(data->env) + 2));
	if (data->env == NULL)
		return ;
	data->env[array_size(data->env) + 1] = NULL;
	while (data->env[i] != NULL)
	{
		data->tmp = get_before_equal_sign(data->env[i]);
		join = get_before_equal_sign(var);
		if (ft_strncmp(data->tmp, join, get_biggest_len(data->tmp, join)) == 0)
		{
			free(data->tmp);
			free(join);
			free(data->env[i]);
			data->env[i] = ft_strdup(var);
			return ;
		}
		free(data->tmp);
		free(join);
		i++;
	}
	free(data->env[i]);
	data->env[i] = ft_strjoin(var, "\0");
}

// static 

static void	update_export(char *var, t_data *data)
{
	int		i;
	char	*join;
	char	*tmp;
	int		b;

	i = 0;
	b = 0;
	while (data->export[i] != NULL)
	{
		join = get_before_equal_sign_export(data->export[i]);
		tmp = get_before_equal_sign(var);
		if (ft_strncmp(join, tmp, get_biggest_len(join, tmp)) == 0)
		{
			free(join);
			free(tmp);
			b = 1;
			break ;
		}
		free(join);
		free(tmp);
		i++;
	}
	if (b == 0)
	{
		data->export = ft_realloc(data->export, sizeof(char *) \
		* (array_size(data->export) + 2));
		if (data->export == NULL)
			return ;
		data->export[array_size(data->export) + 1] = NULL;
	}
	free(data->export[i]);
	data->export[i] = ft_strdup(var);
	tmp = ft_strjoin("declare -x ", data->export[i]);
	free(data->export[i]);
	data->export[i] = ft_strjoin(tmp, "\0");
	free(tmp);
	if (is_equal_sign(var) == 0)
		return ;
	tmp = quote(data->export[i], 0, 0);
	free(data->export[i]);
	data->export[i] = ft_strjoin(tmp, "\0");
	free(tmp);
}

int	exec_export(char **split, t_data *data, t_bt *tree)
{
	int	i;

	i = 1;
	if (split[1] == NULL)
		print_export(data);
	else if (tree->parent == NULL && tree->right == NULL && tree->left == NULL)
	{
		while (split[i] != NULL)
		{
			if (check_variable_name(split[i]) == 0)
				printf("minishell: export: `%s': not a valid identifier\n", \
				split[i]);
			else
			{
				if (is_equal_sign(split[i]) == 1)
					update_env(split[i], data, NULL, i);
				update_export(split[i], data);
			}
			i++;
		}
	}
	return (0);
}
