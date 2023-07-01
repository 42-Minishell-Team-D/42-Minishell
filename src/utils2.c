#include "../libs/minishell.h"

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

static int	determine_args(char *ptr, t_parser *p)
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

int	get_biggest_len(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

char	*ft_getenv(char *name, char **env)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			ret = ft_strdup(env[i] + ft_strlen(name) + 1);
			break ;
		}
		i++;
	}
	return (ret);
}

char	*delete_char(char *str, int index)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (i != index)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

// should return a string that is the copy of the string given as argument 
// starting at index i, until it finds the character c
char	*ft_strcdup(const char *s1, int i, char c)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) - i + 1));
	if (!str)
		return (NULL);
	while (s1[i] && s1[i] != c)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}