#include "../../libs/minishell.h"

static int	builtin_executor_child(char **split, t_data *data)
{
	data->rt = 1;
	if (ft_strncmp(split[0], "pwd\0", 4) == 0)	// bon
		data->rt = exec_pwd();
	else if (ft_strncmp(split[0], "echo\0", 5) == 0)
		data->rt = exec_echo(split);
	else if (ft_strncmp(split[0], "export\0", 7) == 0 && split[1] == NULL)
		data->rt = exec_export(split, data);
	else if (ft_strncmp(split[0], "env\0", 4) == 0)
		data->rt = exec_env(data);
	// else					// Yes, copilot did this but so so :D //
	return (data->rt);
}

void init_child(int id, t_bt *tree, t_data *data)
{
	close_unused_pipes(id, tree, data);

	// ft_printf_fd(1, "closed data->pipes[%d][1] = %d\n", id, data->pipes[id][1]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	(void)tree; (void)data; (void)	id;
}


void	pipe_child(char *join, char **split, t_bt * tree, t_data *data)
{
	int	id;

	id = tree->id / 2;
	if (id == 0)
	{
		if (data->fd_in[0] > 0)
		{
			close(data->fd_in[1]);
			dup2(data->fd_in[0], 0);
			ft_printf_fd(1, "id: 0 child reading from: %d\n", data->fd_in[0]);
		}
		else
			ft_printf_fd(1, "id: 0 child reading from: %d\n", 0);
		if (tree->right != NULL)
		{
			ft_printf_fd(1, "id: 0 child writing to: %d\n", data->pipes[id][1]);
			dup2(data->pipes[id][1], 1);
		}
		else
			ft_printf_fd(1, "id: 0 child writing to: %d\n", 1);
	}
	else
	{
		ft_printf_fd(1, "id: %d child reading from: %d\n", id, data->pipes[id - 1][0]);
		dup2(data->pipes[id - 1][0], 0);
		if (tree->parent->right != NULL)
		{
			ft_printf_fd(1, "id: %d child writing to: %d\n", id, data->pipes[id][1]);
			dup2(data->pipes[id][1], 1);
		}
		else
			ft_printf_fd(1, "id: %d child writing to: %d\n", id, 1);
	}
	if (builtin_executor_child(split, data) == 0)	// for export / unset / env this should be executed on the main process
		return ;
	
	execve(join, split, data->env);
	execve(split[0], split, data->env);
	write(1, "\0", 1);
	ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", split[0]);
}
	/*int pid = fork();
	if (pid == 0)
	{
		execve(join, split, data->env);
		execve(split[0], split, data->env);
		ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", split[0]);
		exit(1);
	}
	write(1, "\0", 1);
	if (id != 0)
	{
		if (close(data->pipes[id - 1][1]) >= 0)
			ft_printf_fd(2, "closed data->pipes[%d][1] = %d\n", id - 1, data->pipes[id - 1][1]);

	}*/