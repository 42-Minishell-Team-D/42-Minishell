#include "../../libs/minishell.h"

void	valid_odd_token(char *p, t_data *data)
{
	if (p[0] == 'e' && p[1] == 'c' && p[2] == 'h' && p[3] == 'o' && (p[4] == '\0' || p[4] == ' '))
		printf("echo\n");
	else if (p[0] == 'c' && p[1] == 'd' && (p[2] == '\0' || p[2] == ' '))
		printf("cd\n");
	else if (p[0] == 'p' && p[1] == 'w' && p[2] == 'd' && p[3] == '\0')
		printf("pwd\n");
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't' && (p[6] == '\0' || p[6] == ' '))
		printf("export\n");
	else if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't' && (p[5] == '\0' || p[5] == ' '))
		printf("unset\n");
	else if (p[0] == 'e' && p[1] == 'n' && p[2] == 'v' && p[3] == '\0')
		printf("env\n");
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't' && (p[4] == '\0' || p[4] == ' '))
		printf("exit\n");
	else
		printf("minishell: %s command not found :/\n", p);
	(void)data;
}

static void	pipe_child(int id, char *join, char **split, t_data *data)
{
	join = ft_strjoin("/bin/", split[0]);
	if (id == 0)
	{
		// ft_printf_fd(1, "id: 0 child writing to: %d\n", data->pipes[id][1]);
		// ft_printf_fd(1, "id: 0 child reading from: %d\n", 0);
		dup2(data->pipes[id][1], 1);
	}
	else
	{
		// ft_printf_fd(1, "id : %d child reading from: %d\n", id, data->pipes[id - 1][0]);
		dup2(data->pipes[id - 1][0], 0);
		// ft_printf_fd(1, "id : %d child writing to: %d\n", id, data->pipes[id][1]);
		dup2(data->pipes[id][1], 1);
	}

	execve(join, split, data->env);
	execve(split[0], split, data->env);
	// ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", split[0]);
	while (split[id])
		free(split[id++]);
	free(split);
	free(join);
	write(1, "\0", 1);
	kill(getpid(), SIGKILL);
	exit(0);
}

void	redirect_pipe(t_bt *tree, t_data *data)
{
	int		pid;
	char	**split;
	char	*join;

	join = NULL;
	split = ft_split_args(tree->args, &data->p);
	int id = tree->id / 2;
	pid = fork();
	if (pid == 0)
		pipe_child(id, join, split, data);
	id = 0;
	while (split[id])
		free(split[id++]);
	free(split);

	// wait(&data->rt);
	// data->rt = WEXITSTATUS(data->rt);
	// else
	// {
	// 	wait(&data->rt);
	// 	data->rt = WEXITSTATUS(data->rt);
	// }
}

t_bt	*redirect_great(t_bt *tree, t_data *data, int option)
{
	int		fd;
	char	buf[1024];
	int		rd;

	if (option == GREAT)
		fd = open(tree->args, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tree->args, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf_fd(2, "minishell: %s: failed to open/create file :/\n", tree->args);
		return (tree->parent);
	}
	rd = read(data->pipes[tree->id / 2 - 1][0], buf, 1024);
	while (rd > 0)
	{
		write(fd, buf, rd);
		rd = read(fd, buf, 1024);
	}
	close(fd);
	return(tree->parent);
}