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

static int builtin_checker(char **split, t_data *data)
{
	data->rt = 1;
	if (ft_strncmp(split[0], "cd\0", 2) == 0 || ft_strncmp(split[0], "cd ", 3) == 0)
		data->rt = exec_cd(split[1]);
	// else if (ft_strncmp(split[0], "pwd\0", 3) == 0 || ft_strncmp(split[0], "pwd ", 4) == 0)
	// 	data->rt = exec_pwd();
	// else if (ft_strncmp(split[0], "echo\0", 4) == 0 || ft_strncmp(split[0], "echo ", 5) == 0)
	// 	data->rt = exec_echo(split);
	else if (ft_strncmp(split[0], "export\0", 7) == 0 || ft_strncmp(split[0], "export ", 7) == 0)
		data->rt = exec_export(split, data);
	else if (ft_strncmp(split[0], "unset\0", 5) == 0 || ft_strncmp(split[0], "unset ", 6) == 0)
		data->rt = exec_unset(split, data);
	else if (ft_strncmp(split[0], "env\0", 3) == 0 || ft_strncmp(split[0], "env ", 4) == 0)
		data->rt = exec_env(data);
	else if (ft_strncmp(split[0], "exit\0", 4) == 0 || ft_strncmp(split[0], "exit ", 5) == 0)
		exec_exit(split);
	// else					// Yes, copilot did this :D //
	return (data->rt);
}

static void	pipe_child(char *join, char **split, t_bt * tree, t_data *data)
{
	int id;

	id = tree->id / 2;
	if (id == 0)
	{
		// ft_printf_fd(1, "id: 0 child writing to: %d\n", data->pipes[id][1]);
		// ft_printf_fd(1, "id: 0 child reading from: %d\n", 0);
		if (tree->right != NULL)
			dup2(data->pipes[id][1], 1);
	}
	else
	{
		// ft_printf_fd(1, "id : %d child reading from: %d\n", id, data->pipes[id - 1][0]);
		dup2(data->pipes[id - 1][0], 0);
		// ft_printf_fd(1, "id : %d child writing to: %d\n", id, data->pipes[id][1]);
		if (tree->parent->right != NULL)
			dup2(data->pipes[id][1], 1);
	}
	if (builtin_checker(split, data) == 0)	// for export / unset / env this should be executed on the main process
		return ;
	execve(join, split, data->env);
	execve(split[0], split, data->env);
	ft_printf_fd(2, "minishell: %s command not found, you can do it! :D\n", split[0]);
}

void	redirect_pipe(t_bt *tree, t_data *data)
{
	int		pid;
	char	**split;
	char	*join;
	int		id;
	
	id = tree->id / 2;
	split = ft_split_args(tree->args, &data->p);
	join = ft_strjoin("/bin/", split[0]);
	pid = fork();
	if (pid == 0)
	{
		// close_unused_pipes(data, id);
		pipe_child(join, split, tree, data);
		id = 0;
		while (split[id])
			free(split[id++]);
		free(split);
		free(join);
		write(1, "\0", 1);
		kill(getpid(), SIGKILL);
		exit(0);
	}
	id = 0;
	while (split[id])
		free(split[id++]);
	free(split);
	wait(NULL);	// edge case: cat /dev/random | head -n 10
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
