#include "../libs/minishell.h"

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
}

int	exec_echo(char *arg, int n, t_data *data)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (arg[n] == ' ')
		n++;
	while (arg[n] != '\0')
	{
    	if (arg[n] == '\'' && !in_double)
    	    in_single = !in_single;
    	else if (arg[n] == '"' && !in_single)
    	    in_double = !in_double;
		else if (arg[n] == '$' && !in_single)
			n += find_echo_var(arg, n, n, data);
    	else
    	    printf("%c", arg[n]);
    	n++;
	}
	printf("\n");
	return (0);
}
