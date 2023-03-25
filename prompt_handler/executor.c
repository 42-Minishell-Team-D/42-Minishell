#include "../libs/minishell.h"

void *init_parent_struct(char *token)
{
    // check if pipe or redirection, init the right struct and return it.
    t_pipe          pipe;
    t_redirection   redirection;

    if (ft_strncmp(token, "|", 1))
    {
        pipe = malloc(sizeof(t_pipe));
        return (pipe);
    }
    else if (ft_strncmp(token, ">", 1))
    {
        redirection = malloc(sizeof(redirection));
        return (redirection);
    }
    return NULL;
}

t_bt	*ft_btnew(char *token, int id, t_bt left, t_bt right)
{
	t_bt	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->args = content;
    tree.id = id;
    tree.data = init_parent_struct(token);
    tree.left = left;
    tree.right = right;
	return (node);
}

void executor(char **parser, t_bt *tree)
{
    int     i;
    int     size;
	t_bt	*node;

    i = 0;
    size = array_size(data->tokens);
    &tree = &node;
    node = ft_btnew(data->tokens[i], size - i, NULL, NULL, NULL);
    while (i < size)
    {
        i++;
        node = ft_btnew(data->tokens[i], size - i, node, NULL)
    }
}