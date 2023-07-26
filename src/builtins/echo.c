/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:10:07 by loris             #+#    #+#             */
/*   Updated: 2023/07/03 22:10:08 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int option_checker(char **split, int *n)
{
	int	i;
	int ret;

	ret = 0;
	(*n) = 1;

	if (ft_strncmp(split[1], "-", 1) != 0)
		return (0);
	while (split[*n] != NULL && ft_strncmp(split[*n], "-", 1) == 0)
	{
		i = 1;
		while (split[*n][i] != '\0')
		{
			if (split[*n][i] == 'n')
				ret = 1;
			else if (split[*n][i] != 'n')
				return (0);
			i++;
		}
		(*n)++;
	}
	return (ret);
}

int	exec_echo(char **split)
{
	int	n;
	int	dash;

	if (split[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	
	dash = option_checker(split, &n);
	while (split[n] != NULL)
	{
		if (split[n + 1] != NULL)
			ft_printf_fd(1, "%s ", split[n++]);
		else
		{
			ft_printf_fd(1, "%s", split[n++]);
			break ;
		}
	}
	if (dash == 0)
		ft_printf_fd(1, "\n");
	return (0);	
}

