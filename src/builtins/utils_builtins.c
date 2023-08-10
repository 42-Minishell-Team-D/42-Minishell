/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:11:04 by loris             #+#    #+#             */
/*   Updated: 2023/08/10 18:08:46 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

char	*get_before_equal_sign(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

char	*get_before_equal_sign_export(char *var)
{
	char	*join;
	char	*tmp;

	join = get_before_equal_sign(var);
	if (ft_strncmp(join, "declare -x ", 11) == 0)
	{
		tmp = ft_substr(join, 11, ft_strlen(join));
		free(join);
		return (tmp);
	}
	return (join);
}
