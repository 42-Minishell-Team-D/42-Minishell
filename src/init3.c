/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:08:08 by lpenelon          #+#    #+#             */
/*   Updated: 2023/08/11 10:09:28 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

static int	get_after_equal_sign(char *var)
{
	int		i;
	char	*value;
	int		ret;

	i = 0;
	ret = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	value = ft_substr(var, i + 1, 500);
	ret = ft_atoi(value);
	free(value);
	return (ret);
}

static void	increment_shlvl(t_data *data)
{
	int	i;
	int	value;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
		{
			value = get_after_equal_sign(data->env[i]);
			if (data->env[i] != NULL)
				free(data->env[i]);
			data->itoa = ft_itoa(value + 1);
			data->env[i] = ft_strjoin("SHLVL=", data->itoa);
			free(data->itoa);
			break ;
		}
		i++;
	}
}

static void	update_shlvl(t_data *data)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (data->env[i] != NULL && b == 0)
	{
		if (ft_strncmp(data->env[i], "SHLVL=", 6) == 0)
			b = 1;
		i++;
	}
	if (b == 0)
		data->env[array_size(data->env)] = ft_strdup("SHLVL=0");
	increment_shlvl(data);
}

void	init_env(t_data *data, int i)
{
	extern char	**environ;

	data->env = NULL;
	data->env = calloc(sizeof(char *), (array_size(environ) + 2));
	if (!data->env)
		free_if_err(data->env, 1);
	while (i < array_size(environ))
	{
		data->env[i] = ft_strjoin(environ[i], "\0");
		i++;
	}
	update_shlvl(data);
}
