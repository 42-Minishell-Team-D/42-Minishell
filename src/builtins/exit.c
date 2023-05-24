#include "../../libs/minishell.h"

void	exec_exit(char **split)
{
	int	ret;

	rl_clear_history();

	if (split[1] == NULL)
		exit (0);
	if (split[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}

	ret = ft_atoi(split[1]); // + 5 is used to only get the argument of exit
	if (ret == 0)
		ret = 1;
	else if (ret < 0)
		ret = 256 - ((ret * -1) % 256);	// modulo calcul
	printf("ret: %i\n", ret);
	exit (ret);
}
