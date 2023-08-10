/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:09:59 by loris             #+#    #+#             */
/*   Updated: 2023/08/10 17:19:34 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static void	update_OLDPWD_PWD(t_data *data)
{

(void)data;
}

static int	if_split_null(t_data *data)
{
	char	*home;

	home = NULL;
	home = ft_getenv("HOME", data->env);
	if (home == NULL)
	{
		ft_printf_fd(2, "minishell: cd: HOME not set\n");
		return (1);
	}
	chdir(home);
	free(home);
	update_OLDPWD_PWD(data);
	return (0);
}

int	exec_cd(char **split, t_data *data)
{
	if (split[1] == NULL)
		return (if_split_null(data));
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(split[1]) == -1)
	{
		ft_printf_fd(2, "minishell: cd: \
%s: No such file or directory\n", split[1]);
		return (1);
	}
	update_OLDPWD_PWD(data);
	return (0);
}
