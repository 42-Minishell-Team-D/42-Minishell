#include "../../libs/minishell.h"

int	exec_echo(char **split, t_data *data)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 1;
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	while (split[n] != NULL)
	{
		i = 0;
		str = split[n];
		if (str[i] == '$' && str[i + 1] != '\0')
			ft_printf_fd(1, "\n");
		while (str[i] != '\0')
		{
			ft_printf_fd(1, "%c", str[i]);
			i++;
		}
		if (split[n + 1] != NULL)
			ft_printf_fd(1, " ", str[i]);
		n++;
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		ft_printf_fd(1, "\n");

	(void)data;
	return (0);
}
