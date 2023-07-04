/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:23:22 by lpenelon          #+#    #+#             */
/*   Updated: 2023/07/04 13:57:09 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

char	*quote(char *export, int i, int j)
{
	char	*temp;

	temp = (char *)ft_calloc(ft_strlen(export) + 3, sizeof(char *));
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
	free(temp);
	return (export);
}

static void	sort_export_ascii2(int i, int size, char **export)
{
	int		j;
	char	*temp;

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
}

static void	sort_export_ascii(char **export, int size, int i)
{
	char	*join;

	while (i < size)
	{
		sort_export_ascii2(i, size, export);
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
	sort_export_ascii(data->export, array_size(data->export), 0);
}
