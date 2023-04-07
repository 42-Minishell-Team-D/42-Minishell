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
