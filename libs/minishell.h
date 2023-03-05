/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:54:01 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/05 19:58:56 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// missing: ttyslot, sigaddset, lstat

/*			src/main.c 			*/


#endif