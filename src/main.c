#include "../libs/minishell.h"

int select_arg(char *p, t_data *data)
{
	if (p[0] == 'e' && p[1] == 'c' && p[2] == 'h' && p[3] == 'o')
		data->rt = exec_echo(p + 4, 0, 1);
	else if (p[0] == 'c' && p[1] == 'd')
		data->rt = exec_cd(p);
	else if (p[0] == 'p' && p[1] == 'w' && p[2] == 'd' && p[3] == '\0')
		data->rt = exec_pwd();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't' && p[6] == '\0')
		printf("exec_export\n");
	else if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't' && p[5] == '\0')
		printf("exec_unset\n");
	else if (p[0] == 'e' && p[1] == 'n' && p[2] == 'v' && p[3] == '\0')
		data->rt = exec_env();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't' && p[4] == '\0')
		exit(0); // That causes leak, even if free(prompt); is implemented
	else if (p[0] == '.' && p[1] == '/')
		data->rt = exec_prog(p);
	else
		printf("minishell: %s command not found :\\\n", p);
	return (0);
}

int	main(void)
{
	t_data	data;
	char	*prompt;

	init_stuff(&data, &prompt);
	while (prompt)
	{
		prompt = readline("minishell$");
		add_history(prompt);
		if (prompt != NULL && prompt[0] == '\n')
			select_arg(prompt, &data);
		free(prompt);
	}
	return (0);
}
