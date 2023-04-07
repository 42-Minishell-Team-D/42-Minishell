#include "../../libs/minishell.h"

static char	*handle_dollar(char *ptr, t_parser *p, t_data *data)
{
	ptr++;
	if (*ptr == '?')
	{
		p->token_alloc[p->i] += ft_strlen(ft_itoa(data->rt));
		ptr++;
	}
	else if (*ptr != '\0' && *ptr != ' ')
	{
		while (*ptr != '\0' && *ptr != ' ' && *ptr != '$')
		{
			if (p->in_double && *ptr == '"')
				break ;
			if (is_new_token(*ptr, *(ptr + 1)) > 0)
				break ;
			ptr++;
			p->temp++;
		}
		p->char_temp = ft_calloc(p->temp + 1, sizeof(char));
		if (p->char_temp == NULL)
			return (NULL);
		ft_strlcpy(p->char_temp, ptr - p->temp, p->temp + 1);
		p->temp = 0;
		if (getenv(p->char_temp))
		{
			p->token_alloc[p->i] += ft_strlen(getenv(p->char_temp));
			free(p->char_temp);
			p->char_temp = NULL;
		}
	}
	else
		p->token_alloc[p->i]++;
	if (*ptr == '$')
		ptr = handle_dollar(ptr, p, data);
	return (ptr);
}

static char	*handle_special_char(char *ptr, t_parser *p)
{
	int	special;

	special = is_new_token(*ptr, *(ptr + 1));
	if (p->token_alloc[p->i] > 0)
		p->i++;
	if (special == GREATGREAT || special == LESSLESS)
	{
		p->token_alloc[p->i++] = 2;
		return (ptr + 2);
	}
	else if (special == GREAT || special == LESS || special == PIPE)
	{
		p->token_alloc[p->i++] = 1;
		return (ptr + 1);
	}
	return (ptr);
}

static void	token_memory_alloc(t_data *data, t_parser *p)
{
	char	*ptr;

	ptr = data->prompt;
	while (*ptr == ' ')
		ptr++;
	while (*ptr != '\0')
	{
		if (*ptr == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (*ptr == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (*ptr == '$' && !p->in_single)
			ptr = handle_dollar(ptr, p, data);
		if (!p->in_double && !p->in_single && is_new_token(*ptr, *ptr + 1) > 0)
			ptr = handle_special_char(ptr, p);
		else if (*ptr != '\0')
		{
			p->token_alloc[p->i]++;
			ptr++;
		}
	}
	// int i = 0;
	// while (p->token_alloc[i] > 0)
	// 	printf("%d\n", p->token_alloc[i++] );
}

void	malloc_token(t_data *data, t_parser *p)
{
	reset_p_vars(p);
	token_memory_alloc(data, p);
	data->tokens = NULL;
	data->tokens = (char **)ft_calloc(10, sizeof(char *));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	p->i = 0;
	p->bigger_token = 0;
	while (p->token_alloc[p->i] > 0)
	{
		data->tokens[p->i] = NULL;
		data->tokens[p->i] = (char *)ft_calloc(p->token_alloc[p->i] + 1, sizeof(char));
		if (data->tokens[p->i] == NULL)
				exit(write(1, "Error: malloc failed\n", 21));
		if (p->bigger_token < p->token_alloc[p->i])
			p->bigger_token = p->token_alloc[p->i];
		p->i++;
	}
	p->token = (char *)ft_calloc(p->bigger_token + 1, sizeof(char));
	if (p->token == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	p->i = 0;
}