#include "../../libs/minishell.h"

static int	check_valid_syntax(char *prompt, t_parser *p)
{
	int	i;
	int	last_token;
	int	token_type;

	p->in_single = 0;
	p->in_double = 0;
	i = 0;
	last_token = 0;
	while (prompt[i])
	{
		while (prompt[i] == ' ' && prompt[i])
			i++;
		token_type = is_new_token(prompt[i], prompt[i + 1]);
		if (token_type > 0 && last_token == 0)								// if new token is fresh pipe or redirection, put info in tracker
			last_token = is_new_token(prompt[i], prompt[i + 1]);
		else if (token_type < 5 && token_type != 0 && last_token == 5)		// if new token is redirection and old token was pipe, put info in tracker
			last_token = is_new_token(prompt[i], prompt[i + 1]);
		else if (token_type > 0 && last_token > 0)							// if is new token, and old token was a pipe or redirection, return (0)
			return (0);
		else
			last_token = 0;
		if (token_type == 1 || token_type == 2)
			i++;
		i++;
	}
	return (1);
}

static int	check_unclosed_quote(char *s, t_parser *p)
{
	int	i;

	i = 0;
	p->in_single = 0;
	p->in_double = 0;
	while (s[i])
	{
		if (s[i] == '\'' && p->in_double == 0)
			p->in_single = !p->in_single;
		if (s[i] == '"' && p->in_single == 0)
			p->in_double = !p->in_double;
		i++;
	}
	if (p->in_single == 1 || p->in_double == 1)
		return (1);
	return (0);
}

static char	*quote_readline(char *prompt, t_parser *p)
{
	int		i;
	char	c;
	char	*tmp;

	while (check_unclosed_quote(prompt, p) == 1)
	{
		i = ft_strlen(prompt) - 1;
		if (p->in_single == 1)
			c = '\'';
		else
			c = '"';
		while (prompt[i] != c && i != 0)
			i--;
		if (prompt[i] == c)
		{
			tmp = ft_strjoin("\n", readline("miniquote> "));
			prompt = ft_strjoin(prompt, tmp);
		}
	}
	return (prompt);
}

static int	check_valid_last_pipe(char *prompt)
{
	int	i;

	i = ft_strlen(prompt) - 1;
	if (prompt[0] == '|')
		return (0);
	while (prompt[i] == ' ' && i != 0)
		i--;
	if (prompt[i] == '|')
		return (1);
	return (0);
}

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

char *get_eof(char *prompt)
{
	int		i;
	int		j;
	char	*eof;

	i = ft_strlen(prompt) - 1;
	j = 0;
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
		{
			eof[j] = prompt[i];
			i++;
			j++;
		}
		if (prompt[i - 1] == '"' || prompt[i - 1] == '\'')
			j--;
		eof[j] = '\0';
		return (eof);
	}
	return (NULL);
}

static char *heredoc_readline(char *prompt)
{
	// can be several heredocs in a row, so need to loop until no more << are found. e.g. ok << ok << ok
	// loop into string backward while detecting << or i != 0
	// if there is a << before the end of the string, save the next char delimited by spaces or quote and return 1
	// if no chars other than space or pipe or redirection after <<, return 0
	char *eof;
	char *tmp;

	eof = ft_strjoin("\n" , get_eof(prompt));
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
	int hdoc_bool;

	hdoc_bool = 0;	
	if (check_valid_syntax(data->prompt, p) == 0)
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
	// printf("%s\n", data->prompt); Don't forget to comment stuff that's not suppose to appear :(

	add_history(data->prompt);
	if (check_unclosed_quote(data->prompt, p) == 1 || check_valid_last_pipe(data->prompt) == 1 || (check_valid_last_heredoc(data->prompt) == 1 && hdoc_bool == 0))
		get_more_prompt(data, p);
}
