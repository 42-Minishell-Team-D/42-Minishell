/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:23:22 by lpenelon          #+#    #+#             */
/*   Updated: 2023/07/04 13:39:28 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	init_env(t_data *data, int i)
{
	extern char	**environ;

	data->env = NULL;
	data->env = malloc(sizeof(char *) * (array_size(environ) + 1));
	if (!data->env)
		free_if_err(data->env, 1);
	while (i < array_size(environ) - 2)
	{
		data->env[i] = ft_strjoin(environ[i], "\0");
		i++;
	}
	data->env[i] = NULL;
}

char	*quote(char *export, int i, int j)
{
	char	temp[ft_strlen(export) + 3];

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
		export = ft_strdup(temp);
	}
	return (export);
}

static void	sort_export_ascii(char **export, int size, int i, int j)
{
	char	*temp;
	char	*join;

	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(export[j], export[j + 1], nb_char_max(export)) > 0)
			{
				temp = export[j];
				export[j] = export[j + 1];
				export[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		join = ft_strjoin("declare -x ", export[i]);
		free (export[i]);
		export[i++] = quote(join, 0, 0);
		free(join);
	}
}

void	init_export(t_data *data, int i)
{
	extern char	**environ;

	data->export = NULL;
	data->export = malloc(sizeof(char *) * (array_size(data->env) + 1));
	if (!data->export)
		free_if_err(data->export, 1);
	while (i < array_size(data->env))
	{
		data->export[i] = ft_strjoin(data->env[i], "\0");
		i++;
	}
	data->export[i] = NULL;
	sort_export_ascii(data->export, array_size(data->export), 0, 0);
}
