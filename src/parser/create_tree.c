#include "../../libs/minishell.h"

char **reverse_array(char **tokens, int size)
{
    int i;
    char *tmp;

    i = 0;
    while (size > i)
    {
        tmp = tokens[size];
        tokens[size] = tokens[i];
        tokens[i] = tmp;
        size--;
        i++;
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

t_bt *create_tree(char **tokens, t_bt *tree)
{
    int     i;
    int     size;
    t_bt    *tmp;

    i = 0;
    // if (check_invalid_inputs(tokens) == 0)       // not working yet
    //     return NULL;
    size = array_size(tokens);
    // tokens = reverse_array(tokens, size);        // cause seg fault from second prompt
    tree = ft_btnew(tokens[i], size - i, NULL, NULL);
    i++;
    if (!(i < size))
        return NULL;
    tree = ft_btnew(tokens[i], size - i, tree, NULL);
    i++;
    while (i + 1 < size)
    {
        tmp = ft_btnew(tokens[i], size - i, NULL, NULL);
        i++;
        tree = ft_btnew(tokens[i], size - i, tmp, tree);
        i++;
    }
    tree = ft_btnew(tokens[i], size - i, NULL, tree);
    return (tree);
}

