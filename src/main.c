#include "../libs/minishell.h"

int select_arg(char *p, t_data *data)
{
	if (p[0] == 'e' && p[1] == 'c' && p[2] == 'h' && p[3] == 'o')
		data->rt = exec_echo(p + 5, 0, data);
	else if (p[0] == 'c' && p[1] == 'd')
		data->rt = exec_cd(p);
	else if (p[0] == 'p' && p[1] == 'w' && p[2] == 'd' && p[3] == '\0')
		data->rt = exec_pwd();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't')
		data->rt = exec_export(data, p);
	else if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't')
		data->rt = exec_unset(data, p);
	else if (p[0] == 'e' && p[1] == 'n' && p[2] == 'v' && p[3] == '\0')
		data->rt = exec_env(data);
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't')
		exec_exit(p);
	else if ((p[0] == '.' && p[1] == '/') || (p[0] == '.' && p[1] == '.' && p[2] == '/'))
		data->rt = exec_prog(p);
	else if (p[0] == 0)	// enter is giving new prompt
		return (0);
	else
		printf("minishell: %s command not found \n", p);
	return (0);
}

void print_tokens(char **tokens)
{
	printf("Tokens:\n");
	for (int i = 0; i < array_size(tokens); i++) {
		printf("  %i: %s\n", i, tokens[i]);
	}
	printf("\n");
}

void print_tree(t_bt *tree)
{
	t_bt *left_tree = tree;
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
		data.prompt = readline("minishell$ ");
		add_history(data.prompt);
		if (data.prompt != NULL && data.prompt[0] != '\0')
		{
			parser(&data);
			print_tokens(data.tokens);
			data.tree = create_tree(data.tokens, data.tree);
			print_tree(data.tree);
			if (check_syntax(data.tree) != 0)
				executor(&data);
			free_after_execution(&data);
		}
		// if (data.prompt != NULL)
		// 	select_arg(data.prompt, &data);
	}
	rl_clear_history();
	free_at_exit(&data);
	free(data.prompt);
	return (0);
}
