// for example
// | ok > ok
// this doesn't create a ok file
// unlike 
// ok | ok > ok

// My understanding: Syntax is checked before executor runs, errors stop the process. and ouput "bash: syntax error near unexpected token `|'"
// If no syntax errors, executor run every command and ouput "ok: command not found".

#include "../../libs/minishell.h"

void	check_syntax(t_bt *tree)
{
	(void)tree;
	tree = NULL;
}