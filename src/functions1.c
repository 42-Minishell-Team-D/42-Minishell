#include "../libs/minishell.h"

int	exec_prog(char *prompt)
{
	char	**args;
	int		n;
	pid_t	id;

	id = fork();
	args = ft_split(prompt, ' ');
	if (id == 0)
		execve(args[0], args, NULL); // exec the executable with the arguments
	n = 0;
	while (args[n])
		free(args[n++]);
	return (0);
}
