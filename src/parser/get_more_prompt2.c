#include "../../libs/minishell.h"

static int	speed_prompt(char *prompt, int *n)
{
	if (prompt[*n] == '"')
	{
		while (prompt[*n] != '"')
			(*n)++;
		if (prompt[*n] == '\0')
			return (1);
	}
	if (prompt[*n] == '\'')
	{
		while (prompt[*n] == '\'')
			(*n)++;
		if (prompt[*n] == '\0')
			return (1);
	}
	return (0);
}

static int new_token_checker(char *prompt, int *n)
{
	int		i;
	int		temp;
	char	*str;
	char	c;

	i = 0;
	c = '\0';
	str = NULL;
	if (is_new_token(prompt[*n], prompt[*n + 1]) <= 2)
		(*n) += 2;
	else
		(*n)++;
	while (prompt[*n] == ' ' && prompt[*n])
		(*n)++;
	if (prompt[*n] == '\'' || prompt[*n] == '"')
		c = prompt[*n];
	if (c > 0)
	{
		temp = (*n)++;
		while (prompt[*n] != c && prompt[*n])
			(*n)++;
		if (prompt[*n] == '\0')
			return (1);
		i = (*n);
		(*n) = temp + 1;
		str = ft_calloc(i - (*n) + 2, sizeof(char));
		ft_strlcpy(str, &prompt[*n], i - (*n) + 1);
		(*n) = i + 1;
		if ((str[1] == '\0' && str[0] != '|') || is_new_token(str[0], str[1]) > 0)
		{
			free(str);
			return (1);
		}
		free(str);
		return (0);
	}
	if ((prompt[*n] == '\0' && prompt[*n - 1] != '|') || is_new_token(prompt[*n], prompt[*n + 1]) > 0)
		return (1);
	return (0);
}

int check_valid_syntax(char *prompt)
{
	int n;

	n = 0;
	
	if (speed_prompt(prompt, &n) == 1)
			return (1);
	if (prompt[n] == '|')
		return (1);
	while (prompt[n])
	{
		if (speed_prompt(prompt, &n) == 1)
			return (1);
		if (is_new_token(prompt[n], prompt[n + 1]) > 0
			&& new_token_checker(prompt, &n) == 1)
			return (1);
		n++;
	}
	return (0);
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
