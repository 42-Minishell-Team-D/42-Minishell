#include "../../libs/minishell.h"

char	**clear_quotes(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '\'' || split[i][0] == '"')
		{
			split[i][ft_strlen(split[i]) - 1] = '\0';
			delete_char_filter(&split[i][0]);
		}
		i++;
	}
	return (split);
}
