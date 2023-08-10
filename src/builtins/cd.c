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

static int	exists_perms(const char *path, int option)
{
	struct stat	info;

	if (option == EXISTS)
		return (stat(path, &info) == 0 && S_ISDIR(info.st_mode));
	else if (option == PERMS)
		return (access(path, R_OK | X_OK) == 0);
	return (0);
}

static void	update_pwd(t_data *data, char *next_dir)
{
	int		n;
	char	pwd[PATH_MAX];

	n = 0;
	while (data->env[n] != NULL)
	{
		if (ft_strncmp(data->env[n], "PWD=", 4) == 0)
		{
			if (data->env[n] != NULL)
				free(data->env[n]);
			data->env[n] = NULL;
			// exit(1);
			chdir(next_dir);
			getcwd(pwd, sizeof(pwd));
			data->env[n] = ft_strjoin("PWD=", pwd);
			break ;
		}
		n++;
	}
}

static void	update_oldpwd(t_data *data)
{
	int		n;
	char	pwd[PATH_MAX];

	n = 0;
	while (data->env[n] != NULL)
	{
		if (ft_strncmp(data->env[n], "OLDPWD=", 7) == 0)
		{
			if (data->env[n] != NULL)
				free(data->env[n]);
			data->env[n] = NULL;
			getcwd(pwd, sizeof(pwd));
			data->env[n] = ft_strjoin("OLDPWD=", pwd);
			break ;
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
	update_oldpwd(data);
	update_pwd(data, home);
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
	update_oldpwd(data);
	update_pwd(data, split[1]);
	return (0);
}
