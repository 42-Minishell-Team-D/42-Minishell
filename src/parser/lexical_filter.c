#include "../../libs/minishell.h"

static void	delete_char(char *str)
{
	while (*str != '\0')
	{
		str++;
		*(str - 1) = *str;
	}
}

void	lexical_filter(t_data *data, t_parser *p)
{
	char	*ptr;

	while (data->tokens[p->i] != NULL)
	{
		ptr = data->tokens[p->i];
		if (*ptr == ' ')
		{
			ptr++;
			delete_char(ptr - 1);
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
		p->i++;
	}
}
