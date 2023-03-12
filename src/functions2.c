#include "../libs/minishell.h"

int	exec_echo(char *args, int n, size_t i)
{
	int	single;
	int	_double;

	single = 0;
	_double = 0;
	(void)i;
	while(args[n])
	{
		if (args[n] == '\'')
		{
			if (single == 1)
			{
				single = 0;
				n++;
				continue ;
			}
		}
		write(2, &args[n++], 1);
	}
	write(2, "\n", 1);
	return (0);
}

/*
int	exec_echo(char *args, int n, size_t i)
{
	while (args[n])
	{
		if (args[n][0] == '\'')
			while (i < ft_strlen((const char*)args[n]) - 1)
				write(2, &args[n][i++], 1);
		else
			{
				while (i < ft_strlen((const char*)args[n]) - 1)
				{
					if (args[n][i] == '"' )
						i++;
					else
						write(2, &args[n][i++], 1);
				}
			}
		n++;
		i = 1;
		if (args[n])
			write(2, " ", 1);
	}
	printf("\n");
	return (0);
}
*/
