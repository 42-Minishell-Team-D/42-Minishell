#include "../../libs/minishell.h"

static int	check_arg(char *arg)
{
	if (ft_strncmp(arg, ">>", 2) == 0 \
	|| ft_strncmp(arg, "<<", 2) == 0)
	{
		printf("minishell: syntax error ( °︠ ‿ ︡°) \
		try again, you can do it!\n");
		return (0);
	}
	else if (ft_strncmp(arg, "|", 1) == 0)
	{
		printf("minishell: syntax error ( °︠ ‿ ︡°) \
		try again, you can do it!\n");
		return (0);
	}
	else if (ft_strncmp(arg, ">", 1) == 0 \
	|| ft_strncmp(arg, "<", 1) == 0)
	{
		printf("minishell: syntax error ( °︠ ‿ ︡°) \
		try again, you can do it!\n");
		return (0);
	}
	return (1);
}

static int	check_invalidity(t_bt *tree)
{
	if (tree->id % 2 != 0)
	{
		if (check_arg(tree->args) == 0)
			return (0);
	}
	return (1);
}

int	check_syntax(t_bt *tree)
{
	t_bt	*left_tree;
	char	*last_arg;

	while (tree != NULL)
	{
		last_arg = tree->args;
		if (check_invalidity(tree) == 0)
			return (0);
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			last_arg = left_tree->args;
			if (check_invalidity(left_tree) == 0)
				return (0);
		}
		tree = tree->right;
	}
	if (check_arg(last_arg) == 0)
		return (0);
	return (1);
}
