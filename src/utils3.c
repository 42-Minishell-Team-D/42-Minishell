/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:56:01 by loris             #+#    #+#             */
/*   Updated: 2023/07/03 22:56:02 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	quote_updater(char *ptr, t_parser *p)
{
	if (*ptr == '"' && !p->in_single)
		p->in_double = !p->in_double;
	if (*ptr == '\'' && !p->in_double)
		p->in_single = !p->in_single;
}

static int	determine_args(char *ptr, t_parser *p)
{
	reset_p_vars(p);
	p->n = 1;
	while (ptr[p->i])
	{
		if (ptr[p->i] == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (ptr[p->i] == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (ptr[p->i] == ' ' && !p->in_double && !p->in_single)
			p->n++;
		p->i++;
	}
	return (p->n + 1);
}

static int	quote_split_handle(char *token, t_parser *p)
{
	if (token[p->i] == '"' && !p->in_single)
	{
		delete_char_filter(&token[p->i]);
		while (token[p->i] != '"' && token[p->i] != '\0')
			p->i++;
		delete_char_filter(&token[p->i]);
		/*if (token[p->i + 1] == '"' && !p->in_single && !p->in_double)
		{
			delete_char_filter(&token[p->i]);
			delete_char_filter(&token[p->i]);
			return (1);
		}
		else
			p->in_double = !p->in_double;
			*/
	}
	if (token[p->i] == '\'' && !p->in_single && !p->in_double)
	{
		if (token[p->i + 1] == '\'')
		{
			delete_char_filter(&token[p->i]);
			delete_char_filter(&token[p->i]);
			return (1);
		}
		else
			p->in_single = !p->in_single;
	}
	return (0);
}

char	**ft_split_args(char *token, t_parser *p)
{
	char	**split;

	if (!token)
		return (NULL);
	split = (char **)ft_calloc(sizeof(char *), determine_args(token, p));
	reset_p_vars(p);
	while (token[p->i])
	{
		if (quote_split_handle(token, p) == 1)
			continue ;
		if (token[p->i] == ' ' && !p->in_double && !p->in_single)
		{
			split[p->n] = (char *)ft_calloc(sizeof(char), p->i + 1 - p->temp);
			ft_strlcpy(split[p->n++], &token[p->temp], p->i + 1 - p->temp);
			p->temp = p->i + 1;
		}
		p->i++;
	}
	split[p->n] = (char *)ft_calloc(sizeof(char), p->i + 1 - p->temp);
	ft_strlcpy(split[p->n++], &token[p->temp], p->i + 1 - p->temp);
	split[p->n] = NULL;
	reset_p_vars(p);
	return (split);
}
