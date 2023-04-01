#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE_EXTENDED 1
# define _POSIX_SOURCE

# include "./libft/libft.h"
# include "./ft_printf_fd/ft_printf.h"

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

# define GREAT 1 
# define GREATGREAT 2
# define LESS 3 
# define LESSLESS 4
# define PIPE 5

// missing: ttyslot, sigaddset, lstat

typedef struct binary_tree
{
	char				*args;
	int					id;
	void				*data;
	struct binary_tree	*left;
	struct binary_tree	*right;
	struct binary_tree	*parent;
}					t_bt;

typedef struct pipe
{
	int			write_fd;
	int			read_fd;
}				t_pipe;

typedef struct great
{
	int			write_fd;
	int			read_fd;
}				t_great;

typedef struct greatgreat
{
	int			write_fd;
	int			read_fd;
}				t_greatgreat;

typedef struct less
{
	int			write_fd;
	int			read_fd;
}				t_less;

typedef struct lessless
{
	int			write_fd;
	int			read_fd;
}				t_lessless;

typedef struct parser
{
	int 	n;
	int 	i;
	int 	temp;
	int 	in_double;
	int 	in_single;
	char	*char_temp;
	char	token[250];
}				t_parser;

typedef struct minishell
{
	int					pid;
	int					rt;
	char				*prompt;
	char				**tokens;
	char				**env;
	char				**export;
	struct sigaction	sa;
	struct sigaction	sb;
	struct parser		p;
}					t_data;

/*			src/builtins/			*/
int		exec_cd(char *prompt);
int		exec_echo(char *arg, int n, t_data *data);
int		exec_env(t_data *data);
void	exec_exit(char *p);
int		exec_export(t_data *data, char *p);
int		exec_pwd(void);
int		exec_unset(t_data *data, char *p);

/*		src/parser	*/
int		lexical_analyzer(t_data *data);
t_bt	*create_tree(char **parser, t_bt *tree);
int		check_invalid_inputs(char **tokens);

/*		src/free	*/
void    free_tree(t_bt *tree);

/*		src/executor	*/

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