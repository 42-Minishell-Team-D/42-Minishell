#include "../libs/minishell.h"

static void handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
	}
	return ;
}

int select_arg(char *p, int *rt)
{
	if (p[0] == 'e' && p[1] == 'c' && p[2] == 'h' && p[3] == 'o')
		printf("exec_echo\n");
	else if (p[0] == 'c' && p[1] == 'd')
		*rt = exec_cd(p);
	else if (p[0] == 'p' && p[1] == 'w' && p[2] == 'd' && p[3] == '\0')
		*rt = exec_pwd();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'p' && p[3] == 'o' && p[4] == 'r' && p[5] == 't')
		*rt = exec_export(p);
	else if (p[0] == 'u' && p[1] == 'n' && p[2] == 's' && p[3] == 'e' && p[4] == 't')
		*rt = exec_unset(p);
	else if (p[0] == 'e' && p[1] == 'n' && p[2] == 'v' && p[3] == '\0')
		*rt = exec_env();
	else if (p[0] == 'e' && p[1] == 'x' && p[2] == 'i' && p[3] == 't')
		exec_exit(p);
	else if (p[0] == '.' && p[1] == '/')
		*rt = exec_prog(p);
	else if (p[0] == 0)	// enter is giving new prompt
		return (0);
	else
		printf("minishell: %s command not found :\\\n", p);
	return (0);
}


int	main(void)
{
	struct sigaction	sa;
	char				*prompt;
	int					rt;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	prompt = (char *)1;
	rt = 0;
	while (prompt)
	{
		prompt = readline("minishell$");
		add_history(prompt);
		if (prompt)
			select_arg(prompt, &rt);
	}
	return (0);
}
