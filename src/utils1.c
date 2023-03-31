#include "../libs/minishell.h"

int array_size(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int search_var(char **s)
{
	int i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int nb_char_max(char **s)
{
	int i;
	size_t ret;
	
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

