#include "../libs/minishell.h"

int main ()
{
	char *prompt;
	
	while (ft_strncmp(prompt, "exit", 4))
	{
		prompt = readline("$");
		printf("input: %s  //  Type exit to stop the program\n", prompt);
	}
	return (0);
}