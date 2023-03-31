#include "../../libs/minishell.h"

void *init_parent_struct(char *token)
{
    t_pipe          *pipe;
    t_redirection   *redirection;

    if (ft_strncmp(token, "|", 1))
    {
        pipe = malloc(sizeof(t_pipe));
        if (!pipe)
            return NULL;
        return (pipe);
    }
    else if (ft_strncmp(token, ">", 1))
    {
        redirection = malloc(sizeof(redirection));
        if (!redirection)
            return NULL;
        return (redirection);
    }
    return NULL;
}

t_bt	*ft_btnew(char *token, int id, t_bt *left, t_bt *right)
{
	t_bt	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->args = token;
    node->id = id;
    node->data = init_parent_struct(token);
    node->left = left;
    node->right = right;
	return (node);
}

void create_node(char **parser, t_bt *tree)        // With current implementation: parser should always be an odd number of strings!
{
    int     i;
    int     size;
    t_bt    *tmp;

    i = 0;
    size = array_size(parser);
    tree = ft_btnew(parser[i], size - i, NULL, NULL);
    i++;
    if (!(i < size))
        return ;
    tree = ft_btnew(parser[i], size - i, tree, NULL);
    i++;
    while (i + 1 < size)
    {
        tmp = ft_btnew(parser[i], size - i, NULL, NULL);
        i++;
        tree = ft_btnew(parser[i], size - i, tmp, tree);
        i++;
    }
    tree = ft_btnew(parser[i], size - i, NULL, tree);
}
