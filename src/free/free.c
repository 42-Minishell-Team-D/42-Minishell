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
