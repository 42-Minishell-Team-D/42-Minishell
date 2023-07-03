#include "../libs/minishell.h"

void	print_tokens(char **tokens)
{
	printf("Tokens:\n");
	for (int i = 0; i < array_size(tokens); i++)
	{
		printf("  %i: %s\n", i, tokens[i]);
	}
	printf("\n");
}

void print_tree(t_bt *tree)
{
	t_bt	*left_tree;

	left_tree = tree;
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
			write(1, "\r", 1);
		data.prompt = readline("minishell$ ");
		if (data.prompt != NULL)
			data.prompt = ft_realloc(data.prompt, ft_strlen(data.prompt) + 1);
		data.slash_r = 0;
		data.fd_in[0] = -1;
		if (data.prompt != NULL && data.prompt[0] != '\0')
		{
			add_history(data.prompt);
			data.p.char_temp = ft_calloc(1, 1);
			if (get_more_prompt(&data, &data.p, 0, NULL) == 1)
			{
				// free_after_execution(&data);
				if (data.prompt != NULL)
					free(data.prompt);
				free(data.p.char_temp);
				close(data.fd_in[1]);
				continue ;
			}
			if (data.fd_in[1] > 0)
				write(data.fd_in[1], data.p.char_temp, ft_strlen(data.p.char_temp));
			free(data.p.char_temp);
			if (data.fd_in[1] > 0)
				close(data.fd_in[1]);
			// printf("Prompt: %s\n", data.prompt);

			parser(&data);

			// print_tokens(data.tokens);

			if (redirect_input_check(&data) > 0)
			{
				free_after_execution(&data);
				continue ;
			}
			
			// print_tokens(data.tokens);

			data.tree = create_tree(data.tokens, data.tree, 0);
			// print_tree(data.tree);

			executor(&data, 0, 0);
			free_after_execution(&data);
		}
	}
	rl_clear_history();
	free_at_exit(&data);
	return (data.rt);
}
