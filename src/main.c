/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:40:53 by ddantas-          #+#    #+#             */
/*   Updated: 2023/08/05 17:18:31 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

// void	print_tokens(char **tokens)
// {
// 	printf("Tokens:\n");
// 	for (int i = 0; i < array_size(tokens); i++)
// 	{
// 		printf("  %i: %s\n", i, tokens[i]);
// 	}
// 	printf("\n");
// }

// void print_tree(t_bt *tree)
// {
// 	t_bt	*left_tree;

// 	left_tree = tree;
// 	printf("Tree:\n");
// 	while (tree != NULL)
// 	{
// 		printf("ID: %i	Token: %s", tree->id, tree->args);
// 		if (tree->left != NULL)
// 			printf("	Left: %i", tree->left->id);
// 		else
// 			printf("	Left: NULL");
// 		if (tree->right != NULL)
// 			printf("	Right: %i", tree->right->id);
// 		else
// 			printf("	Right: NULL");
// 		if (tree->parent != NULL)
// 			printf("	Parent: %i", tree->parent->id);
// 		else
// 			printf("	Parent: NULL");
// 		printf("\n");
// 		if (tree->left != NULL)
// 		{
// 			left_tree = tree->left;
// 			printf("ID: %i	Token: %s", left_tree->id, left_tree->args);
// 			if (left_tree->left != NULL)
// 				printf("	Left: %i", left_tree->left->id);
// 			else
// 				printf("	Left: NULL");
// 			if (left_tree->right != NULL)
// 				printf("	Right: %i", left_tree->right->id);
// 			else
// 				printf("	Right: NULL");
// 			if (left_tree->parent != NULL)
// 				printf("	Parent: %i", left_tree->parent->id);
// 			else
// 				printf("	Parent: NULL");
// 			printf("\n");
// 		}
// 		tree = tree->right;
// 	}
// 	printf("\n");
// }

// if (data->slash_r == 0)
	// write(1, "\r", 1);
// data->slash_r = 0; 
// put betwen like 75 and 76 and delete (void)data to put as it was

static char	*get_prompt(t_data *data)
{
	(void)data;
	return (readline("minishell$ "));
}

static int	check_empty_prompt(t_data *data)
{
	int	i;

	i = 0;
	while (data->prompt[i] != '\0')
	{
		if (data->prompt[i] != ' ' && data->prompt[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

static int	main2(t_data *data)
{
	if (get_more_prompt(data, &data->p, 0) == 1)
	{
		if (data->prompt != NULL)
			free(data->prompt);
		free(data->p.char_temp);
		close(data->fd_in[1]);
		return (1);
	}
	if (data->fd_in[1] > 0)
		write(data->fd_in[1], data->p.char_temp, ft_strlen(data->p.char_temp));
	free(data->p.char_temp);
	if (data->fd_in[1] > 0)
		close(data->fd_in[1]);
	parser(data);
	if (data->tokens[0][0] == '\0')
		return (1);
	if (redirect_input_check(data) > 0)
	{
		free_after_execution(data);
		return (1);
	}
	data->tree = create_tree(data->tokens, data->tree, 0);
	executor(data);
	free_after_execution(data);
	return (0);
}

int	main(void)
{
	t_data		data;

	init_stuff(&data, &data.prompt);
	while (data.prompt)
	{
		data.prompt = get_prompt(&data);
		if (data.prompt == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (data.prompt != NULL && check_empty_prompt(&data) == 0)
		{
			free(data.prompt);
			continue ;
		}
		if (data.prompt != NULL && data.prompt[0] != '\0'
			&& data.prompt[0] != '\n')
			data.prompt = ft_realloc(data.prompt, ft_strlen(data.prompt) + 1);
		if (data.prompt != NULL && data.prompt[0] != '\0')
		{
			add_history(data.prompt);
			data.p.char_temp = ft_calloc(1, 1);
			if (main2(&data) == 1)
				continue ;
		}
	}
	rl_clear_history();
	free_at_exit(&data);
	return (data.rt);
}
