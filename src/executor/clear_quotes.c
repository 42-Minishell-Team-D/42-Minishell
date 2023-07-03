/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:29:24 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/03 22:29:25 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

char	**clear_quotes(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '\'' || split[i][0] == '"')
		{
			split[i][ft_strlen(split[i]) - 1] = '\0';
			delete_char_filter(&split[i][0]);
		}
		i++;
	}
	return (split);
}
