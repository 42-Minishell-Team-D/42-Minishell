#include "../../libs/minishell.h"

char **reverse_array(char **tokens, int size)
{
    char    *tmp;
    int     i;
    int     j;

    i = 0;
    j = size - 1;
    while (i < j)
    {
        tmp = tokens[i];
        tokens[i] = tokens[j];
        tokens[j] = tmp;
        i++;
        j--;
    }
    return (tokens);
}

void *init_parent_struct(char *token)
{
    t_pipe          *pipe;
    t_great         *great;
    // t_greatgreat    *greatgreat;
    // t_less          *less;
    // t_lessless      *lessless;

    if (ft_strncmp(token, "|", 1))
    {
        pipe = malloc(sizeof(t_pipe));
        if (!pipe)
            return NULL;
        return (pipe);
    }
    else if (ft_strncmp(token, ">", 1))
    {
        great = malloc(sizeof(great));
        if (!great)
            return NULL;
        return (great);
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

t_bt    *assign_parents(t_bt *tree, t_bt *parent)
{
    if (tree)
    {
        tree->parent = parent;
        assign_parents(tree->left, tree);
        assign_parents(tree->right, tree);
    }
    return (tree);
}

t_bt    *create_tree(char **tokens, t_bt *tree)
{
    int     i;
    int     size;
    t_bt    *tmp;

    i = 0;
    size = array_size(tokens);
    tokens = reverse_array(tokens, size);
    tree = ft_btnew(tokens[i], size - i, NULL, NULL);
    i++;
    if (size % 2 != 0 && i < size)
    {
        tree = ft_btnew(tokens[i], size - i, tree, NULL);
        i++;
    }
    while (i + 1 < size)
    {
        tmp = ft_btnew(tokens[i], size - i, NULL, NULL);
        i++;
        tree = ft_btnew(tokens[i], size - i, tmp, tree);
        i++;
    }
    if (i < size)
        tree = ft_btnew(tokens[i], size - i, NULL, tree);
    tree = assign_parents(tree, NULL);
    return (tree);
}
