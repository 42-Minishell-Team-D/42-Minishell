#include "../libs/minishell.h"

int	exec_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else 
		return (1);
	return (0);
}


int	exec_env(void)
{
	extern char **environ;

	while (*(environ + 2) != NULL)
    	printf("%s\n", *environ++);
	return (0);
}