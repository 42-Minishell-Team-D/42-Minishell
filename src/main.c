#include "../libs/minishell.h"

int select_arg(char *p, t_data *data)
{
	if (p[0] == 'e' && p[1] == 'c' && p[2] == 'h' && p[3] == 'o')
		data->rt = exec_echo(p + 5, 0, data);
	else if (p[0] == 'c' && p[1] == 'd')
		data->rt = exec_cd(p);
	else if (p[0] == 'p' && p[1] == 'w' && p[2] == 'd' && p[3] == '\0')
		data->rt = exec_pwd();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't')
		data->rt = exec_export(data, p);
	else if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't')
		data->rt = exec_unset(data, p);
	else if (p[0] == 'e' && p[1] == 'n' && p[2] == 'v' && p[3] == '\0')
		data->rt = exec_env(data);
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't')
		exec_exit(p);
	else if ((p[0] == '.' && p[1] == '/') || (p[0] == '.' && p[1] == '.' && p[2] == '/'))
		data->rt = exec_prog(p);
	else if (p[0] == 0)	// enter is giving new prompt
		return (0);
	else
		printf("minishell: %s command not found :/\n", p);
	return (0);
}

int	main(void)
{
	t_data		data;
	// t_bt		tree;
	// char *parser[] = {
    // 	"grep 'org'",
    // 	"|",
    // 	"grep 'GNOME'",
    // 	"|",
    // 	"export",
	// };

	init_stuff(&data, &data.prompt);
	while (data.prompt)
	{
		data.prompt = readline("minishell$ ");
		add_history(data.prompt);
		//parser(&data);
		// create_node(parser, &tree);
		// executor(&data, &tree);
		if (data.prompt != NULL)
			select_arg(data.prompt, &data);
		free(data.prompt);
	}
	rl_clear_history();
	free(data.prompt);
	return (0);
}
