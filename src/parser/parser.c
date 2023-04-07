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

void	parser(t_data *data)
{
	t_parser	*p;

	p = &data->p;
	malloc_token(data, p);
	lexical_analyzer(data, p);
	if (p->token != NULL)
		free(p->token);
	reset_p_vars(p);
	lexical_filter(data, &data->p);
	// if (is_new_token(data->tokens[0][0], data->tokens[0][1]) > 0)
	// 	add_empty(data);
	// int	i = 0;
	// while (data->tokens[i] != NULL)
	//  	printf("'%s'\n", data->tokens[i++]);
	// printf("---------------------------\n");
}

//	Parser Print	
