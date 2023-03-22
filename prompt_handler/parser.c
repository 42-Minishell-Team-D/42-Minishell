#include "../libs/minishell.h"
/*
static int find_echo_var(char *arg, int n, int init, t_data *data)
{
	char	*var;


	return (n);
}

void parser(char *prompt, t_data *data)
{
	char	**tokens;
	int		n;
	int		i;
	int		in_single;
	int		in_double;

	in_single = 0;
	in_double = 0;

	// the ideia is to separate the inputs into tokens
	// each token is the whole command like "echo -n asas 'hii'"
	// But first we need to try see how many arguments it has
	// So we can allocate memory to it in the binary tree

	i = 0;
	n = 0;
	while (prompt[n])
	{
		while (!in_single && !in_double && prompt[n] == ' ')
			n++;
		if (prompt[n] == '$' && !in_single)
			tokens[i++] = find_echo_var(prompt, n, n, data);
	}
}
*/