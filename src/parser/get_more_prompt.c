/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_more_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:54 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/04 08:36:38 by loris            ###   ########.fr       */
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

static char	*heredoc_readline(char *prompt, t_parser *p, char *tmp, char *join)
{
	char	*eof;
	char	*heredoc_prompt;

	eof = get_eof(prompt, p);
	heredoc_prompt = "\0";
	while (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
	{
		tmp = readline("minihduc🐣> ");
		if (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
		{
			join = ft_strjoin(tmp, "\n");
			free(tmp);
			tmp = ft_strjoin(join, "\0");
			free(join);
			join = ft_strjoin(heredoc_prompt, tmp);
			free(tmp);
			if (heredoc_prompt[0] != '\0')
				free(heredoc_prompt);
			heredoc_prompt = ft_strdup(join);
			free(join);
		}
	}
	free(eof);
	free(tmp);
	return (heredoc_prompt);
}

static int	get_more_prompt_hduc(t_data *data, int baal, t_parser *p, char *join)
{
	data->tmp = heredoc_readline(data->prompt, p, "\0", NULL);
	if (ft_strncmp("\0", data->tmp, 3) == 0)
		return (1);
	join = ft_strjoin(p->char_temp, data->tmp);
	free(p->char_temp);
	p->char_temp = ft_strjoin(join, "\0");
	free(join);
	free(data->tmp);
	update_prompt(data, p);
	if (baal == 0)
		pipe(data->fd_in);
	return (0);
}

static void	get_more_prompt_pipe(t_data *data, char *join)
{
	data->tmp = readline("minipipe> ");
	if (data->tmp == NULL)
	{
		ft_printf_fd(1, "\n");
		return ;
	}
	join = ft_strjoin(data->prompt, data->tmp);
	free(data->prompt);
	data->prompt = ft_strdup(join);
	free(join);
	free(data->tmp);
}

int	get_more_prompt(t_data *data, t_parser *p, int baal)
{
	if (check_valid_syntax(data->prompt) == 1)
	{
		data->rt = 2;
		printf("minishell: syntax error ( °︠ ‿ ︡°)\n");
		return (1);
	}
	if (check_valid_heredoc(data->prompt) == 1)
	{
		if (get_more_prompt_hduc(data, baal, p, NULL) == 1)
			return (1);
	}
	else if (check_valid_last_pipe(data->prompt) == 1)
		get_more_prompt_pipe(data, NULL);
	if (check_valid_last_pipe(data->prompt) == 1 || \
	(check_valid_heredoc(data->prompt) == 1))
		get_more_prompt(data, p, 1);
	return (0);
}
