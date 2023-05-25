#include "../../libs/minishell.h"

int	exec_echo(char **split, t_data *data)
{
	int		in_single;
	int		in_double;
	int		i;
	int		n;
	char	*str;

	in_single = 0;
	in_double = 0;
	i = 0;
	n = 1;
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	while (split[n] != NULL)
	{
		str = split[n];
		while (str[i] != '\0')
		{
			if (str[i] == '\'' && !in_double)
				in_single = !in_single;
			else if (str[i] == '"' && !in_single)
				in_double = !in_double;
			else
				ft_printf_fd(1, "%c", str[i]);
			i++;
		}
		n++;
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		ft_printf_fd(1, "\n", str[i]);

	(void)data;
	return (0);
}
