#include "../../libs/minishell.h"

int	valid_even_token(char *token)
{
	int		i;
	char	*valid_even_token[6];

	i = 0;
	valid_even_token[0] = "|";
	valid_even_token[1] = ">";
	valid_even_token[2] = "<";
	valid_even_token[3] = ">>";
	valid_even_token[4] = "<<";
	valid_even_token[5] = NULL;
	while (valid_even_token[i] != NULL && \
	ft_strncmp(token, valid_even_token[i], 3) != 0)
		i++;
	if (valid_even_token[i] == NULL)
		return (1);
	return (0);
}

int	valid_odd_token(char *token)
{
	int		i;
	char	*valid_odd_token[15];

	i = 0;
	valid_odd_token[0] = "echo\0";
	valid_odd_token[1] = "echo ";
	valid_odd_token[2] = "cd\0";
	valid_odd_token[3] = "cd ";
	valid_odd_token[4] = "pwd\0";
	valid_odd_token[5] = "pwd ";
	valid_odd_token[6] = "export\0";
	valid_odd_token[7] = "export ";
	valid_odd_token[8] = "unset\0";
	valid_odd_token[9] = "unset ";
	valid_odd_token[10] = "env\0";
	valid_odd_token[11] = "env ";
	valid_odd_token[12] = "exit\0";
	valid_odd_token[13] = "exit ";
	valid_odd_token[14] = NULL;
	while (valid_odd_token[i] != NULL && \
	ft_strncmp(token, valid_odd_token[i], 100) != 0)
		i++;
	if (valid_odd_token[i] == NULL)
		return (1);
	return (0);
}

void	redirect(t_bt *tree, t_data *data)
{
	if (tree->id % 2 != 0 && valid_odd_token(tree->args) == 0)
	{
		if (ft_strncmp(tree->args, "echo", 4) == 0)
			printf("echo\n");
			// exec_echo();
		else if (ft_strncmp(tree->args, "cd", 2) == 0)
			printf("cd\n");
			// exec_cd();
		else if (ft_strncmp(tree->args, "pwd", 3) == 0)
			printf("pwd\n");
			// exec_pwd();
		else if (ft_strncmp(tree->args, "export", 6) == 0)
			printf("export\n");
			// exec_export();
		else if (ft_strncmp(tree->args, "unset", 5) == 0)
			printf("unset\n");
			// exec_unset();
		else if (ft_strncmp(tree->args, "env", 3) == 0)
			printf("env\n");
			// exec_env();
		else if (ft_strncmp(tree->args, "exit", 4) == 0)
			printf("exit\n");
			// exec_exit();
	}
	if (tree->id % 2 == 0 && valid_even_token(tree->args) == 0)
	{
		if (ft_strncmp(tree->args, "|", 1) == 0)
			printf("|\n");
			// exec_();
		else if (ft_strncmp(tree->args, ">", 1) == 0)
			printf(">\n");
			// exec_();
		else if (ft_strncmp(tree->args, "<", 1) == 0)
			printf("<\n");
			// exec_();
		else if (ft_strncmp(tree->args, ">>", 2) == 0)
			printf(">>\n");
			// exec_();
		else if (ft_strncmp(tree->args, "<<", 2) == 0)
			printf("<<\n");
			// exec_();
	}
	else
		printf("minishell: %s command not found :/\n", tree->args);
	(void)data;
	data = NULL;
}

void	executor(t_data *data)
{
	t_bt	*tree;
	t_bt	*left_tree;

	tree = data->tree;
	while (tree != NULL)
	{
		redirect(tree, data);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			redirect(left_tree, data);
		}
		tree = tree->right;
	}
}
