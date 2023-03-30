#include "../../libs/minishell.h"

int	is_new_token(char c, char c2)
{
	if (c == '<')
		return (LESS);
	if (c == '<' && c2 == '<')
		return (LESSLESS);
	if (c == '>')
		return (GREAT);
	if (c == '>' && c2 == '>')
		return (GREATGREAT);
	if (c == '|')
		return (PIPE);
	return (0);
}

static char	*handle_special_char(char *ptr, t_parser *p, t_data *data)
{
	int	special;

	special = is_new_token(*ptr, *ptr + 1);
	if (p->in_single || p->in_double)
		return (ptr);
	ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	ft_bzero(p->token, 250);
	p->n = 0;
	if (special == GREATGREAT)
	{
		data->tokens[p->i][0] = '>';
		data->tokens[p->i++][1] = '>';
		return (ptr + 2);
	}
	else if (special == LESSLESS)
	{
		data->tokens[p->i][0] = '<';
		data->tokens[p->i++][1] = '<';
		return (ptr + 2);
	}
	else if (special == PIPE)
	{
		data->tokens[p->i++][0] = '|';
		return (ptr + 1);
	}
	else if (special == LESS)
	{
		data->tokens[p->i++][0] = '<';
		return (ptr + 1);
	}
	else if (special == GREAT)
	{
		data->tokens[p->i++][0] = '>';
		return(ptr + 1);
	}
	return (ptr);
}

static char *handle_dollar(char *ptr, t_parser *p, t_data *data)
{
	char	*temp;
	ptr++;
	if (*ptr == '?')
	{
		temp = malloc(sizeof(char) * ft_strlen(ft_itoa(data->rt)));
		temp = ft_itoa(data->rt);
		temp = ft_strjoin(p->token, temp);
		ft_strlcpy(p->token, temp, ft_strlen(temp) + 1);
		p->n += ft_strlen(ft_itoa(data->rt));
		ptr++;
	}
	else
	{
	}
	return (ptr);
}

static void	get_next_token(t_data *data, t_parser *p)
{
	char *ptr = NULL;

	p->n = 0;
	ft_bzero(p->token, 250);
	if (ptr == NULL)
		ptr = data->prompt;
	if (*ptr == '\0')
		return ;
	while (*ptr != '\0')
	{
		if (*ptr == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (*ptr == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (*ptr == '$' && !p->in_single)
			ptr = handle_dollar(ptr, p, data);
		if (is_new_token(*ptr, *ptr + 1) > 0)
			ptr = handle_special_char(ptr, p, data);
		else if (*ptr != '\0')
		{
			p->token[p->n++] = *ptr;
			ptr++;
		}
	}
	ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
}

int	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	p->i = 0;
	p->n = 0;
	p->in_double = 0;
	p->in_single = 0;
	get_next_token(data, p);
	/*int i = 0;
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");
	exit(1);*/
	
	return (0);
}
