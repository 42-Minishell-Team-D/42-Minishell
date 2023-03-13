#include "../libs/minishell.h"

int	exec_echo(char *arg, int n, int	in_single, int	in_double)
{
	
	while (arg[n] != '\0')
	{
		if (arg[n] == '\'')
		{
			if (in_single == 0 && in_double == 0)
			{
				in_single = 1;
				n++;
				continue ;
			}
			else if (in_single == 1)
			{
				in_single = 0;
				n++;
				continue ;
			}
		}
		if (arg[n] == '"')
		{
			if (in_single == 0 && in_double == 0)
			{
				in_double = 1;
				n++;
				continue ;
			}
			else if (in_double == 1)
			{
				in_double = 0;
				n++;
				continue ;
			}
		}
		write(2, &arg[n++], 1);
	}
	write(2, "\n", 1);
	return (0);
}

void	exec_exit(char *p)
{
	int	ret;

	rl_clear_history();
	if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't' && p[4] == '\0')
	{
		free(p);
		exit(0);
	}
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't' && p[4] == ' ' && p[5] == '0')
	{
		free(p);
		exit(0);
	}
	ret = ft_atoi(p + 5); // + 5 is used to only get the argument of exit
	if (ret == 0)
		ret = 1;
	else if (ret < 0)
		ret = 256 - ((ret * -1) % 256);	// modulo calcul
	free (p);
	exit (ret);	// That causes leak, even if free(prompt); is implemented
}

int	exec_export(char *p)
{
	if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't')
		printf("print export\n");
    return (0);
}

int	exec_unset(char *p)
{
	if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't' && p[5] == '\0')
		return (0);
    return (0);
}