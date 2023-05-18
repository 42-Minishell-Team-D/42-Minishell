#include "../../libs/minishell.h"

int	exec_cd(char *path)
{
	int in_single;
	int in_double;

	in_single = 0;
	in_double = 0;
	while (*path != '\0')
	{
		if (*path == '\'' && in_double == 0)
			in_single = !in_single;
		if (*path == '\"' && in_single == 0)
			in_double = !in_double;
		if ((*path == ' ' || *path == '\0') && in_single == 0 && in_double == 0)
			break ;
		path++;
	}
	
	if (*path != '\0')
		chdir(path);
	return (0);
}