#include "../../libs/minishell.h"

int		get_number_of_processes(t_bt *tree)
{
	int		count;
	t_bt	*left_tree;

	count = 0;
	count++;
	while (tree != NULL)
	{
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			while (left_tree != NULL)
			{
				count++;
				left_tree = left_tree->right;
			}
		}
		left_tree = tree->left;
		tree = tree->right;
	}
	// printf("Number of processes: %d\n", count);
	return (count);
}

void	close_unused_pipes(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < get_number_of_processes(data->tree) + 1)
	{
		if (j != i)
		{
			if (data->pipes[j][0] != 0)
				if (close(data->pipes[j][0]) == -1)
					printf("Close failed pipe[%d][0]\n", j);
			if (data->pipes[j][1] != 0)
				if (close(data->pipes[j][1]) == -1)
					printf("Close failed pipe[%d][1]\n", j);
		}
		j++;
	}
}

void	close_free_pipes_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < get_number_of_processes(data->tree) + 1)
	{
		if (data->pipes[i][0] != 0)
			if (close(data->pipes[i][0]) == -1)
				printf("Close failed pipe[%d][0]\n", i);
		if (data->pipes[i][1] != 0)
			if (close(data->pipes[i][1]) == -1)
				printf("Close failed pipe[%d][1]\n", i);
		if (data->pipes != NULL)
			free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	if (data->pipes != NULL)
		free(data->pipes);
	if (data->pids != NULL)
		free(data->pids);
}

// uncomment this executor() function and comment out other one down below to test

/*void	executor(t_data *data)
{
	t_bt	*tree ;
	t_bt	*left_tree;

	if (init_executor(data) == 1)
		return ;

	// write()
	tree = data->tree;
	while (tree != NULL)
	{
		data->pids[tree->id - 1] = fork();
		if (data->pids[tree->id - 1] == -1)
		{
			close_free_pipes_pids(data);
			perror("Fork failed");
			return ;
		}
		else if (data->pids[tree->id -1] == 0)
		{
			close_unused_pipes(data, tree->id - 1);
			dup2(data->pipes[tree->id - 1][1], 1);	// write
			dup2(data->pipes[tree->id - 1][0], 0);  // read
			printf("pipe[%d][0]: %d\n", tree->id - 1, data->pipes[tree->id - 1][0]);
			printf("pipe[%d][1]: %d\n", tree->id - 1, data->pipes[tree->id - 1][1]);
			redirect(tree, data);
			return ;
		}
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			redirect(left_tree, data);
		}
		tree = tree->right;
	}
	wait(NULL);

	close_free_pipes_pids(data);
}*/

void	executor(t_data *data)
{
	t_bt	*tree;
	// t_bt	*left_tree;


	tree = data->tree;
	if (init_executor(data))
		return ;
	while (tree != NULL)
	{
		if (tree->id == 1)
			redirect(tree, data);
		tree = tree->right;
	}

	/*tree = data->tree;
	while (tree != NULL)
	{
		redirect(tree, data);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			redirect(left_tree, data);
		}
		tree = tree->right;
	}*/
	
	/*char **split = ft_split(data->tokens[0], ' ');
	int pid = fork();
	if (pid == 0)
	{
		if (ft_strncmp(split[0], "env", 3) == 0)
			exec_env(data);
		else
		{
			char *join = ft_strjoin("/bin/", split[0]);
			execve(split[0], split, data->env);
			execve(join, split, data->env);
		}
		kill(getpid(), SIGKILL);
	}
	wait(NULL);*/
}
