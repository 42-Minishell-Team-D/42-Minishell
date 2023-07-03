#include "../../libs/minishell.h"

char	*get_before_equal_sign(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '\0' && var[i] != '=')
		i++;
	return (ft_substr(var, 0, i));
}

char	*get_before_equal_sign_export(char *var)
{
	var = get_before_equal_sign(var);
	// remove "declare -x " from the variable
	if (ft_strncmp(var, "declare -x ", 11) == 0)
		var = ft_substr(var, 11, ft_strlen(var));
	return (var);
}


// char	*get_before_equal_sign(char *var)
// {
// 	int	i;

// 	i = 0;
// 	while (var[i] != '\0' && var[i] != '=')
// 		i++;
// 	return (ft_substr(var, 0, i));
// }

// char	*get_before_equal_sign_export(char *var)
// {
// 	char	*join;

// 	join = get_before_equal_sign(var);
// 	free(var);
// 	var = ft_strjoin(join, "\0");
// 	free(join);
// 	if (ft_strncmp(var, "declare -x ", 11) == 0)
// 	{
// 		join = ft_substr(var, 11, ft_strlen(var));
// 		free(var);
// 		var = ft_strjoin(join, "\0");
// 		free(join);
// 	}
// 	return (var);
// }
