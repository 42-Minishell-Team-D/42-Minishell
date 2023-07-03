/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:37:02 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/03 23:08:39 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	lexical_analyzer(t_data *data, t_parser *p, char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	while (*ptr != '\0')
	{
		if (*ptr == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (*ptr == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (*ptr == '$' && !p->in_single)
			ptr = handle_dollar_anal(ptr, p, data);
		if (!p->in_double && !p->in_single \
		&& is_new_token(*ptr, *(ptr + 1)) > 1)
			ptr = handle_special_char_anal(ptr, p, data);
		else if (*ptr != '\0')
		{
			if (is_new_token(*ptr, *(ptr + 1)) > 0)
			{
				p->token[p->n++] = *ptr;
				ptr++;
			}
			p->token[p->n++] = *ptr;
			ptr++;
		}
	}
	if (p->n != 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	data->tokens[p->i++] = NULL;
	return (0);
}
