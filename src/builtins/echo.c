#include "../../libs/minishell.h"

int	exec_echo(char **split)
{
	int		n;

	n = 1;
	if (split[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	while (split[n] != NULL)
	{
		if (split[n + 1] != NULL)
			ft_printf_fd(1, "%s ", split[n++]);
		else
		{
			ft_printf_fd(1, "%s", split[n++]);
			break ;
		}
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		write(1, "\n", 1);
	return (0);
}
