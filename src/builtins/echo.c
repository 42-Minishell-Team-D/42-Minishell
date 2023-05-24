#include "../../libs/minishell.h"

int	exec_echo(char **args, int n, t_data *data)
{
	int		in_single;
	int		in_double;
	int		i;
	char	*str;

	in_single = 0;
	in_double = 0;
	i = 0;
	(void)data;
	while (args[n] != NULL)
	{
		str = args[n];
		while (str[i] != '\0')
		{
			if (str[i] == '\'' && !in_double)
				in_single = !in_single;
			else if (str[n] == '"' && !in_single)
				in_double = !in_double;
			else
				ft_printf_fd(1, "%c", str[n]);
			n++;
		}
	}
	printf("\n");
	return (0);
}
