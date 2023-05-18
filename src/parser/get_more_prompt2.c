#include "../../libs/minishell.h"

int	check_valid_syntax(char *prompt, t_parser *p, int i, int last_token)
{
	int	token_type;

	p->in_single = 0;
	p->in_double = 0;
	while (prompt[i])
	{
		while (prompt[i] == ' ' && prompt[i])
			i++;
		token_type = is_new_token(prompt[i], prompt[i + 1]);
		if (token_type > 0 && last_token == 0)
			last_token = is_new_token(prompt[i], prompt[i + 1]);
		else if (token_type < 5 && token_type != 0 && last_token == 5)
			last_token = is_new_token(prompt[i], prompt[i + 1]);
		else if (token_type > 0 && last_token > 0)
			return (0);
		else
			last_token = 0;
		if (token_type == 1 || token_type == 2)
			i++;
		i++;
	}
	return (1);
}

int	check_unclosed_quote(char *s, t_parser *p)
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

char	*quote_readline(char *prompt, t_parser *p)
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

int	check_valid_last_pipe(char *prompt)
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
