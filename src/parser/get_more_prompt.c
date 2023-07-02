#include "../../libs/minishell.h"

static int	check_valid_heredoc(char *prompt)
{
	int i;

	i = 0;
	while (prompt[i])
	{
		if (is_new_token(prompt[i], prompt[i + 1]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static char	*get_eof(char *prompt, int j, t_parser *p)
{
	char	*eof;
	int		i;

	i = 0;
	reset_p_vars(p);
	eof = malloc(sizeof(char) * ft_strlen(prompt));
	while (prompt[i])
	{
		if (is_new_token(prompt[i], prompt[i + 1]) == 1)
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
			if (p->in_double == 0 && p->in_single == 0)
			{
				while (is_new_token(prompt[i], prompt[i + 1]) == 0 && prompt[i] != '\0' && prompt[i] != '\n' && prompt[i] != ' ')
					eof[j++] = prompt[i++];
			}
			else if (p->in_double == 1)
			{
				while (prompt[i] != '"' && prompt[i] != '\0')
					eof[j++] = prompt[i++];
			}
			else if (p->in_single == 1)
			{
				while (prompt[i] != '\'' && prompt[i] != '\0')
					eof[j++] = prompt[i++];
			}
			eof[j] = '\0';
			reset_p_vars(p);
			return (eof);
		}			
		i++;
	}
	return (NULL);
}

static void	update_prompt(t_data *data, t_parser *p)
{
	int i;
	char *eof;

	i = 0;
	p->in_single = 0;
	p->in_double = 0;
	eof = get_eof(data->prompt, 0, p);
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) != 1 && data->prompt[i] != '\0')
		i++;
	if (data->prompt[i] == '\0')
		return ;
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	delete_char_filter(&data->prompt[i]);
	delete_char_filter(&data->prompt[i]);
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) == 0 && data->prompt[i] != '\n' && data->prompt[i] != '\0')
		delete_char_filter(&data->prompt[i]);
	data->prompt = ft_strcdup(data->prompt, 0, '\n');
}

static char	*heredoc_readline(char *prompt, t_parser *p)
{
	char	*eof;
	char	*tmp;
	char	*heredoc_prompt;

	eof = get_eof(prompt, 0, p);
	tmp = "\0";
	heredoc_prompt = "\0";
	while (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
	{
		tmp = readline("minihduc🐣> ");
		if (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
		{
			tmp = ft_strjoin(tmp, "\n");
			heredoc_prompt = ft_strjoin(heredoc_prompt, tmp);
		}
	}
	free(eof);
	free(tmp);
	return (heredoc_prompt);
}

int	get_more_prompt(t_data *data, t_parser *p, int baal)
{
	char	*tmp;
	char	*join;

	if (check_valid_syntax(data->prompt) == 1)
	{
		printf("minishell: syntax error ( °︠ ‿ ︡°)\n");
		return (1);
	}
	if (check_valid_heredoc(data->prompt) == 1)
	{
		tmp = heredoc_readline(data->prompt, p);
		if (ft_strncmp("\0", tmp, 3) == 0)
			return (1);
		join = ft_strjoin(p->char_temp, tmp);
		free(p->char_temp);
		p->char_temp = ft_strjoin(join, "\0");
		free(join);
		free(tmp);
		update_prompt(data, p);
		if (baal == 0)
			pipe(data->fd_in);
	}
	else if (check_valid_last_pipe(data->prompt) == 1)
	{
		tmp = readline("minipipe> ");
		if (tmp == NULL)
			return (ft_printf_fd(1, "\n"));
		data->prompt = ft_strjoin(data->prompt, tmp);
		free(tmp);
	}
	if (check_valid_last_pipe(data->prompt) == 1 || \
	(check_valid_heredoc(data->prompt) == 1))
		get_more_prompt(data, p, 1);
	return (0);
}
