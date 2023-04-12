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

static char *remove_after_last_occurrence(char *s, char c)
{
	// remove everything after the last occurrence of c in s
	int i;

	i = ft_strlen(s) - 1;
	while (s[i] != c && i != 0)
		i--;
	if (s[i] == c)
		s[i + 1] = '\0';
	return (s);
}

static char *get_from_second_line(char *s)
{
	// get everything from second line
	int i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (&s[i]);
}

// char *del_from_c_to_newline(char *p, char*tmp, char c)
// {
// 	int i;

// 	i = ft_strlen(p) - 1;
// 	while (p[i] != c && i != 0)
// 		i--;
// 	if (p[i] == c)
// 		p[i + 1] = '\0';
// 	i = 0;
// 	while (tmp[i] != '\n' && tmp[i] != '\0')
// 		i++;
// 	p = ft_strjoin(p, tmp);
// 	return (p);
// }

static char *quote_readline(char *prompt, t_parser *p)
{
	// quote " and ' will prompt for more until another ' or " is being input. Also adds newlines.
	int i;
	char c;
	char *tmp;
	char *tmp2;

	tmp = ft_strdup(prompt);
	while(check_unclosed_quote(tmp, p) == 1)
	{
		i = ft_strlen(tmp) - 1;
		if (p->in_single == 1)
			c = '\'';
		else
			c = '"';
		while (tmp[i] != c && i != 0)
			i--;
		if (tmp[i] == c)
		{
			tmp2 = ft_strjoin("\n", readline("miniquote> "));
			tmp = ft_strjoin(tmp, tmp2);
		}
	}
	prompt = ft_strjoin(remove_after_last_occurrence(prompt, c), get_from_second_line(tmp));
	// prompt = del_from_c_to_newline(prompt, tmp, c);
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