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
	char		**temp;

	temp = environ;
	while (*(temp + 2) != NULL)
    	printf("%s\n", *temp++);
	return (0);
}

int exec_cd(char *prompt)
{
	char	*temp;

	temp = prompt + 3;
	if (*temp != '\0')
		chdir(temp);
	else
		chdir("/");
	return (0);
}
