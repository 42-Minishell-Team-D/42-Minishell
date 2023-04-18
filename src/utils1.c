#include "../libs/minishell.h"

int	array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	search_var(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	nb_char_max(char **s)
{
	int		i;
	size_t	ret;
	
	i = 0;
	ret = 0;
	while (i < array_size(s))
	{
		if (ret < ft_strlen(s[i]))
			ret = ft_strlen(s[i]);
		i++;
	}
	return (ret);
}

int	is_new_token(char c, char c2)
{
	if (c2 && c == '<' && c2 == '<')
		return (LESSLESS);
	else if (c2 && c == '>' && c2 == '>')
		return (GREATGREAT);
	else if (c == '<')
		return (LESS);
	else if (c == '>')
		return (GREAT);
	else if (c == '|')
		return (PIPE);
	return (0);
}

int	is_new_readline(char *token)
{
	if (ft_strncmp(&token[ft_strlen(token) - 1], "'\0", 2) == 0)
		return (1);
	else if (token[ft_strlen(token) - 1] == '"')
		return (1);
	else if (token[ft_strlen(token) - 1] == '|')
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}


static int determine_args(char *ptr, t_parser *p)
{
	p->n = 1;
	while (ptr[p->i])
	{
		if (ptr[p->i] == '"' && !p->in_single)
			p->in_double = !p->in_double;
		if (ptr[p->i] == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		if (ptr[p->i] == ' ' && !p->in_double && !p->in_single)
			p->n++;
		p->i++;
	}
	return (p->n + 1);

}

char	**ft_split_args(char *token, t_parser *p)
{
	char	**split;

	reset_p_vars(p);
	if (!token)
		return (NULL);
	split = (char **)ft_calloc(sizeof(char *), determine_args(token, p));
	reset_p_vars(p);
	while (token[p->i])
	{
		if (token[p->i] == '"' && !p->in_single)
			p->in_double = !p->in_double;
		else if (token[p->i] == '\'' && !p->in_double)
			p->in_single = !p->in_single;
		else if (token[p->i] == ' ' && !p->in_double && !p->in_single)
		{
			split[p->n] = (char *)ft_calloc(sizeof(char), p->i + 1 - p->temp);
			ft_strlcpy(split[p->n++], &token[p->temp], p->i + 1 - p->temp);
			p->temp = p->i + 1;
		}
		p->i++;
	}
	split[p->n] = (char *)ft_calloc(sizeof(char), p->i + 1 - p->temp);
	ft_strlcpy(split[p->n++], &token[p->temp], p->i + 1 - p->temp);
	return (split);
}