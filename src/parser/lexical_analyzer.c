/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:37:02 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 17:04:41 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

char	*hda_join(char *ptr, int itoa, t_parser *p, t_data *data)
{
	data->itoa = ft_itoa(itoa);
	p->char_temp = ft_strjoin(p->token, data->itoa);
	ft_strlcpy(p->token, p->char_temp, ft_strlen(p->char_temp) + 1);
	p->n += ft_strlen(data->itoa);
	free(data->itoa);
	free(p->char_temp);
	ptr++;
	return (ptr);
}

char	*hda_quotes(char *ptr, t_parser *p)
{
	char	temp;

	temp = *ptr;
	ptr++;
	while (*ptr != '\0' && *ptr != temp)
	{
		p->token[p->n++] = *ptr;
		ptr++;
	}
	return (++ptr);
}

int	lexical_analyzer(t_data *data, t_parser *p, char *ptr)
{
	while (*ptr == ' ')
		ptr++;
	while (*ptr != '\0')
	{
		quote_updater(ptr, p);
		if (*ptr == '$' && !p->in_single)
			ptr = handle_dollar_anal(ptr, p, data);
		if (*ptr == '\0')
			break ;
		if (!p->in_double && !p->in_single \
		&& is_new_token(*ptr, *(ptr + 1)) > 1)
			ptr = handle_special_char_anal(ptr, p, data);
		else if (*ptr != '\0')
		{
			if (is_new_token(*ptr, *(ptr + 1)) > 0)
				p->token[p->n++] = *ptr++;
			p->token[p->n++] = *ptr++;
		}
	}
	if (p->n != 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	data->tokens[p->i++] = NULL;
	return (0);
}
