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

	// int	i;

	// i = ft_strlen(prompt) - 1;
	// while (prompt[i] != '<' && i != 0)
	// 	i--;
	// if (i < 1)
	// 	return (0);
	// if (prompt[i] == '<' && prompt[i - 1] == '<')
	// {
	// 	i++;
	// 	while (prompt[i] == ' ' && i != 0)
	// 		i++;
	// 	if (prompt[i] == '\0')
	// 		return (0);
	// 	return (1);
	// }
	// return (0);
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

// static int check_if_end_is_eof(char *prompt, char *eof)
// {
// 	int	i;
// 	int	j;

// 	printf("prompt: %s\n", prompt);
// 	printf("eof: %s\n", eof);

// 	i = ft_strlen(prompt) - 1;
// 	j = ft_strlen(eof) - 1;
// 	if (ft_strchr(prompt, '\n') == NULL)
// 		return (0);
// 	while (prompt[i] != '\0' && j != 0)
// 	{
// 		if (prompt[i] == eof[j])
// 		{
// 			i--;
// 			j--;
// 		}
// 		else
// 			return (0);	// return 0 if not end of file
// 	}
// 	if (prompt[i] != '\n')
// 		return (0);
// 	return (1);	// return 1 if end of file
// }

static void	update_prompt(t_data *data, t_parser *p)
{
	int i;
	char *eof;
	// char *get_str;
	// char *ret;

	i = 0;
	p->in_single = 0;
	p->in_double = 0;
	eof = get_eof(data->prompt, 0, p);
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) != 1 && data->prompt[i] != '\0')
		i++;
	if (data->prompt[i] == '\0')
		return ;
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		data->prompt = delete_char(data->prompt, i);
	data->prompt = delete_char(data->prompt, i);
	data->prompt = delete_char(data->prompt, i);
	while (data->prompt[i] == ' ' && data->prompt[i] != '\0')
		data->prompt = delete_char(data->prompt, i);
	while (is_new_token(data->prompt[i], data->prompt[i + 1]) == 0 && data->prompt[i] != '\n' && data->prompt[i] != '\0')
		data->prompt = delete_char(data->prompt, i);
	// printf("prompt: %s\n", data->prompt);
	// while (data->prompt[i] != '\n')
		// i++;
	// i++;
	// get_str = ft_strcdup(data->prompt, i, '\n');
	// ret = ft_strdup(get_str);
	// while (ft_strncmp(eof, get_str, get_biggest_len(eof, get_str)) != 0 && eof != NULL)
	// {
	// 	while (data->prompt[i] != '\n')
	// 		i++;
	// 	i++;
	// 	get_str = ft_strcdup(data->prompt, i, '\n');
	// 	if (ft_strncmp(eof, get_str, get_biggest_len(eof, get_str)) != 0)
	// 		ret = ft_strjoin(ret, ft_strjoin("\n", get_str));
	// }
	data->prompt = ft_strcdup(data->prompt, 0, '\n');
	// printf("prompt2: %s\n", data->prompt);

}

static char	*heredoc_readline(char *prompt, t_parser *p)
{
	char	*eof;
	char	*tmp;
	char	*heredoc_prompt;

	eof = ft_strjoin("\n", get_eof(prompt, 0, p));
	tmp = "\0";
	heredoc_prompt = "\0";
	// if (check_if_end_is_eof(prompt, eof) == 1)
	// {
	// 	free(eof);
	// 	return (prompt);
	// }
	while (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
	{
		tmp = ft_strjoin("\n", readline("minihdoc🐣> "));
		if (ft_strncmp(eof, tmp, get_biggest_len(eof, tmp)) != 0)
			heredoc_prompt = ft_strjoin(heredoc_prompt, tmp);
	}
	free(eof);
	free(tmp);
	return (heredoc_prompt);
}

int	get_more_prompt(t_data *data, t_parser *p)
{
	char	*tmp;

	if (check_valid_syntax(data->prompt) == 1)
	{
		printf("minishell: syntax error ( °︠ ‿ ︡°)\n");
		return (1);
	}
	if (check_valid_last_pipe(data->prompt) == 1)
		data->prompt = ft_strjoin(data->prompt, readline("minipipe> "));
	if (check_valid_heredoc(data->prompt) == 1)
	{
		// heredoc_prompt = heredoc_readline(data->prompt, p);
		tmp = heredoc_readline(data->prompt, p);
		p->char_temp = ft_strjoin(p->char_temp, tmp);
		update_prompt(data, p);
		printf("heredoc_prompt: %s\n", p->char_temp);
		printf("prompt: %s\n", data->prompt);
		// ATTENTION: heredoc_prompt can be NULL!
		pipe(data->fd_in);
		write(data->fd_in[1], p->char_temp, ft_strlen(p->char_temp));
		// close(data->fd_in[1]);
		// (void)heredoc_prompt;
	}
	if (check_valid_last_pipe(data->prompt) == 1 || \
	(check_valid_heredoc(data->prompt) == 1))
		get_more_prompt(data, p);
	// free(p->char_temp);
	return (0);
}
