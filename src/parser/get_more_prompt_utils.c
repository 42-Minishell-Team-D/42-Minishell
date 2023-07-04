/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_more_prompt_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:41:08 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 18:38:51 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static int	get_eof3(char *prompt, char *eof, int i, t_parser *p)
{
	int	j;

	j = 0;
	if (p->in_double == 0 && p->in_single == 0)
	{
		while (prompt[i] != '\0' && prompt[i] \
		!= '\n' && prompt[i] != ' ')
		{
			if (is_new_token(prompt[i], prompt[i + 1]) == 0)
				eof[j] = prompt[i];
			i++;
			j++;
		}
	}
	else if (p->in_double == 1)
		while (prompt[i] != '"' && prompt[i] != '\0')
			eof[j++] = prompt[i++];
	else if (p->in_single == 1)
		while (prompt[i] != '\'' && prompt[i] != '\0')
			eof[j++] = prompt[i++];
	eof[j] = '\0';
	reset_p_vars(p);
	return (i);
}

static int	get_eof2(char *prompt, int i, t_parser *p)
{
	i += 2;
	while (prompt[i] == ' ' && prompt[i])
		i++;
	if (prompt[i] == '"')
	{
		p->in_double = 1;
		i++;
	}
	else if (prompt[i] == '\'')
	{
		p->in_single = 1;
		i++;
	}
	return (i);
}

char	*get_eof(char *prompt, t_parser *p)
{
	char	*eof;
	int		i;

	i = 0;
	reset_p_vars(p);
	eof = ft_calloc(sizeof(char), ft_strlen(prompt) + 1);
	while (prompt[i])
	{
		if (is_new_token(prompt[i], prompt[i + 1]) == 1)
		{
			i = get_eof2(prompt, i, p);
			i = get_eof3(prompt, eof, i, p);
			return (eof);
		}
		i++;
	}
	free(eof);
	return (NULL);
}

void	update_prompt(t_data *data, t_parser *p)
{
	int		i;
	char	*join;

	i = 0;
	p->in_single = 0;
	p->in_double = 0;
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) \
	!= 1 && data->prompt[i] != '\0')
		i++;
	if (data->prompt[i] == '\0')
		return ;
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	delete_char_filter(&data->prompt[i]);
	delete_char_filter(&data->prompt[i]);
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) == 0 \
	&& data->prompt[i] != '\n' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	join = ft_strcdup(data->prompt, 0, '\n');
	free(data->prompt);
	data->prompt = ft_strdup(join);
	free(join);
}

int	check_valid_heredoc(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		speed_prompt(prompt, &i);
		if (prompt[i] == '\0')
			return (0);
		if (is_new_token(prompt[i], prompt[i + 1]) == 1)
			return (1);
		i++;
	}
	return (0);
}