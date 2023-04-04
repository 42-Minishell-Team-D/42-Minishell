#include "../../libs/minishell.h"

int	valid_odd_token(char *token)
{
	int		i;
	char	**valid_odd_inputs;

	i = 0;
	valid_odd_inputs = {"|", ">", "<", ">>", "<<", NULL};
	while (ft_strncmp(token, valid_odd_inputs[i], 3) != 0)
		i++;
	if (valid_odd_inputs[i] == NULL)
		return (1);
	return (0);
}

int	valid_even_token(char *token)
{
	int		i;
	char	**valid_even_inputs;

	i = 0;
	valid_even_inputs = {"echo\0", "echo ", "cd\0", "cd " "pwd\0", "pwd ",\
	"export\0", "export ","unset\0", "unset ", "env\0", "env ", "exit\0", "exit ", NULL};
	while (ft_strncmp(token, valid_even_inputs[i], 100) != 0)
		i++;
	if (valid_even_inputs[i] == NULL)
		return (1);
	return (0);
}

int	check_invalid_inputs(char **tokens)
{
	int		i;

	i = 0;
    while (tokens[i] != NULL)
    {
        if (i % 2 == 0)
        {
            if (valid_even_token(tokens[i]) == 0)
                return (0);
        }
        else
            if (valid_odd_token(tokens[i]) == 0)
                return (0);
        i++;
    }
    return (1);
}