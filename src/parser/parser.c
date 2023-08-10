/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 22:40:48 by ddantas-          #+#    #+#             */
/*   Updated: 2023/07/03 23:04:05 by ddantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minishell.h"

void	reset_p_vars(t_parser *p)
{
	int	i;

	p->n = 0;
	p->i = 0;
	p->temp = 0;
	p->in_double = 0;
	p->in_single = 0;
	i = 0;
	while (i < 10)
		p->token_alloc[i++] = 0;
}

static void	add_first_empty_token(t_data *data)
{
	int	i;

	i = array_size(data->tokens) - 1;
	while (i >= 0)
	{
		data->tokens[i + 1] = data->tokens[i];
		i--;
	}
	data->tokens[0] = ft_strdup("\0");
}

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	malloc_token(data, p);
	p->in_double = 0;
	p->in_single = 0;
	lexical_analyzer(data, p, data->prompt);

	int	i = 0;
	while (data->tokens[i] != NULL)
	 	printf("token = %s\n", data->tokens[i++]);
	printf("---------------------------\n");
	exit(1);
		
	if (p->token != NULL)
		free(p->token);
	reset_p_vars(p);
	lexical_filter(data, &data->p);
	if (data->tokens[0] == NULL)
		return ;
	if (ft_strncmp(data->tokens[0], "|\0", 2) == 0)
		delete_token(data->tokens);
	if (is_new_token(data->tokens[0][0], data->tokens[0][1]) > 0 && \
	ft_strncmp(data->tokens[0], "|\0", 2) != 0)
		add_first_empty_token(data);
}

//	Parser Print	
