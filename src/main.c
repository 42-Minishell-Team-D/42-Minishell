#include "../libs/minishell.h"

static void handler(int sig, siginfo_t *id, void *content)
{
	(void)id;
	(void)content;
	if (sig == SIGINT)
	{
		(void)sig;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
	}
	return ;
}

int	select_arg(char *prompt, int *rt)
{
	if (prompt[0] == 'p' && prompt[1] == 'w' && prompt[2] == 'd' && prompt[3] == '\0')
		*rt = exec_pwd();
	else if (prompt[0] == 'e' && prompt[1] == 'n' && prompt[2] == 'v' && prompt[3] == '\0')
		*rt = exec_env();
	else if (prompt[0] == 'c' && prompt[1] == 'd')
		*rt = exec_cd(prompt);
	else if (prompt[0] == '.' && prompt[1] == '/')
		printf("exec_prog\n");
	else
		printf("minishell: %s command not found :\\\n", prompt);
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
