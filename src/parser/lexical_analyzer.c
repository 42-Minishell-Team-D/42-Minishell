#include "../../libs/minishell.h"

static char	*handle_special_char_2(char *ptr, int special,
									t_parser *p, t_data *data)
{
	if (special == LESSLESS)
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

static char	*handle_special_char(char *ptr, t_parser *p, t_data *data)
{
	int	special;

	special = is_new_token(*ptr, *(ptr + 1));
	if (p->n > 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	ft_bzero(p->token, p->bigger_token + 1);
	p->n = 0;
	if (special == GREATGREAT)
	{
		data->tokens[p->i][0] = '>';
		data->tokens[p->i++][1] = '>';
		return (ptr + 2);
	}
	return (handle_special_char_2(ptr, special, p, data));
}

static char	*handle_dollar_2(char *ptr, t_parser *p, t_data *data)
{
	while (*ptr != '\0' && *ptr != ' ' && *ptr != '$')
	{
		if (p->in_double && *ptr == '"')
			break ;
		if (is_new_token(*ptr, *(ptr + 1)) > 1)
			break ;
		ptr++;
		p->temp++;
	}
	p->char_temp = ft_calloc(p->temp + 1, sizeof(char));
	if (p->char_temp == NULL)
		return (NULL);
	ft_strlcpy(p->char_temp, ptr - p->temp, p->temp + 1);
	p->temp = 0;
	if (ft_getenv(p->char_temp, data->env))
	{
		ft_strlcpy(&p->token[ft_strlen(p->token)],
			ft_getenv(p->char_temp, data->env), ft_strlen(ft_getenv(p->char_temp, data->env)) + 1);
		p->n += ft_strlen(ft_getenv(p->char_temp, data->env));
		free(p->char_temp);
		p->char_temp = NULL;
	}
	return (ptr);
}

static char	*handle_dollar(char *ptr, t_parser *p, t_data *data)
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
		ptr = handle_dollar_2(ptr, p, data);
	else
		p->token[p->n++] = '$';
	if (*ptr == '$')
		ptr = handle_dollar(ptr, p, data);
	return (ptr);
}

int	lexical_analyzer(t_data *data, t_parser *p)
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
		if (!p->in_double && !p->in_single && is_new_token(*ptr, *(ptr + 1)) > 1)
			ptr = handle_special_char(ptr, p, data);
		else if (*ptr != '\0')
		{
			if (is_new_token(*ptr, *(ptr + 1)) > 0)
			{
				p->token[p->n++] = *ptr;
				ptr++;
			}
			p->token[p->n++] = *ptr;
			ptr++;
		}
	}
	if (p->n != 0)
		ft_strlcpy(data->tokens[p->i++], p->token, p->n + 1);
	data->tokens[p->i++] = NULL;
	return (0);
}
