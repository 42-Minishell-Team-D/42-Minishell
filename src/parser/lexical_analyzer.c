#include "../../libs/minishell.h"

static char	*handle_special_char(char *ptr, t_parser *p, t_data *data)
{
	int	special;

	if (p->in_single || p->in_double)
		return (ptr);
	special = is_new_token(*ptr, *(ptr + 1));
	if (p->n > 0)
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
		return (ptr + 1);
	}
	return (ptr);
}

static char *handle_dollar(char *ptr, t_parser *p, t_data *data)
{
	ptr++;
	if (*ptr == '?')
	{
		p->char_temp = malloc(sizeof(char) * ft_strlen(ft_itoa(data->rt)));
		if (p->char_temp == NULL)
			return (NULL);
		p->char_temp = ft_itoa(data->rt);
		p->char_temp = ft_strjoin(p->token, p->char_temp);
		ft_strlcpy(p->token, p->char_temp, ft_strlen(p->char_temp) + 1);
		p->n += ft_strlen(ft_itoa(data->rt));
		free(p->char_temp);
		ptr++;
	}
	else if (*ptr != '\0' && *ptr != ' ')
	{
		while (*ptr != '\0' && *ptr != ' ' && *ptr != '$')
		{
			if (p->in_double && *ptr == '"')
				break ;
			if (!p->in_single && !p->in_double && is_new_token(*ptr, *(ptr + 1)) > 0)
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
			ft_strlcpy(&p->token[ft_strlen(p->token)], getenv(p->char_temp), ft_strlen(getenv(p->char_temp)) + 1);
			p->n += ft_strlen(getenv(p->char_temp));
			free(p->char_temp);
			p->char_temp = NULL;
		}
	}
	else
		p->token[p->n++] = '$';
	// if (*ptr == '$')
	// 	ptr = handle_dollar(ptr, p, data);
	return (ptr);
}

static char	*get_next_token(t_data *data, t_parser *p)
{
	char	*ptr;

	p->n = 0;
	ptr = data->prompt;

	while (*ptr != '\0')
	{
		if (*ptr == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (*ptr == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (*ptr == '$' && !p->in_single)
		{
			ptr = handle_dollar(ptr, p, data);
			if (ptr == NULL)
				return (NULL);
		}
		if (!p->in_double && !p->in_single && is_new_token(*ptr, *ptr + 1) > 0)
			ptr = handle_special_char(ptr, p, data);
		else if (*ptr != '\0')
		{
			p->token[p->n++] = *ptr;
			ptr++;
		}
	}
	if (p->n != 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	data->tokens[p->i++] = NULL;
	while (p->i < 10)
		free(data->tokens[p->i++]);
	return (0);
}

static void init_parser(t_data *data)
{
	int i;

	i = 10;
	data->tokens = (char **)ft_calloc(i, sizeof(char*));
	if (data->tokens == NULL)
		exit(write(1, "Error: malloc failed\n", 21));
	while (i-- > 0)
	{
		data->tokens[i] = (char *)ft_calloc(10000, sizeof(char));
		if(data->tokens[i] == NULL)
			exit(write(1, "Error: malloc failed\n", 21));
	}
}

int	lexical_analyzer(t_data *data)
{
	t_parser	*p;

	if (data->prompt[0] == '\0')
		return (0);
	p = &data->p;
	p->i = 0;
	p->n = 0;
	p->in_double = 0;
	p->in_single = 0;
	init_parser(data);
	ft_bzero(p->token, 250);
	get_next_token(data, p);
	int i = 0;
	while (data->tokens[i] != NULL)
	 	printf("'%s'\n", data->tokens[i++]);
	printf("---------------------------\n");
	
	return (0);
}