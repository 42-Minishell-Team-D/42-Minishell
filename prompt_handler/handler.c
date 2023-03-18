#include "../libs/minishell.h"

void divide_prompt(t_command *cmd)
{
	int	n;
	int	i;

	n = 0;

	// the ideia is to separate the inputs into tokens
	// each token is the whole command like "echo -n asas 'hii'"
	// But first we need to try see how many arguments it has
	// So we can allocate memory to it


	/*while(cmd->prompt[n] == ' ')
		n++;
	i = 0;
	while (cmd->prompt[n] != ' ' || cmd->prompt[n] != '\0')
	{
		i++;
		n++;
	}*/
}