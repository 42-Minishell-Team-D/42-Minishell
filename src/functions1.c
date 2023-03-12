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
	while (*(temp + 2) != NULL)		// +2 because the first two elements of the environ array are reserved for the program name and arguments
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

int exec_prog(char *prompt)
{
	char	**args;
	int			n;
	pid_t		id;

	id = fork();
	if (id == -1)
		return (1);
	args = ft_split(prompt, ' ');
	if (id == 0)
		execve(args[0], args, NULL); // exec the executable with the arguments
	n = 0;
	while (args[n])
		free(args[n++]);
	return (0);
}