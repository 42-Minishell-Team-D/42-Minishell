/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:56:41 by lpenelon          #+#    #+#             */
/*   Updated: 2023/07/04 19:34:47 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define LESSLESS 1
# define GREATGREAT 2
# define LESS 4
# define GREAT 3
# define PIPE 5

typedef struct binary_tree
{
	char				*args;
	int					id;
	void				*data;
	struct binary_tree	*left;
	struct binary_tree	*right;
	struct binary_tree	*parent;
}					t_bt;

typedef struct parser
{
	int		n;
	int		i;
	int		temp;
	int		in_double;
	int		in_single;
	char	*char_temp;
	int		token_alloc[10];
	int		bigger_token;
	char	*token;
}				t_parser;

typedef struct minishell
{
	int					rt;
	char				*prompt;
	pid_t				childs_pid[10];
	int					n;
	char				*itoa;
	int					fd_in[2];
	char				**tokens;
	char				**env;
	char				*join;
	char				*tmp;
	char				**split;
	char				**export;
	int					**pipes;
	struct sigaction	sa;
	struct sigaction	sb;
	struct parser		p;
	struct binary_tree	*tree;
	int					slash_r;
}					t_data;

/*			src/builtins/			*/
int		exec_cd(char **split);
int		exec_echo(char **split);
int		exec_env(t_data *data);
int		exec_exit(char **split, t_data *data, int i, char *join);
int		exec_export(char **split, t_data *data, t_bt *tree);
int		exec_pwd(void);
int		exec_unset(char **split, t_data *data);

/*		src/parser	*/
void	reset_p_vars(t_parser *p);
char	*hda_quotes(char *ptr, t_parser *p);
int		lexical_analyzer(t_data *data, t_parser *p, char *ptr);
void	malloc_token(t_data *data, t_parser *p);
char	*hda_tkn_quotes(char *ptr, t_parser *p);
void	token_memory_alloc(t_data *data, t_parser *p);
char	*lexical_prompt_filter(char *prompt);
void	lexical_filter(t_data *data, t_parser *p);
void	parser(t_data *data);
t_bt	*create_tree(char **parser, t_bt *tree, int i);
int		check_syntax(t_bt *tree);
int		get_more_prompt(t_data *data, t_parser *p, int baal);
int		check_valid_syntax(char *prompt);
int		redirect_input_check(t_data *data);
int		check_valid_last_pipe(char *prompt);
char	*handle_dollar_anal(char *ptr, t_parser *p, t_data *data);
char	*handle_special_char_anal(char *ptr, t_parser *p, t_data *data);
int		check_valid_heredoc(char *prompt);

/*		src/free	*/
void	free_after_execution(t_data *data);
void	free_at_exit(t_data *data);
void	free_tokens(char **tokens);
void	free_if_err(char **var, int exit_code);
void	free_tree(t_bt *tree);

/*		src/executor	*/
void	executor(t_data *data);
int		init_executor(t_data *data);
void	close_free_pipes(t_data *data);
void	close_unused_pipes(int i, t_bt *tree, t_data *data);
int		get_number_of_processes(t_bt *tree);
void	redirect_pipe(t_bt *tree, t_data *data);
t_bt	*redirect_great(t_bt *tree, t_data *data, int option, int rd);
char	**clear_quotes(char **split);
void	init_child(int id, t_bt *tree, t_data *data);
void	pipe_child(char **split, t_bt *tree, t_data *data);
char	*get_eof(char *prompt, t_parser *p);
void	update_prompt(t_data *data, t_parser *p);
int		speed_prompt(char *prompt, int *n);
void	print_export(t_data *data);
int		check_variable_name(char *var);
int		is_equal_sign(char *var);

/*			src/init.c			*/
void	handler(int sig, siginfo_t *id, void *content);
void	init_env(t_data *data, int i);
void	init_export(t_data *data, int i);
void	init_sa(struct sigaction sa, struct sigaction sb);
void	init_stuff(t_data *data, char **prompt);
char	*quote(char *export, int i, int j);

/*			src/utils1.c		*/
int		array_size(char **s);
int		search_var(char **s);
int		nb_char_max(char **s);
int		is_new_token(char c, char c2);
int		is_new_readline(char *token);
void	*ft_realloc(void *ptr, size_t size);
char	**ft_split_args(char *token, t_parser *p);
int		get_biggest_len(char *s1, char *s2);
char	*ft_getenv(char *name, char **env);
char	*ft_strcdup(const char *s1, int i, char c);
void	delete_char_filter(char *str);

/*			src/builtins/utils_builtins.c			*/
char	*get_before_equal_sign(char *var);
char	*get_before_equal_sign_export(char *var);

/*			src/main.c 			*/
int		select_arg(char *p, t_data *data);
void	print_tokens(char **tokens);

#endif