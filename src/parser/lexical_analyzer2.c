/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:37:02 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 11:40:24 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static char	*handle_special_char_2_anal(char *ptr, int special,
									t_parser *p, t_data *data)
{
	if (special == LESSLESS)
	{
		data->tokens[p->i][0] = '<';
		data->tokens[p->i++][1] = '<';
		return (ptr + 2);
	}
	else if (special == PIPE)
	{
		data->tokens[p->i++][0] = '|';
		return (ptr + 1);
	}
	else if (special == LESS)
	{
		data->tokens[p->i++][0] = '<';
		return (ptr + 1);
	}
	else if (special == GREAT)
	{
		data->tokens[p->i++][0] = '>';
		return (ptr + 1);
	}
	return (ptr);
}

char	*handle_special_char_anal(char *ptr, t_parser *p, t_data *data)
{
	int	special;

	special = is_new_token(*ptr, *(ptr + 1));
	if (p->n > 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	ft_bzero(p->token, p->bigger_token + 1);
	p->n = 0;
	if (special == GREATGREAT)
	{
		data->tokens[p->i][0] = '>';
		data->tokens[p->i++][1] = '>';
		return (ptr + 2);
	}
	return (handle_special_char_2_anal(ptr, special, p, data));
}

static void	handle_dollar_anal_env(t_parser *p, t_data *data)
{
	char	*getenv;

	getenv = NULL;
	getenv = ft_getenv(p->char_temp, data->env);
	if (getenv)
	{
		ft_strlcpy(&p->token[ft_strlen(p->token)],
			getenv, ft_strlen(getenv) + 1);
		p->n += ft_strlen(getenv);
		free(p->char_temp);
		p->char_temp = NULL;
	}
	if (getenv != NULL)
		free(getenv);
}

static char	*handle_dollar_anal_2(char *ptr, t_parser *p, t_data *data)
{
	while (*ptr != '\0' && *ptr != ' ' && *ptr != '$')
	{
		if ((p->in_double && *ptr == '"') || *ptr == '\0')
			break ;
		if (is_new_token(*ptr, *(ptr + 1)) > 1)
			break ;
		ptr++;
		p->temp++;
	}
	p->char_temp = ft_calloc(p->temp + 1, sizeof(char));
	if (p->char_temp == NULL)
		return (NULL);
	ft_strlcpy(p->char_temp, ptr - p->temp, p->temp + 1);
	p->temp = 0;
	handle_dollar_anal_env(p, data);
	return (ptr);
}

char	*handle_dollar_anal(char *ptr, t_parser *p, t_data *data)
{
	ptr++;
	if (*ptr == '?')
	{
		p->char_temp = malloc(sizeof(char) * ft_strlen(ft_itoa(data->rt)));
		if (p->char_temp == NULL)
			return (NULL);
		p->char_temp = ft_itoa(data->rt);
		p->char_temp = ft_strjoin(p->token, p->char_temp);
		ft_strlcpy(p->token, p->char_temp, ft_strlen(p->char_temp) + 1);
		p->n += ft_strlen(ft_itoa(data->rt));
		free(p->char_temp);
		ptr++;
	}
	else if (*ptr != '\0' && *ptr != ' ')
		ptr = handle_dollar_anal_2(ptr, p, data);
	else
		p->token[p->n++] = '$';
	if (*ptr == '$')
		ptr = handle_dollar_anal(ptr, p, data);
	return (ptr);
}
