/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:09:59 by loris             #+#    #+#             */
/*   Updated: 2023/08/11 10:43:48 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static int	exists_perms(const char *path, int option)
{
	struct stat	info;

	if (option == EXISTS)
		return (stat(path, &info) == 0 && S_ISDIR(info.st_mode));
	else if (option == PERMS)
		return (access(path, R_OK | X_OK) == 0);
	return (0);
}

static void	update_pwd(t_data *data, int n)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	while (data->env[n] != NULL)
	{
		if (ft_strncmp(data->env[n], "PWD=", 4) == 0)
		{
			free(data->env[n]);
			data->env[n] = ft_strjoin("PWD=", cwd);
			break ;
		}
		n++;
	}
	n = 0;
	while (data->export[n] != NULL)
	{
		if (ft_strncmp(&data->export[n][11], "PWD=", 4) == 0)
		{
			free(data->export[n]);
			data->join = ft_strjoin("declare -x PWD=\"", cwd);
			data->export[n] = ft_strjoin(data->join, "\"\0");
			free(data->join);
			data->join = NULL;
		}
		n++;
	}
}

static void	update_oldpwd(t_data *data, int n)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	while (data->env[n] != NULL)
	{
		if (ft_strncmp(data->env[n], "OLDPWD=", 7) == 0)
		{
			free(data->env[n]);
			data->env[n] = ft_strjoin("OLDPWD=", cwd);
			break ;
		}
		n++;
	}
	n = 0;
	while (data->export[n] != NULL)
	{
		if (ft_strncmp(&data->export[n][11], "OLDPWD=", 7) == 0)
		{
			free(data->export[n]);
			data->join = ft_strjoin("declare -x OLDPWD=\"", cwd);
			data->export[n] = ft_strjoin(data->join, "\"\0");
			free(data->join);
				data->join = NULL;
		}
		n++;
	}
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
	update_oldpwd(data, 0);
	chdir(home);
	update_pwd(data, 0);
	free(home);
	return (0);
}

int	exec_cd(char **split, t_data *data)
{
	if (split[1] == NULL)
		return (if_split_null(data));
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	if (exists_perms(split[1], EXISTS) == 0)
	{
		ft_printf_fd(2, "minishell: cd: \
%s: No such file or directory\n", split[1]);
		return (1);
	}
	else if (exists_perms(split[1], PERMS) == 0)
	{
		ft_printf_fd(2, "minishell: cd: \
%s: Permission denied\n", split[1]);
		return (1);
	}
	update_oldpwd(data, 0);
	chdir(split[1]);
	update_pwd(data, 0);
	return (0);
}
