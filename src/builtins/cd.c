#include "../../libs/minishell.h"

int	exec_cd(char **split)
{
	if (split[1] == NULL)
		return (chdir(getenv("HOME")));
	if (split[2] != NULL)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (chdir(split[1]) == -1)
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", split[1]);
	return (0);
}
