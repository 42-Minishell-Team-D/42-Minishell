/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_more_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpenelon <lpenelon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 13:42:36 by lpenelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

static int	check_valid_heredoc(char *prompt)
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

static char	*heredoc_readline(t_data *data, char *join, char *eof, char *h_p)
{
	data->tmp = "\0";
	while (ft_strncmp(eof, data->tmp, get_biggest_len(eof, data->tmp)) != 0)
	{
		data->tmp = readline("minihduc🐣> ");
		if (data->tmp == NULL)
			return (NULL);
		if (ft_strncmp(eof, data->tmp, get_biggest_len(eof, data->tmp)) != 0)
		{
			join = ft_strjoin(data->tmp, "\n");
			free(data->tmp);
			data->tmp = ft_strjoin(join, "\0");
			free(join);
			join = ft_strjoin(h_p, data->tmp);
			free(data->tmp);
			data->tmp = "\0";
			if (h_p[0] != '\0')
				free(h_p);
			h_p = ft_strdup(join);
			free(join);
		}
	}
	free(eof);
	free(data->tmp);
	return (h_p);
}

static int	get_more_prompt_hduc(t_data *data, int b, t_parser *p, char *join)
{
	data->tmp = heredoc_readline(data, NULL, get_eof(data->prompt, p), "\0");
	if (data->tmp == NULL)
		return (1);
	if (ft_strncmp("\0", data->tmp, 3) == 0)
	{
		update_prompt(data, p);
		if (b == 0)
			pipe(data->fd_in);
		return (0);
	}
	join = ft_strjoin(p->char_temp, data->tmp);
	free(p->char_temp);
	p->char_temp = ft_strjoin(join, "\0");
	free(join);
	free(data->tmp);
	update_prompt(data, p);
	if (b == 0)
		pipe(data->fd_in);
	return (0);
}

static int	get_more_prompt_pipe(t_data *data, char *join)
{
	data->tmp = readline("minipipe> ");
	if (data->tmp == NULL)
		return (1);
	join = ft_strjoin(data->prompt, data->tmp);
	free(data->prompt);
	data->prompt = ft_strdup(join);
	free(join);
	free(data->tmp);
	return (0);
}

int	get_more_prompt(t_data *data, t_parser *p, int b)
{
	if (check_valid_syntax(data->prompt) == 1)
	{
		data->rt = 2;
		printf("minishell: syntax error ( °︠ ‿ ︡°)\n");
		return (1);
	}
	if (check_valid_heredoc(data->prompt) == 1)
	{
		if (get_more_prompt_hduc(data, b, p, NULL) == 1)
			return (1);
	}
	else if (check_valid_last_pipe(data->prompt) == 1)
	{
		if (get_more_prompt_pipe(data, NULL) == 1)
			return (1);
	}
	if (check_valid_last_pipe(data->prompt) == 1 || \
	(check_valid_heredoc(data->prompt) == 1))
		get_more_prompt(data, p, 1);
	return (0);
}
