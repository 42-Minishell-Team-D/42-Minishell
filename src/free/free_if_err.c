/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_if_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:34:20 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/03 22:34:20 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

void	free_if_err(char **var, int exit_code)
{
	if (var)
		free(var);
	ft_printf_fd(2, "minishell: Error, exit code :%d\n", exit_code);
	exit(exit_code);
}
