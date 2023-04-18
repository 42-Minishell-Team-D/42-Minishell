#include "../../libs/minishell.h"

void	valid_even_token(char *p, t_data *data)
{
	if (p[0] == '>' && p[1] == '>')
		printf(">>\n");
	else if (p[0] == '<' && p[1] == '<')
		printf("<<\n");
	else if (p[0] == '|')
		printf("|\n");
	else if (p[0] == '<')
		printf("<\n");
	else if (p[0] == '>')
		printf(">\n");
	(void)data;
}

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

void	redirect(t_bt *tree, t_data *data)
{
	int		pid;
	char	**split;
	char	*join;
	
	split = ft_split(tree->args, ' ');
	(void)data;
	pid = fork();
	if (pid == 0)
	{
		join = ft_strjoin("/bin/", split[0]);
		execve(join, split, data->env);
		execve(split[0], split, data->env);
		printf("tree->id: %d\n", tree->id);
		printf("tree->args: %s\n", tree->args);
		kill(getpid(), SIGKILL);
	}
	else
	{
		wait(&data->rt);
		data->rt = WEXITSTATUS(data->rt);
	}


	// To avoid que spam

	// if (tree->id % 2 != 0)
	// 	valid_odd_token(tree->args, data);
	// else
	// 	valid_even_token(tree->args, data);
}
