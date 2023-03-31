#include "../../libs/minishell.h"

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
	exit (ret);
}
