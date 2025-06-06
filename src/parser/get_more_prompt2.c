/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_more_prompt2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:45:53 by ddantas-          #+#    #+#             */
/*   Updated: 2023/08/05 19:31:03 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

int	speed_prompt(char *prompt, int *n)
{
	if (prompt[*n] == '"')
	{
		(*n)++;
		while (prompt[*n] != '\0' && prompt[*n] != '"')
			(*n)++;
		if (prompt[*n] == '\0')
			return (1);
	}
	else if (prompt[*n] == '\'')
	{
		(*n)++;
		while (prompt[*n] != '\0' && prompt[*n] != '\'')
			(*n)++;
		if (prompt[*n] == '\0')
			return (1);
	}
	return (0);
}

static int	quote_handler(char *prompt, char c, int *n)
{
	int		temp;
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	temp = (*n)++;
	while (prompt[*n] != c && prompt[*n])
		(*n)++;
	if (prompt[*n] == '\0')
		return (1);
	if (prompt[*n - 1] == c)
		return (0);
	i = (*n);
	(*n) = temp + 1;
	str = ft_calloc(i - (*n) + 2, sizeof(char));
	ft_strlcpy(str, &prompt[*n], i - (*n) + 1);
	(*n) = i + 1;
	if ((str[1] == '\0' && str[0] != '|') || is_new_token(str[0], str[1]) > 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

static int	new_token_checker(char *prompt, int *n, int i, int c)
{
	if (is_new_token(prompt[*n], prompt[*n + 1]) <= 2)
		(*n) += 2;
	else
		(*n)++;
	while (prompt[*n] == ' ' && prompt[*n])
	{
		(*n)++;
		i++;
	}
	if (prompt[*n] == '\'' || prompt[*n] == '"')
		c = prompt[*n];
	if (c > 0)
	{
		if (quote_handler(prompt, c, n) == 1)
			return (1);
		return (0);
	}
	if ((prompt[*n] == '\0' && prompt[*n - i - 1] != '|'))
		return (1);
	if (ft_strncmp(&prompt[*n], "\0", 2) == 0)
		return (0);
	if (is_new_token(prompt[*n], prompt[*n + 1]) > 0)
		return (1);
	return (0);
}

int	check_valid_syntax(char *prompt)
{
	int	n;

	n = 0;
	if (speed_prompt(prompt, &n) == 1)
		return (1);
	if (prompt[n] == '|')
		return (1);
	n = 0;
	while (prompt[n] != '\0')
	{
		if (speed_prompt(prompt, &n) == 1)
			return (1);
		if (is_new_token(prompt[n], prompt[n + 1]) > 0)
		{
			if (new_token_checker(prompt, &n, 0, '\0') == 1)
				return (1);
		}
		n++;
		if (n > (int)ft_strlen(prompt))
			break ;
	}
	return (0);
}

int	check_valid_last_pipe(char *prompt)
{
	int	i;

	if (prompt[0] == '\0')
		return (0);
	i = ft_strlen(prompt) - 1;
	if (prompt[0] == '|')
		return (0);
	while (prompt[i] == ' ' && prompt[i] == '\t' && i > 0)
		i--;
	if (prompt[i] == '|')
		return (1);
	return (0);
}
