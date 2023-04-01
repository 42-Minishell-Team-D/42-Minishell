#include "../../libs/minishell.h"

int valid_odd_token(char *token)
{
	char	*valid_odd_inputs[] = {"|", ">", "<", ">>", "<<", NULL};
    int     i;
    
    i = 0;
    while (ft_strncmp(token, valid_odd_inputs[i], 100) != 0)
        i++;
    if (valid_odd_inputs[i] == NULL)
        return (1);
    return (0);
}

int valid_even_token(char *token)
{
	char	*valid_even_inputs[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int     i;
    
    i = 0;
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