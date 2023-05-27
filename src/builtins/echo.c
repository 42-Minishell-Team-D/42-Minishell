#include "../../libs/minishell.h"

int	exec_echo(char **split)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 1;
	// print_tokens(split);
	if (split[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	while (split[n] != NULL)
	{
		i = 0;
		str = split[n];
		if (str[i] == '$' && str[i + 1] != '\0')
			write(1, "\n", 1);
		while (str[i] != '\0')
		{
			// ft_printf_fd(1, "%c", str[i]);
			write(1, &str[i], 1);
			i++;
		}
		if (split[n + 1] != NULL)
		{
			// ft_printf_fd(1, " ", str[i]);
			write(1, " ", 1);
		}
		n++;
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		write(1, "\n", 1);

	return (0);
}
