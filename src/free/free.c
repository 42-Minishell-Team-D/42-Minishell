#include "../../libs/minishell.h"

void	free_tree(t_bt *tree)
{
	if (tree != NULL)
	{
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree->data);
		free(tree);
	}
	tree = NULL;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		ft_bzero(tokens[i], ft_strlen(tokens[i]));
		if (tokens[i] != NULL)
			free(tokens[i]);
		tokens[i++] = NULL;
	}
	free(tokens);
	tokens = NULL;
}

void	free_after_execution(t_data *data)
{
	if (data->tree != NULL)
		free_tree(data->tree);
	if (data->tokens != NULL)
		free_tokens(data->tokens);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->fd_in != 0)
		close(data->fd_in);
}

void	free_at_exit(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_bzero(data->env[i], ft_strlen(data->env[i]));
		if (data->env[i] != NULL)
			free(data->env[i]);
		data->env[i++] = NULL;
	}
	free(data->env);
	i = 0;
	while (data->export[i])
	{
		ft_bzero(data->export[i], ft_strlen(data->export[i]));
		if (data->export[i] != NULL)
			free(data->export[i]);
		data->export[i++] = NULL;
	}
	free(data->export);
}
