#include "../../libs/minishell.h"

int	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf_fd(1, "%s\n", cwd);
	else
		return (1);
	return (0);
}