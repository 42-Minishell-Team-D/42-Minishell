#include "../../libs/minishell.h"

static int	builtin_checker_parent(char **split)
{
	if (ft_strncmp(split[0], "cd\0", 3) == 0)
		return (0);
	else if (ft_strncmp(split[0], "export\0", 7) == 0 && split[1] != NULL)
		return (0);
	else if (ft_strncmp(split[0], "unset\0", 6) == 0)
		return (0);
	else if (ft_strncmp(split[0], "exit\0", 5) == 0)
		return (0);
	return (1);
}

static int	builtin_executor_parent(char **split, t_data *data,
char *join, t_bt *tree)
{
	data->rt = 1;
	if (ft_strncmp(split[0], "cd\0", 3) == 0)
		data->rt = exec_cd(split);
	else if (ft_strncmp(split[0], "export\0", 7) == 0 && split[1] != NULL)
		data->rt = exec_export(split, data, tree);
	else if (ft_strncmp(split[0], "unset\0", 6) == 0 && \
	tree->id / 2 == 0 && tree->right == NULL)
		data->rt = exec_unset(split, data);
	else if (ft_strncmp(split[0], "exit\0", 5) == 0 && \
	tree->id / 2 == 0 && tree->right == NULL)
		data->rt = exec_exit(split, data, 0, join);
	return (data->rt);
}

// static void

void	redirect_pipe(pid_t *fork_id, t_bt *tree, t_data *data)
{
	char	**split;
	char	*join;
	int		id;

	id = tree->id / 2;
	split = clear_quotes(ft_split_args(tree->args, &data->p));
	join = ft_strjoin("/bin/", split[0]);
	if (ft_strncmp(split[0], "echo\0", 7) == 0 && \
	ft_strncmp(split[1], "-n\0", 3) == 0 && split[1] != NULL)
		data->slash_r = 1;
	if (builtin_checker_parent(split) > 0)
	{
		(*fork_id) = fork();
		if ((*fork_id) == 0)
		{
			init_child(id, tree, data);
			pipe_child(join, split, tree, data);
			id = 0;
			while (split[id])
				free(split[id++]);
			free(split);
			free(join);
			free_after_execution(data);
			free_at_exit(data);
			exit(0);
		}
	}
	else
		builtin_executor_parent(split, data, join, tree);
	free(join);
	if (id == 0 && tree->right != NULL && data->pipes[id][1] > 0)
		close(data->pipes[id][1]);
	else if (id > 0 && tree->parent->right != NULL && data->pipes[id][1] > 0)
		close(data->pipes[id][1]);
	id = 0;
	while (split[id])
		free(split[id++]);
	free(split);
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
		ft_printf_fd(2, "minishell: %s: \
failed to open/create file :/\n", tree->args);
		return (tree->parent);
	}
	rd = read(data->pipes[tree->id / 2 - 1][0], buf, 1024);
	while (rd > 0)
	{
		write(fd, buf, rd);
		rd = read(data->pipes[tree->id / 2 - 1][0], buf, 1024);
	}
	close(fd);
	return (tree->parent);
}
