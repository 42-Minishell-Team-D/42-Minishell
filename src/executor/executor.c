#include "../../libs/minishell.h"

int	valid_odd_token(char *token)
{
	int		i;
	char	*valid_odd_inputs[6];

	i = 0;
	valid_odd_inputs[0] = "|";
	valid_odd_inputs[1] = ">";
	valid_odd_inputs[2] = "<";
	valid_odd_inputs[3] = ">>";
	valid_odd_inputs[4] = "<<";
	valid_odd_inputs[5] = NULL;
	while (ft_strncmp(token, valid_odd_inputs[i], 3) != 0)
		i++;
	if (valid_odd_inputs[i] == NULL)
		return (1);
	return (0);
}

int	valid_even_token(char *token)
{
	int		i;
	char	*valid_even_inputs[15];

	i = 0;
	valid_even_inputs[0] = "echo\0";
	valid_even_inputs[1] = "echo ";
	valid_even_inputs[2] = "cd\0";
	valid_even_inputs[3] = "cd ";
	valid_even_inputs[4] = "pwd\0";
	valid_even_inputs[5] = "pwd ";
	valid_even_inputs[6] = "export\0";
	valid_even_inputs[7] = "export ";
	valid_even_inputs[8] = "unset\0";
	valid_even_inputs[9] = "unset ";
	valid_even_inputs[10] = "env\0";
	valid_even_inputs[11] = "env ";
	valid_even_inputs[12] = "exit\0";
	valid_even_inputs[13] = "exit ";
	valid_even_inputs[14] = NULL;
	while (ft_strncmp(token, valid_even_inputs[i], 100) != 0)
		i++;
	if (valid_even_inputs[i] == NULL)
		return (1);
	return (0);
}

void    redirect(t_bt *tree, t_data *data)
{
    if (tree->id % 2 == 0 && valid_even_token(tree->args) == 0)
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
    if (tree->id % 2 != 0 && valid_odd_token(tree->args) == 0)
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

// void	old_executor(t_data *data)
// {
// 	t_bt	*left_tree;
// 	int		i;

// 	i = 0;
// 	left_tree = tree;
// 	while (tree != NULL)
// 	{
// 		if (tree->id % 2 == 0)
// 		{
// 			if (valid_even_token(tree->args) == 1)
// 				return (1);
// 		}
// 		else
// 		{
// 			if (valid_odd_token(tree->args) == 1)
// 				return (1);
// 		}
// 		if (tree->left != NULL)
// 		{
// 			left_tree = tree->left;
// 			if (left_tree->id % 2 == 0)
// 			{
// 				if (valid_even_token(left_tree->args) == 1)
// 					return (1);
// 			}
// 			else
// 			{
// 				if (valid_odd_token(left_tree->args) == 1)
// 					return (1);
// 			}
// 		}
// 		tree = tree->right;
// 	}
// 	return (0);
// }