#include "../libs/minishell.h"
/*
static int find_echo_var(char *arg, int n, int init, t_data *data)
{
	char	*var;

	if (arg[n + 1] == ' ' || arg[n + 1] == '\0')
		return (printf("$"));
	while (arg[n] != ' ' && arg[n] != '\0')
		n++;
	var = (char *)malloc((n - init) * sizeof(char));
	ft_strlcpy(var, &arg[init + 1], n - init);
	if (var[0] == '?' && var[1] == '\0')
		printf("%d ", data->rt);
	else if (getenv(var))
		printf("%s ", getenv(var));
	free(var);
	return (n);
}*/

void parser(char *prompt)
{
	/*char	**tokens;
	int		n;
	int		i;
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;

	*/(void)prompt;/*

	// the ideia is to separate the inputs into tokens
	// each token is the whole command like "echo -n asas 'hii'"
	// But first we need to try see how many arguments it has
	// So we can allocate memory to it

	i = 0;
	n = 0;
	while (prompt[n])
	{
		while (!in_single && !in_double && prompt[n] == ' ')
			n++;
		if (prompt[n] == '$' && !in_single)
			tokens[i++] = find_echo_var();
		
	}*/
}