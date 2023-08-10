/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:09:59 by loris             #+#    #+#             */
/*   Updated: 2023/07/04 19:21:58 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	exec_cd(char **split)
{
	char	*home;

	home = NULL;
	if (split[1] == NULL)
	{
		home = getenv("HOME");
		chdir(home);
		free(home);
		return (0);

	}
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(split[1]) == -1)
	{
		ft_printf_fd(2, "minishell: cd: \
%s: No such file or directory\n", split[1]);
		return (1);
	}
	return (0);
}
