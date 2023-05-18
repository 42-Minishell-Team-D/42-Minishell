#include "../../libs/minishell.h"

static int	check_valid_last_heredoc(char *prompt)
{
	int	i;

	i = ft_strlen(prompt) - 1;
	while (prompt[i] != '<' && i != 0)
		i--;
	if (i < 1)
		return (0);
	if (prompt[i] == '<' && prompt[i - 1] == '<')
	{
		i++;
		while (prompt[i] == ' ' && i != 0)
			i++;
		if (prompt[i] == '\0')
			return (0);
		return (1);
	}
	return (0);
}

static char	*get_eof(char *prompt, int i, int j)
{
	char	*eof;

	eof = malloc(sizeof(char) * ft_strlen(prompt));
	while (prompt[i] != '<' && i != 0)
		i--;
	if (i < 1)
		return (NULL);
	if (prompt[i] == '<' && prompt[i - 1] == '<')
	{
		i++;
		while (prompt[i] == ' ' && i != 0)
			i++;
		if (prompt[i] == '"' || prompt[i] == '\'')
			i++;
		while (prompt[i] != '\0')
			eof[j++] = prompt[i++];
		if (prompt[i - 1] == '"' || prompt[i - 1] == '\'')
			j--;
		eof[j] = '\0';
		return (eof);
	}
	return (NULL);
}

static char	*heredoc_readline(char *prompt)
{
	char	*eof;
	char	*tmp;

	eof = ft_strjoin("\n", get_eof(prompt, ft_strlen(prompt) - 1, 0));
	tmp = ft_strjoin("\n", readline("minihdoc> "));
	while (ft_strncmp(eof, tmp, ft_strlen(eof)) != 0)
	{
		tmp = ft_strjoin("\n", readline("minihdoc> "));
		prompt = ft_strjoin(prompt, tmp);
	}
	free(eof);
	return (prompt);
}

void	get_more_prompt(t_data *data, t_parser *p)
{
	int	hdoc_bool;

	hdoc_bool = 0;
	if (check_valid_syntax(data->prompt, p, 0, 0) == 0)
	{
		add_history(data->prompt);
		return ;
	}
	if (check_unclosed_quote(data->prompt, p) == 1)
		data->prompt = quote_readline(data->prompt, p);
	if (check_valid_last_pipe(data->prompt) == 1)
		data->prompt = ft_strjoin(data->prompt, readline("minipipe> "));
	if (check_valid_last_heredoc(data->prompt) == 1 && hdoc_bool == 0)
	{
		data->prompt = heredoc_readline(data->prompt);
		hdoc_bool = 1;
	}
	add_history(data->prompt);
	if (check_unclosed_quote(data->prompt, p) == 1 || \
	check_valid_last_pipe(data->prompt) == 1 || \
	(check_valid_last_heredoc(data->prompt) == 1 && hdoc_bool == 0))
		get_more_prompt(data, p);
}
