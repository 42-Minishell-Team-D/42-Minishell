#include "../libs/minishell.h"

void	print_tokens(char **tokens)
{
	printf("Tokens:\n");
	for (int i = 0; i < array_size(tokens); i++) {
		printf("  %i: %s\n", i, tokens[i]);
	}
	printf("\n");
}

void print_tree(t_bt *tree)
{
	t_bt	*left_tree = tree;

	printf("Tree:\n");
	while (tree != NULL)
	{
		printf("ID: %i	Token: %s", tree->id, tree->args);
		if (tree->left != NULL)
			printf("	Left: %i", tree->left->id);
		else
			printf("	Left: NULL");
		if (tree->right != NULL)
			printf("	Right: %i", tree->right->id);
		else
			printf("	Right: NULL");
		if (tree->parent != NULL)
			printf("	Parent: %i", tree->parent->id);
		else
			printf("	Parent: NULL");
		printf("\n");
		if (tree->left != NULL)
		{
			left_tree = tree->left;
			printf("ID: %i	Token: %s", left_tree->id, left_tree->args);
			if (left_tree->left != NULL)
				printf("	Left: %i", left_tree->left->id);
			else
				printf("	Left: NULL");
			if (left_tree->right != NULL)
				printf("	Right: %i", left_tree->right->id);
			else
				printf("	Right: NULL");
			if (left_tree->parent != NULL)
				printf("	Parent: %i", left_tree->parent->id);
			else
				printf("	Parent: NULL");
			printf("\n");
		}
		tree = tree->right;
	}
	printf("\n");
}

int	main(void)
{
	t_data		data;

	init_stuff(&data, &data.prompt);
	while (data.prompt)
	{
		
		if (data.slash_r == 0)
			write(1, "\r", 1); // edge case, ctrl+C fixes double minishell$
		data.prompt = readline("minishell$ ");
		data.slash_r = 0;
		if (data.prompt != NULL && data.prompt[0] != '\0')
		{
			get_more_prompt(&data, &data.p);
			// printf("Prompt: %s\n", data.prompt);
			parser(&data);
			// print_tokens(data.tokens);
			data.tree = create_tree(data.tokens, data.tree);
			// print_tree(data.tree);
			if (check_syntax(data.tree) != 0)
				executor(&data);
			free_after_execution(&data);
		}
	}
	rl_clear_history();
	free_at_exit(&data);
	return (0);
}
