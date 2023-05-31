#include "../../libs/minishell.h"

int	invalid_odd_token(char *token)
{
	int		i;
	char	*invalid_odd_token[6];

	i = 0;
	invalid_odd_token[0] = "|";
	invalid_odd_token[1] = ">";
	invalid_odd_token[2] = "<";
	invalid_odd_token[3] = ">>";
	invalid_odd_token[4] = "<<";
	invalid_odd_token[5] = NULL;
	while (invalid_odd_token[i] != NULL && \
	ft_strncmp(token, invalid_odd_token[i], 3) != 0)
		i++;
	if (invalid_odd_token[i] == NULL)
		return (1);
	return (0);
}

int	check_invalidity(t_bt *tree)
{
	if (tree->id % 2 != 0)
	{
		if (ft_strncmp(tree->args, ">>", 2) == 0 \
		|| ft_strncmp(tree->args, "<<", 2) == 0)
		{
			printf("minishell: syntax error ( °︠ ‿ ︡°) \
			try again, you can do it!\n");
			return (0);
		}
		else if (ft_strncmp(tree->args, "|", 1) == 0)
		{
			printf("minishell: syntax error ( °︠ ‿ ︡°) \
			try again, you can do it!\n");
			return (0);
		}
		else if (ft_strncmp(tree->args, ">", 1) == 0 \
		|| ft_strncmp(tree->args, "<", 1) == 0)
		{
			printf("minishell: syntax error ( °︠ ‿ ︡°) \
			try again, you can do it!\n");
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_bt *tree)
{
	t_bt	*left_tree;

	while (tree != NULL)
	{
		if (check_invalidity(tree) == 0)
			return (0);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			if (check_invalidity(left_tree) == 0)
				return (0);
		}
		tree = tree->right;
	}
	return (1);
}
