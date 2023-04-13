#include "../../libs/minishell.h"

static int check_unclosed_quote(char *s, t_parser *p)
{
	// check all the string for quotes and return 1 if there is a single or double quote not closed. p->in_single and p->in_double will be set to 1 if there is a quote not closed
	int i;

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

static char *quote_readline(char *prompt, t_parser *p)
{
	// quote " and ' will prompt for more until another ' or " is being input. Also adds newlines.
	int i;
	char c;
	char *tmp;

	while(check_unclosed_quote(prompt, p) == 1)
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

static int check_valid_last_pipe(char *prompt)
{
	// if valid last pipe, return 1. 0 if not
	// should return 0 if double pipe or first char is a pipe.
	// loop into string backward until detecting |, then loop and skipp spaces forward until detecting |. If there is a | before the end of the string, return 1
	int i;

	i = ft_strlen(prompt) - 1;
	if (prompt[0] == '|')
		return (0);
	while (prompt[i] == ' ' && i != 0)
		i--;
	if (prompt[i] == '|')
	{
		i--;
		while (prompt[i] == ' ')
			i--;
		if (prompt[i] == '|')
			return (0);
	}
	i = ft_strlen(prompt) - 1;
	while (prompt[i] == ' ' && i != 0)
		i--;
	if (prompt[i] == '|')
		return (1);
	return (0);
}

void	get_more_prompt(t_data *data, t_parser *p)
{
	if (check_unclosed_quote(data->prompt, p) == 1)
		data->prompt = quote_readline(data->prompt, p);
	if (check_valid_last_pipe(data->prompt) == 1)
		data->prompt = ft_strjoin(data->prompt, readline("minipipe> "));
	add_history(data->prompt);

	if (check_unclosed_quote(data->prompt, p) == 1 || check_valid_last_pipe(data->prompt) == 1)
		get_more_prompt(data, p);
}

// still need to handle heredoc <<, read until the next token is the same as the first one