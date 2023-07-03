#include "../../libs/minishell.h"

static void	free_and_exit(t_data *data, int ret, char *join, char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	free(join);
	free_after_execution(data);
	rl_clear_history();
	free_at_exit(data);
	exit (ret);
}

int	exec_exit_else(char **split, t_data *data, int i, char *join)
{
	int	ret;

	ret = 0;
	if (split[1][i] == '-' && split[1][i + 1] != '\0')
		i++;
	while (split[1][i] != '\0')
	{
		if (ft_isdigit(split[1][i++]) == 0)
		{
			ft_printf_fd(2, "minishell: exit: %s: \
			numeric argument required\n", split[1]);
			free_and_exit(data, 2, join, split);
		}
	}
	ret = ft_atoi(split[1]);
	return (ret);
}

int	exec_exit(char **split, t_data *data, int i, char *join)
{
	int	ret;

	ret = 0;
	if (split[1] == NULL)
		free_and_exit(data, 0, join, split);
	else
		ret = exec_exit_else(split, data, i, join);
	if (split[2] != NULL)
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		return (0);
	}
	if (ret > 255)
		ret = ret % 256;
	if (ret < 0)
		ret = 256 - ((ret * -1) % 256);
	free_and_exit(data, ret, join, split);
	return (0);
}
