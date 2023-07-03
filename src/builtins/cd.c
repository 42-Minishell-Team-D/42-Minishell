/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:09:59 by loris             #+#    #+#             */
/*   Updated: 2023/07/03 22:10:00 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	exec_cd(char **split)
{
	if (split[1] == NULL)
		return (chdir(getenv("HOME")));
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(split[1]) == -1)
	{
		ft_printf_fd(2, "minishell: cd: \
%s: No such file or directory\n", split[1]);
	}
	return (0);
}
