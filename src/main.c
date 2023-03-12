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

int	select_arg(char *prompt)
{
	if (prompt[0] == 'p' && prompt[1] == 'w' && prompt[2] == 'd' && prompt[3] == '\0')
		printf("exec_pwd\n");
	if (prompt[0] == '.' && prompt[1] == '/')
		printf("exec_prog\n");

	return (0);
}

int	main(void)
{
	struct sigaction	sa;
	char				*prompt;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	prompt = (char *)1;
	while (prompt)
	{
		prompt = readline("minishell$");
		if (prompt)
			select_arg(prompt);
	}
	return (0);
}
