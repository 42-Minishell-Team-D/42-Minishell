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
	else if (c == '<' && c2 != '<')
		return (LESS);
	else if (c == '>' && c2 != '>')
		return (GREAT);
	else if (c == '|' && c2 != '|')
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
