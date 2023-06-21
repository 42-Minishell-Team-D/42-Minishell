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
