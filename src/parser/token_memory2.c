/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 09:14:58 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 18:59:46 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

void	handle_dollar_2_bleh(char *ptr, t_parser *p, t_data *data)
{
	char	*getenv;

	p->char_temp = ft_calloc(p->temp + 1, sizeof(char));
	if (p->char_temp == NULL)
		free_if_err(data->tokens, 1);
	ft_strlcpy(p->char_temp, ptr - p->temp, p->temp + 1);
	p->temp = 0;
	getenv = ft_getenv(p->char_temp, data->env);
	if (getenv)
		p->token_alloc[p->i] += ft_strlen(getenv);
	free(p->char_temp);
	p->char_temp = NULL;
	free(getenv);
}

static char	*handle_dollar(char *ptr, t_parser *p, t_data *data)
{
	if (*ptr == '?')
		ptr = hda_tkn_join(ptr, data->rt, p, data);
	else if (*ptr == '\'' || *ptr == '\"')
		ptr = hda_tkn_quotes(ptr, p);
	else if (*ptr != '\0' && *ptr != ' ')
		tkn_memo_hda_while(ptr, p, data);
	else
		p->token_alloc[p->i]++;
	if (*ptr == '$')
		ptr = hda_tkn_join(ptr, data->ms_id, p, data);
	if (*ptr == '$')
		ptr = handle_dollar(ptr, p, data);
	return (ptr);
}

static char	*handle_special_char(char *ptr, t_parser *p)
{
	int	special;

	special = is_new_token(*ptr, *(ptr + 1));
	if (p->token_alloc[p->i] > 0)
		p->i++;
	if (special == GREATGREAT || special == LESSLESS)
	{
		p->token_alloc[p->i++] = 2;
		return (ptr + 2);
	}
	else if (special == GREAT || special == LESS || special == PIPE)
	{
		p->token_alloc[p->i++] = 1;
		return (ptr + 1);
	}
	return (ptr);
}

void	token_ptr_quote(char *ptr, t_parser *p)
{
	if (*ptr == '"' && !p->in_single)
	{
		p->token_alloc[p->i]++;
		p->in_double = !p->in_double;
	}
	if (*ptr == '\'' && !p->in_double)
	{
		p->token_alloc[p->i]++;
		p->in_single = !p->in_single;
	}
}

void	token_memory_alloc(t_data *data, t_parser *p)
{
	char	*ptr;

	ptr = data->prompt;
	while (*ptr == ' ')
		ptr++;
	while (*ptr != '\0')
	{
		token_ptr_quote(ptr, p);
		if (*ptr == '$' && !p->in_single)
			ptr = handle_dollar(ptr + 1, p, data);
		if (*ptr == '\0')
			break ;
		if (!p->in_double && !p->in_single && \
		is_new_token(*ptr, *(ptr + 1)) > 1)
			ptr = handle_special_char(ptr, p);
		else if (*ptr != '\0')
		{
			p->token_alloc[p->i]++;
			ptr++;
		}
	}
}
