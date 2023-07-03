#include "../../libs/minishell.h"

static int	exec_echo_print(char **split, int i, int n)
{
	char	*str;

	while (split[n] != NULL)
	{
		i = 0;
		str = split[n];
		if (str[i] == '$' && str[i + 1] != '\0')
			write(1, "\n", 1);
		while (str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		if (split[n + 1] != NULL)
			write(1, " ", 1);
		n++;
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		write(1, "\n", 1);
	return (0);
}

int	exec_echo(char **split)
{
	int		i;
	int		n;

	i = 0;
	n = 1;
	if (split[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	exec_echo_print(split, i, n);
	return (0);
}
