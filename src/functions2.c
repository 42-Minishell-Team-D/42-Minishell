#include "../libs/minishell.h"

int find_echo_var(char *arg, int n, int init, t_data *data)
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

void	exec_exit(char *p)
{
	int	ret;

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