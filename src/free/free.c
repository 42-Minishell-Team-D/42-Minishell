#include "../../libs/minishell.h"

void free_tree(t_bt *tree)
{
    if (tree != NULL) {
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree->data);
        free(tree);
    }
}

void    free_tokens(char **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}