/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:45:43 by ddantas-          #+#    #+#             */
/*   Updated: 2023/03/25 15:07:51 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

// ft_prinft.c
int		ft_printf_fd(int fd, const char *str, ...);

// ft_printf_utils.c
int		check_perc(const char *str, int n);
int		ft_funcion_selector(int fd, char c, va_list ap);

// ft_printf_functions.c
int		p_function(int fd, unsigned long int p);
int		nbr_if(int fd, int n, int sinal);
int		int_len(int n, int len);
void	print_str(int fd, char *str, int n, int len);
int		nbr_function(int fd, int n);

// ft_printf_function_2.c
int		c_function(int fd, char c);
int		s_function(int fd, char *s, int n);
char	x_util(unsigned int n, int caps);
int		x_function(int fd, unsigned int n, int caps, int div);

#endif