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
	{
		execve(args[0], args, NULL);
	}
	n = 0;
	while (args[n])
		free(args[n++]);
	return (0);
}

void exec_exit(char *p)
{
	int ret;

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