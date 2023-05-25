#include "../../libs/minishell.h"

char	**clear_quotes(char **split)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (split[i] != NULL)
	{
		if (split[i][0] == '\'' || split[i][0] == '"')
		{
			str = split[i];
			j = 0;
			while (str[j] != '\0')
			{
				str[j] = str[j + 1];
				j++;
			}
			str[j - 2] = '\0';
		}
		i++;
	}
	return (split);
}
