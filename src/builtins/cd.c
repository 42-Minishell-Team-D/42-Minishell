#include "../../libs/minishell.h"

int	exec_cd(char **split, int i, int in_single, int in_double)
{
	if (split[1] == NULL)
		return (chdir(getenv("HOME")));
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(split[1]) == -1)
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", split[1]);
	while (split[1][i] != '\0')
	{
		if (split[1][i] == '\'' && in_double == 0)
			in_single = !in_single;
		if (split[1][i] == '\"' && in_single == 0)
			in_double = !in_double;
		if ((split[1][i] == ' ' || split[1][i] == '\0') && in_single == 0 && in_double == 0)
			break ;
		i++;
	}
	return (0);
}
