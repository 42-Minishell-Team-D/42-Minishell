/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:10:11 by loris             #+#    #+#             */
/*   Updated: 2023/07/04 11:59:22 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	exec_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
		ft_printf_fd(1, "%s\n", data->env[i++]);
	return (0);
}
