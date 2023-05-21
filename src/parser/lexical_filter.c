#include "../../libs/minishell.h"

static void	delete_token(char **token)
{
	char	**ptr;

	ptr = token;
	free(*token);
	while (*ptr != NULL)
	{
		*ptr = *(ptr + 1);
		ptr++;
	}
}

static void	delete_char(char *str)
{
	while (*str != '\0')
	{
		str++;
		*(str - 1) = *str;
	}
}

char	*lexical_prompt_filter(char *prompt)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (*prompt == ' ')
		delete_char(prompt);
	while (*prompt != '\0')
	{
		if (*prompt == '"' && !in_single)
			in_double = !in_double;
		if (*prompt == '\'' && !in_double)
			in_single = !in_single;
		if (*prompt == ' ' && (*(prompt + 1) == ' ' || *(prompt + 1) == '\0')
			&& !in_double && !in_single)
			delete_char(prompt);
		else
			prompt++;
	}
	return (prompt);
}

void	lexical_filter(t_data *data, t_parser *p)
{
	char	*ptr;

	while (data->tokens[p->i] != NULL)
	{
		ptr = data->tokens[p->i++];
		while (*ptr == ' ')
			delete_char(ptr);
		if (ft_strlen(ptr) == 0)
		{
			delete_token(data->tokens + --p->i);
			continue ;
		}
		while (*ptr != '\0')
		{
			if (*ptr == '"' && !p->in_single)
				p->in_double = !p->in_double;
			if (*ptr == '\'' && !p->in_double)
				p->in_single = !p->in_single;
			if (*ptr == ' ' && (*(ptr + 1) == ' ' || *(ptr + 1) == '\0')
				&& !p->in_double && !p->in_single)
				delete_char(ptr);
			else
				ptr++;
		}
	}
}
