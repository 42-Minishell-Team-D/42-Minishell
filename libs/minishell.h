#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE_EXTENDED 1
# define _POSIX_SOURCE

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

// missing: ttyslot, sigaddset, lstat

typedef struct command
{
	char				*prompt;
	int					argc;
	char				**argv;
}			t_command;

typedef struct minishell
{
	int					pid;
	int					rt;
	char				**env;
	char				**export;
	struct sigaction	sa;
	struct sigaction	sb;
	struct t_command	*cmd;
}				t_data;

/*			builtins/			*/
int		exec_cd(char *prompt);
int		exec_echo(char *arg, int n, t_data *data);
int		exec_env(t_data *data);
void	exec_exit(char *p);
int		exec_export(t_data *data, char *p);
int		exec_pwd(void);
int		exec_unset(t_data *data, char *p);

/*		prompt_handler/handler.c	*/
void	divide_prompt(t_command *cmd);

/*			src/functions1.c	*/
int		exec_prog(char *prompt);

/*			src/init.c			*/
void	handler(int sig, siginfo_t *id, void *content);
void	init_data(t_data *data, int i);
void	init_sa(struct sigaction sa, struct sigaction sb);
void	init_stuff(t_data *data, char **prompt);

/*			src/utils1.c		*/
int		array_size(char **s);
int		search_var(char **s);
int		nb_char_max(char **s);

/*			src/main.c 			*/
int		select_arg(char *p, t_data *data);

#endif