/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:11:53 by loris             #+#    #+#             */
/*   Updated: 2023/08/10 18:08:46 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

void	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (array_size(data->export) > i && data->export[i] \
	!= NULL && data->export[i][0] != '\0')
		ft_printf_fd(1, "%s\n", data->export[i++]);
}

int	check_variable_name(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (0);
	while (var[i] != '\0' && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_equal_sign(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	if (var[i] == '\0')
		return (0);
	return (1);
}
