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
	if (is_new_token(prompt[*n], prompt[*n + 1]) <= 2)
		(*n) += 2;
	else
		(*n)++;
	while (prompt[*n] == ' ' && prompt[*n])
		(*n)++;
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

// int	check_valid_syntax(char *prompt, t_parser *p, int i, int last_token)
// {
	// int	token_type;

	// p->in_single = 0;
	// p->in_double = 0;
	// while (prompt[i])
	// {
	// 	while (prompt[i] == ' ' && prompt[i])
	// 		i++;
	// 	token_type = is_new_token(prompt[i], prompt[i + 1]);
	// 	if (token_type > 0 && last_token == 0)
	// 		last_token = is_new_token(prompt[i], prompt[i + 1]);
	// 	else if (token_type < 5 && token_type != 0 && last_token == 5)
	// 		last_token = is_new_token(prompt[i], prompt[i + 1]);
	// 	else if (token_type > 0 && last_token > 0)
	// 		return (0);
	// 	else
	// 		last_token = 0;
	// 	if (token_type == 1 || token_type == 2)
	// 		i++;
	// 	i++;
	// }
	// return (1);
// }

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
