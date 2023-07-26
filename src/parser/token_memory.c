/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:15:01 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 09:22:29 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

char	*hda_tkn_question(char *ptr, t_parser *p, t_data *data)
{
	data->itoa = ft_itoa(data->rt);
	p->token_alloc[p->i] += ft_strlen(data->itoa);
	free(data->itoa);
	ptr++;
	return (ptr);
}

char	*hda_tkn_quotes(char *ptr, t_parser *p)
{
	char	temp;

	temp = *ptr;
	ptr++;
	while (*ptr != '\0' && *ptr != temp)
	{
		p->token_alloc[p->i]++;
		ptr++;
	}
	return (++ptr);
}

static void	malloc_token2(t_data *data, t_parser *p)
{
	reset_p_vars(p);
	token_memory_alloc(data, p);
	data->tokens = NULL;
	data->tokens = (char **)ft_calloc(10, sizeof(char *));
	if (data->tokens == NULL)
		free_if_err(data->tokens, 1);
	p->i = 0;
	p->bigger_token = 0;
}

void	malloc_token(t_data *data, t_parser *p)
{
	malloc_token2(data, p);
	while (p->token_alloc[p->i] > 0)
	{
		data->tokens[p->i] = NULL;
		data->tokens[p->i] = \
		(char *)ft_calloc(p->token_alloc[p->i] + 1, sizeof(char));
		if (data->tokens[p->i] == NULL)
			free_if_err(data->tokens, 1);
		if (p->bigger_token < p->token_alloc[p->i])
			p->bigger_token = p->token_alloc[p->i];
		p->i++;
	}
	p->token = (char *)ft_calloc(p->bigger_token + 1, sizeof(char));
	if (p->token == NULL)
		free_if_err(data->tokens, 1);
	p->i = 0;
}
