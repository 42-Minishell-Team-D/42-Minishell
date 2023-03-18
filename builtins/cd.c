#include "../libs/minishell.h"

int	exec_cd(char *prompt)
{
	char	*temp;

	temp = prompt + 3;
	if (*temp != '\0')
		chdir(temp);
	else
		chdir("/");
	return (0);
}