#include "../../libs/minishell.h"

// static char *get_env(char *str, char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;

// 	i = 0;
// 	j = 0;
// 	while (env[i] != NULL)
// 	{
// 		printf("ft_strncmp(str, env[i], get_biggest_len(str, env[i])) = %i\n", ft_strncmp(str, env[i], get_biggest_len(str, env[i])));
// 		if (ft_strncmp(str, env[i], get_biggest_len(str, env[i])) == 0)
// 		{
// 			tmp = ft_strdup(env[i]);
// 			while (tmp[j] != '=')
// 				j++;
// 			ft_printf_fd(1, "%s", str + j + 1);
// 			return ("\0");
// 		}
// 		i++;
// 	}
// 	ft_printf_fd(1, "that's a test\n");
// 	return ("\0");
// }

int	exec_echo(char **split, t_data *data)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 1;
	while (ft_strncmp(split[n], "-n\0", 3) == 0)
		n++;
	while (split[n] != NULL)
	{
		i = 0;
		str = split[n];
		// if (str[i] == '$')
		// 	str = get_env(str + 1, data->env);
		while (str[i] != '\0')
		{
			ft_printf_fd(1, "%c", str[i]);
			i++;
		}
		if (split[n + 1] != NULL)
			ft_printf_fd(1, " ", str[i]);
		n++;
	}
	if (ft_strncmp(split[1], "-n\0", 3) != 0)
		ft_printf_fd(1, "\n", str[i]);

	(void)data;
	return (0);
}
