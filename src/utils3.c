#include "../libs/minishell.h"

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
